/* 这是一个用于高性能 NetX IP 堆栈的 DHCP 客户端小示例。 */

#include "tx_api.h"               // ThreadX API 头文件
#include "nx_api.h"               // NetX API 头文件
#ifndef NX_DISABLE_IPV4
#include "nxd_dhcp_client.h"      // DHCP 客户端 API 头文件
#include "nxd_dhcp_server.h"      // DHCP 服务器 API 头文件

// 定义演示所需的常量
#define DEMO_STACK_SIZE             4096                // 线程堆栈大小
#define NX_PACKET_SIZE              1536                // 单个数据包的大小
#define NX_PACKET_POOL_SIZE         NX_PACKET_SIZE * 8  // 数据包池的大小

// DHCP 服务器 IP 地址
#define NX_DHCP_SERVER_IP_ADDRESS_0 IP_ADDRESS(10,0,0,1)   
// 可分配的起始和结束 IP 地址范围
#define START_IP_ADDRESS_LIST_0     IP_ADDRESS(10,0,0,10)
#define END_IP_ADDRESS_LIST_0       IP_ADDRESS(10,0,0,19)

// 子网掩码、默认网关和 DNS 服务器地址
#define NX_DHCP_SUBNET_MASK_0       IP_ADDRESS(255,255,255,0)
#define NX_DHCP_DEFAULT_GATEWAY_0   IP_ADDRESS(10,0,0,1)
#define NX_DHCP_DNS_SERVER_0        IP_ADDRESS(10,0,0,1)

// 定义接口索引
#define NX_DHCP_INTERFACE_INDEX     0             

// 如果定义了该宏，则主机请求一个（先前的）客户端 IP 地址
/*
#define REQUEST_CLIENT_IP
*/

#ifdef REQUEST_CLIENT_IP       
// 请求特定的 IP 地址使用 DHCP 客户端地址选项
#define NX_DHCP_CLIENT_IP_ADDRESS   IP_ADDRESS(10,0,0,18)  

// 如果定义了 NX_TRUE，客户端请求跳过 DISCOVER 消息，直接进入引导状态
#define SKIP_DISCOVER_MESSAGE       NX_TRUE 
#endif

// 定义 ThreadX 和 NetX 对象控制块
TX_THREAD               client_thread;           // 客户端线程
NX_PACKET_POOL          client_pool;             // 客户端数据包池
NX_IP                   client_ip;               // 客户端 IP 实例
NX_DHCP                 dhcp_client;             // DHCP 客户端实例

TX_THREAD               server_thread;           // 服务器线程
NX_PACKET_POOL          server_pool;             // 服务器数据包池
NX_IP                   server_ip;               // 服务器 IP 实例
NX_DHCP_SERVER          dhcp_server;             // DHCP 服务器实例

// 定义演示应用程序中使用的计数器
ULONG                   client_thread_counter;    // 客户端线程计数器
ULONG                   state_changes;           // 状态变化计数器
ULONG                   error_counter;           // 错误计数器
CHAR                    *pointer;                // 内存指针

UCHAR message[50] = "My Ping Request!";           // 要发送的 ping 消息

// 定义线程原型
void server_thread_entry(ULONG thread_input);     // 服务器线程入口
void client_thread_entry(ULONG thread_input);     // 客户端线程入口
void dhcp_state_change(NX_DHCP *dhcp_ptr, UCHAR new_state); // DHCP 状态变化处理函数

// 选择以太网驱动程序
void _nx_ram_network_driver(struct NX_IP_DRIVER_STRUCT *driver_req);

// 定义主入口点
int main()
{
    // 进入 ThreadX 内核
    tx_kernel_enter();
    return 0;
}

// 定义初始系统配置
void tx_application_define(void *first_unused_memory)
{
    UINT status;

    // 设置工作指针
    pointer = (CHAR *) first_unused_memory;

    // 创建客户端线程
    tx_thread_create(&client_thread, "thread client", client_thread_entry, 0,  
            pointer, DEMO_STACK_SIZE, 
            4, 4, TX_NO_TIME_SLICE, TX_AUTO_START);
    pointer = pointer + DEMO_STACK_SIZE;  // 移动指针以分配内存

    // 创建服务器线程
    tx_thread_create(&server_thread, "thread server", server_thread_entry, 0,  
            pointer, DEMO_STACK_SIZE, 
            3, 3, TX_NO_TIME_SLICE, TX_AUTO_START);
    pointer = pointer + DEMO_STACK_SIZE;  // 移动指针以分配内存

    // 初始化 NetX 系统
    nx_system_initialize();

    // 创建客户端数据包池
    status = nx_packet_pool_create(&client_pool, "NetX Main Packet Pool", 1024, pointer, NX_PACKET_POOL_SIZE);
    pointer = pointer + NX_PACKET_POOL_SIZE; // 移动指针以分配内存

    // 检查数据包池创建错误
    if (status)
        return;
    
    // 创建服务器数据包池
    status = nx_packet_pool_create(&server_pool, "NetX Main Packet Pool", 1024, pointer, NX_PACKET_POOL_SIZE);
    pointer = pointer + NX_PACKET_POOL_SIZE; // 移动指针以分配内存

    // 检查数据包池创建错误
    if (status)
        return;

    // 为 DHCP 客户端创建 IP 实例
    status = nx_ip_create(&client_ip, "DHCP Client", IP_ADDRESS(0, 0, 0, 0), 0xFFFFFF00UL, &client_pool, _nx_ram_network_driver, pointer, 2048, 1);
    pointer = pointer + 2048; // 移动指针以分配内存

    // 检查 IP 创建错误
    if (status)
        return;
    
    // 为 DHCP 服务器创建 IP 实例
    status = nx_ip_create(&server_ip, "DHCP Server", NX_DHCP_SERVER_IP_ADDRESS_0, 0xFFFFFF00UL, &server_pool, _nx_ram_network_driver, pointer, 2048, 1);
    pointer = pointer + 2048; // 移动指针以分配内存

    // 检查 IP 创建错误
    if (status)
        return;         

    // 启用 ARP 并为 DHCP 客户端 IP 提供 ARP 缓存内存
    status = nx_arp_enable(&client_ip, (void *) pointer, 1024);
    pointer = pointer + 1024; // 移动指针以分配内存
    
    // 启用 ARP 并为 DHCP 服务器 IP 提供 ARP 缓存内存
    status += nx_arp_enable(&server_ip, (void *) pointer, 1024);
    pointer = pointer + 1024; // 移动指针以分配内存

    // 检查 ARP 启用错误
    if (status)
        return;

    // 启用 UDP 流量
    status = nx_udp_enable(&client_ip);
    status += nx_udp_enable(&server_ip);

    // 检查 UDP 启用错误
    if (status)
        return;

    // 启用 ICMP
    status = nx_icmp_enable(&client_ip);
    status += nx_icmp_enable(&server_ip);

    // 检查错误
    if (status)
        return;
}

// 定义服务器线程
void server_thread_entry(ULONG thread_input)
{
    UINT status;
    UINT addresses_added;

    NX_PARAMETER_NOT_USED(thread_input); // 避免未使用参数警告

    // 修改 MTU 大小以避免 DHCP 数据包的碎片化，默认 MTU 大小为 128
    status = nx_ip_interface_mtu_set(&server_ip, NX_DHCP_INTERFACE_INDEX, 1500);    

    // 检查 MTU 设置错误
    if (status)                         
        return;

    // 创建 DHCP 服务器
    status = nx_dhcp_server_create(&dhcp_server, &server_ip, pointer, DEMO_STACK_SIZE, 
                                   "DHCP Server", &server_pool);
    pointer = pointer + DEMO_STACK_SIZE; // 移动指针以分配内存
    
    // 检查创建 DHCP 服务器的错误
    if (status)
        return;

    // 为第一个接口加载可分配的 DHCP IP 地址
    status = nx_dhcp_create_server_ip_address_list(&dhcp_server, NX_DHCP_INTERFACE_INDEX, START_IP_ADDRESS_LIST_0, 
                                                   END_IP_ADDRESS_LIST_0, &addresses_added);

    // 检查创建地址列表的错误
    if (status)
        return;

    // 验证所有地址是否已添加到列表
    if (addresses_added != 10)
        return;

    // 设置接口网络参数
    status = nx_dhcp_set_interface_network_parameters(&dhcp_server, NX_DHCP_INTERFACE_INDEX, NX_DHCP_SUBNET_MASK_0, 
                                                      NX_DHCP_DEFAULT_GATEWAY_0, NX_DHCP_DNS_SERVER_0);

    // 检查设置网络参数的错误
    if (status)
        return;

    // 启动 DHCP 服务器任务
    status = nx_dhcp_server_start(&dhcp_server);

    // 检查启动 DHCP 服务器的错误
    if (status)
        return;
}

// 定义客户端线程
void client_thread_entry(ULONG thread_input)
{
    UINT status;
    UINT actual_status;
    UINT length;
    UINT ping = NX_TRUE;           // 是否进行 ping 操作的标志
    UINT run_dhcp_client = NX_TRUE; // 控制 DHCP 客户端运行的标志
    NX_PACKET *my_packet;           // 用于 ping 的数据包指针

    NX_PARAMETER_NOT_USED(thread_input); // 避免未使用参数警告

    // 修改 MTU 大小以避免 DHCP 数据包的碎片化，默认 MTU 大小为 128
    status = nx_ip_interface_mtu_set(&client_ip, NX_DHCP_INTERFACE_INDEX, 1500);    

    // 检查 MTU 设置错误
    if (status)                         
        return;

    // 创建 DHCP 实例
    status = nx_dhcp_create(&dhcp_client, &client_ip, "DHCP-CLIENT");
    if (status)
        return;    

#ifdef REQUEST_CLIENT_IP
    // 请求特定 IP 地址
    status = nx_dhcp_request_client_ip(&dhcp_client, NX_DHCP_CLIENT_IP_ADDRESS, SKIP_DISCOVER_MESSAGE);
    if (status)
        error_counter++;
#endif

    // 注册状态变化通知
    status = nx_dhcp_state_change_notify(&dhcp_client, dhcp_state_change);
    if (status)
        error_counter++;

    // 启动 DHCP 客户端
    nx_dhcp_start(&dhcp_client);
    while(run_dhcp_client)
    {
        // 等待 DHCP 分配 IP 地址
        do
        {
            // 检查地址解析状态
            status = nx_ip_status_check(&client_ip, NX_IP_ADDRESS_RESOLVED, (ULONG *) &actual_status, NX_IP_PERIODIC_RATE);
    
            // 检查状态
            if (status)
            {
                // 等待一会儿
                tx_thread_sleep(NX_IP_PERIODIC_RATE);
            }
    
        } while (status != NX_SUCCESS);
    
        length = sizeof(message);
    
        while(ping)
        {
            // 向网络上的其他主机发送 ping 请求
            status = nx_icmp_ping(&client_ip, NX_DHCP_SERVER_IP_ADDRESS_0, (CHAR *)message, length, &my_packet, NX_IP_PERIODIC_RATE);
            if (status)
               error_counter++;
            else
                nx_packet_release(my_packet); // 释放数据包

            // 增加计数器
            client_thread_counter++; 
          
            // 暂停一段时间
            tx_thread_sleep(NX_IP_PERIODIC_RATE);
        }
    
        // 这里可以发送消息到服务器，例如 DECLINE 如果 IP 地址被另一个主机占用
        // nx_dhcp_send_request(&dhcp_client, NX_DHCP_TYPE_DHCPDECLINE);

        // 如果主机正在切换网络或运行 DHCP 循环，可以释放 IP 地址
        // nx_dhcp_release(&dhcp_client);
    
        // 停止 DHCP 客户端
        nx_dhcp_stop(&dhcp_client);
    
        tx_thread_sleep(NX_IP_PERIODIC_RATE);
    
        // 清除网络参数并重新启动客户端
        nx_dhcp_reinitialize(&dhcp_client);
    
        // 重新启动 DHCP 客户端线程
        nx_dhcp_start(&dhcp_client);
    
        // 允许恢复 ping 尝试
        ping = NX_TRUE;
    }

    // 完成所有操作，释放资源
    nx_dhcp_delete(&dhcp_client);
    return;
}

// DHCP 状态变化处理函数
void dhcp_state_change(NX_DHCP *dhcp_ptr, UCHAR new_state)
{
    NX_PARAMETER_NOT_USED(dhcp_ptr);
    NX_PARAMETER_NOT_USED(new_state);

    // 增加状态变化计数器
    state_changes++;
    return;
}
#endif /* NX_DISABLE_IPV4 */

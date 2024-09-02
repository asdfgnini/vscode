/**************************************************************************/
/*                                                                        */
/*       Copyright (c) Microsoft Corporation. All rights reserved.        */
/*                                                                        */
/*       This software is licensed under the Microsoft Software License   */
/*       Terms for Microsoft Azure RTOS. Full text of the license can be  */
/*       found in the LICENSE file at https://aka.ms/AzureRTOS_EULA       */
/*       and in the root directory of this software.                      */
/*                                                                        */
/**************************************************************************/

/* 

   这是一个高性能 NetX TCP/IP 协议栈的 MQTT 客户端小型示例程序。

   本示例程序通过 IP 地址 10.0.10.1 连接到 Mosquitto 服务器。它订阅一个主题，
   并向相同的主题发送消息。应用程序应能够从代理接收到相同的消息。

   本示例假设已正确配置 NetX Duo TCP/IP 协议栈，并启用了 TCP 模块。
   入口函数为 "thread_mqtt_entry"。调用者需要传递 IP 实例和有效的包池实例。
*/

#include "nx_api.h"
#include "nxd_mqtt_client.h"

/* MQTT 示例定义 */

/* 本地服务器的 IP 地址 */
#define  LOCAL_SERVER_ADDRESS (IP_ADDRESS(192, 168, 1, 1))

/*****************************************************************************************/
/* MQTT 本地服务器 IoT 客户端示例。                                                     */
/*****************************************************************************************/

/* 定义栈大小 */
#define  DEMO_STACK_SIZE            2048
#define  CLIENT_ID_STRING           "mytestclient"  // 客户端 ID 字符串
#define  MQTT_CLIENT_STACK_SIZE     4096  // MQTT 客户端栈大小

/* 获取字符串长度的宏定义 */
#define  STRLEN(p)                  (sizeof(p) - 1)

/* 声明 MQTT 线程栈空间 */
static ULONG                        mqtt_client_stack[MQTT_CLIENT_STACK_SIZE / sizeof(ULONG)];

/* 声明 MQTT 客户端控制块 */
static NXD_MQTT_CLIENT              mqtt_client;

/* 定义消息接收信号的标识符 */

/* 定义测试线程 */
#define TOPIC_NAME                  "topic"  // 主题名称
#define MESSAGE_STRING              "This is a message. "  // 消息内容

/* 定义 MQTT 内部线程的优先级 */
#define MQTT_THREAD_PRIORTY         2

/* 定义 MQTT 保持连接的心跳时间为 5 分钟 */
#define MQTT_KEEP_ALIVE_TIMER       300

/* 定义 QoS 等级 */
#define QOS0                        0
#define QOS1                        1

/* 声明事件标志，在本示例中使用 */
TX_EVENT_FLAGS_GROUP                mqtt_app_flag;
#define DEMO_MESSAGE_EVENT          1  // 定义消息事件标志
#define DEMO_ALL_EVENTS             3  // 定义所有事件标志

/* 声明用于存储消息和主题的缓冲区 */
static UCHAR message_buffer[NXD_MQTT_MAX_MESSAGE_LENGTH];
static UCHAR topic_buffer[NXD_MQTT_MAX_TOPIC_NAME_LENGTH];

/* 声明断开连接的通知函数 */
static VOID my_disconnect_func(NXD_MQTT_CLIENT *client_ptr)
{
    NX_PARAMETER_NOT_USED(client_ptr);  // 未使用参数宏
    printf("client disconnected from server\n");  // 打印客户端断开连接的信息
}

/* 声明接收消息通知函数 */
static VOID my_notify_func(NXD_MQTT_CLIENT* client_ptr, UINT number_of_messages)
{
    NX_PARAMETER_NOT_USED(client_ptr);  // 未使用参数宏
    NX_PARAMETER_NOT_USED(number_of_messages);  // 未使用参数宏
    tx_event_flags_set(&mqtt_app_flag, DEMO_MESSAGE_EVENT, TX_OR);  // 设置消息事件标志
    return;
}

/* 入口函数，处理 MQTT 客户端线程的主要逻辑 */
void thread_mqtt_entry(NX_IP *ip_ptr, NX_PACKET_POOL *pool_ptr);

static ULONG    error_counter;  // 用于计数错误的变量
void thread_mqtt_entry(NX_IP *ip_ptr, NX_PACKET_POOL *pool_ptr)
{
    UINT status;
    NXD_ADDRESS server_ip;
    ULONG events;
    UINT topic_length, message_length;

    /* 创建 MQTT 客户端实例 */
    status = nxd_mqtt_client_create(&mqtt_client, "my_client", CLIENT_ID_STRING, STRLEN(CLIENT_ID_STRING),
                                    ip_ptr, pool_ptr, (VOID*)mqtt_client_stack, sizeof(mqtt_client_stack), 
                                    MQTT_THREAD_PRIORTY, NX_NULL, 0);
    
    if (status)
    {
        printf("Error in creating MQTT client: 0x%02x\n", status);  // 打印错误信息
        error_counter++;  // 增加错误计数器
    }
    
    /* 注册断开连接的通知函数 */
    nxd_mqtt_client_disconnect_notify_set(&mqtt_client, my_disconnect_func);
    
    /* 创建用于本示例的事件标志 */
    status = tx_event_flags_create(&mqtt_app_flag, "my app event");
    if(status)
        error_counter++;
    
    /* 设置服务器的 IP 地址 */
    server_ip.nxd_ip_version = 4;
    server_ip.nxd_ip_address.v4 = LOCAL_SERVER_ADDRESS;

    /* 开始与服务器的连接 */
    status = nxd_mqtt_client_connect(&mqtt_client, &server_ip, NXD_MQTT_PORT, 
                                     MQTT_KEEP_ALIVE_TIMER, 0, NX_WAIT_FOREVER);
    if(status)
        error_counter++;

    /* 以 QoS 等级 0 订阅主题 */
    status = nxd_mqtt_client_subscribe(&mqtt_client, TOPIC_NAME, STRLEN(TOPIC_NAME), QOS0);
    if(status)
        error_counter++;
    
    /* 设置接收通知函数 */
    status = nxd_mqtt_client_receive_notify_set(&mqtt_client, my_notify_func);
    if(status)
        error_counter++;
    
    /* 以 QoS 等级 1 发布消息 */
    status = nxd_mqtt_client_publish(&mqtt_client, TOPIC_NAME, STRLEN(TOPIC_NAME),
                                     (CHAR*)MESSAGE_STRING, STRLEN(MESSAGE_STRING), 0, QOS1, NX_WAIT_FOREVER);

    /* 等待代理发布消息 */
    tx_event_flags_get(&mqtt_app_flag, DEMO_ALL_EVENTS, TX_OR_CLEAR, &events, TX_WAIT_FOREVER);
    if(events & DEMO_MESSAGE_EVENT)
    {
        status = nxd_mqtt_client_message_get(&mqtt_client, topic_buffer, sizeof(topic_buffer), &topic_length, 
                                             message_buffer, sizeof(message_buffer), &message_length);
        if(status == NXD_MQTT_SUCCESS)
        {
            topic_buffer[topic_length] = 0;
            message_buffer[message_length] = 0;
            printf("topic = %s, message = %s\n", topic_buffer, message_buffer);  // 打印主题和消息内容
        }
    }

    /* 取消订阅主题 */
    nxd_mqtt_client_unsubscribe(&mqtt_client, TOPIC_NAME, STRLEN(TOPIC_NAME));

    /* 断开与代理的连接 */
    nxd_mqtt_client_disconnect(&mqtt_client);

    /* 删除客户端实例，释放所有资源 */
    nxd_mqtt_client_delete(&mqtt_client);
    
    return;
}

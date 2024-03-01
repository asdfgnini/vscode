#pragma once
#include <iostream>
#include <boost/asio.hpp>
using namespace boost;

//告诉编译器这只是一个函数声明，没有定义，去别处找定义，相比原来可以避免重复包含的问题
extern int client_end_point();//客户端生成端点

extern int server_end_point();//服务端生成端点

//创建socket ,分为4步 创建上下文iocontext,选择协议，生成socket,打开socket

extern int create_tcp_socket();//创建套接字，对于服务端来说，这只是监听套接字

//创建acceptor ,分为4步 创建上下文iocontext,选择协议，生成acceptor,打开acceptor

extern int create_acceptor_socket();//创建接收套接字，

//绑定acceptor，前面只是创建了socket,但没有绑定端点信息，和bind一样

extern int bind_acceptor_socket();//将端点和socket 绑定在一起

//客户端连接指定的端点，作为客户端可以连接服务器指定的端点进行连接

extern int connect_to_end();//客户端连接服务器指定的端点

//服务器接收连接，当有客户端连接时，服务器需要接收连接
extern int accept_new_aconnetion();

//关于buffer操作，任何网络库都有buffer的数据结构，buffer用来保存发送和接收时缓存数据的结构
//在asio中asio::mutable_buffer用于写服务时缓存数据，asio::const_buffer用于读服务时缓存数据
//但是asio没有直接提供操作这二个buffer的api,而是提出了MutableBufferSequence和ConstBufferSequence
//所以我们只能理解MutableBufferSequence为std::vertor<asio::mutable_buffer>,看作时多个asio::mutable_buffer
//ConstBufferSequence也是一样的

// 每个vector存储的都是mutable_buffer的地址，每个mutable_buffer的第一个字节表示数据的长度，后面跟着数据内容。
// 这么复杂的结构交给用户使用并不合适，所以asio提出了buffer()函数，该函数接收多种形式的字节流，该函数返回asio::mutable_buffers_1 o或者asio::const_buffers_1结构的对象。
// 如果传递给buffer()的参数是一个只读类型，则函数返回asio::const_buffers_1 类型对象。
// 如果传递给buffer()的参数是一个可写类型，则返回asio::mutable_buffers_1 类型对象。
// asio::const_buffers_1和asio::mutable_buffers_1是asio::mutable_buffer和asio::const_buffer的适配器，提供了符合MutableBufferSequence和ConstBufferSequence概念的接口，所以他们可以作为boost::asio的api函数的参数使用。


// 简单概括一下，我们可以用  buffer()  函数生成我们要用的缓存存储数据。


/*******************************************************/
//asio socket同步读写
//同步写有write_some、send、write
//同步读有read_some、receive、read
 
//write_some 每次向指定套接字写入固定的字节数，如果写缓冲区满了，就只写一部分，返回写入的字数
extern void write_to_socket(asio::ip::tcp::socket& sock);//同步写write_some
//send 一次性将buffer中的内容发送给对端，如果部分字节因为缓冲区满无法发送，则阻塞等待
//直到写缓冲区可用，则继续发送完成
extern int send_data_by_send();//同步写send
//write与send类似，区别在于send属于sock,write属于asio
extern int send_data_by_write();


//read_some 读取固定字节数
extern std::string read_from_socket(asio::ip::tcp::socket& sock);
extern int read_data_by_read_some();

//receive 一次性同步接收对方发送的数据
extern int read_data_by_receive();

//与receive类似，区别在于receive属于sock,read属于asio
extern int read_data_by_read();

//读取直到指定字符
extern std::string read_data_by_until(asio::ip::tcp::socket& sock);

//异步发送数据
extern int async_write_data();

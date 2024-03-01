#include "../include/endpoint.h"




int client_end_point()
{
    std::string raw_ip_address = "127.0.0.1";
    unsigned int port_num = 3333;
    boost::system::error_code ec;
    asio::ip::address ip_address = asio::ip::address::from_string(raw_ip_address,ec);
    if (ec.value() != 0)
    {
       std::cout << "failed tp parse the IP address. Error code = " << ec.value()
       << ".message: " << ec.message();
       return ec.value();
    }

    asio::ip::tcp::endpoint ep(ip_address,port_num);        

    return 0;
}

int server_end_point()
{
    unsigned short port_num = 3333;
    //这里采用IPV6协议
    asio::ip::address ip_address = asio::ip::address_v6::any();

    asio::ip::tcp::endpoint ep(ip_address,port_num);    

    return 0;
}

int create_tcp_socket()
{
    //创建iocontext
    asio::io_context ios;
    //选择协议
    asio::ip::tcp protocol = asio::ip::tcp::v4();
    //创建socket
    asio::ip::tcp::socket sock(ios);
    //打开socket
    boost::system::error_code ec;

    sock.open(protocol,ec);

    if (ec.value() != 0)
    {
        std::cout << "Fail to open the socket! Error code = "
        << ec.value() << ".message: " << ec.message();
    }
    return 0;
}

int create_acceptor_socket()
{
    //创建iocontext
    asio::io_context ios;
    //选择协议
    asio::ip::tcp protocol = asio::ip::tcp::v6();
    //创建acceptor
    asio::ip::tcp::acceptor acceptor(ios);

    //打开acceptor
    boost::system::error_code ec;
    acceptor.open(protocol,ec);

    if (ec.value() != 0)
    {
        std::cout << "Fail to open the acceptor socket!"
        << "Error code = "
        << ec.value() << " .Message: " << ec.message();
        return ec.value();
    }
    return 0;
}

int bind_acceptor_socket()
{
    //创建端点
    unsigned short port_num = 3333;
    asio::ip::tcp::endpoint ep(asio::ip::address_v4::any(),port_num);
    //创建socket
    asio::io_context ios;
    asio::ip::tcp::acceptor acceptor(ios,ep.protocol());
    //绑定，可能失败，加error_code
    boost::system::error_code ec;
    acceptor.bind(ep,ec);
    if (ec.value() != 0)
    {
        std::cout << "Fail to bind the acceptor socket."
        << "Error code = " << ec.value() << ".Message: "
        << ec.message();
    }
    
    return ec.value();
}

int connect_to_end()
{

    std::string raw_ip_address = "127.0.0.1";
    unsigned short port_num = 3333;
    try
    {
        //创建端点
        asio::ip::tcp::endpoint ep(asio::ip::address::from_string(raw_ip_address),port_num);
        //创建socket
        asio::io_context ios;
        asio::ip::tcp::socket sock(ios,ep.protocol());

        //连接服务器
        sock.connect(ep);

    }
    catch(boost::system::system_error& e)
    {
        std::cout << "Error occured! Error code = " << e.code()
        << ".Message: " << e.what();
    
        return e.code().value();
    }
    return 0;
}


int accept_new_aconnetion()
{
    //这个数值表示待定的连接请求队列容量
    const int BACKLOG_SIZE = 30;
    //创建端点
    unsigned short port_num = 3333;
    asio::ip::tcp::endpoint ep(asio::ip::address_v4::any(),port_num);

    //创建socket
    asio::io_context ios;
    try
    {
        asio::ip::tcp::acceptor acceptor(ios,ep.protocol());
        //绑定端点信息
        acceptor.bind(ep);
        //开启监听
        acceptor.listen(BACKLOG_SIZE);
        //创建监听socket
        asio::ip::tcp::socket sock(ios);
        acceptor.accept(sock);

    }
    catch(boost::system::system_error& e)
    {
        std::cout << "Error occured! Error code = " << e.code()
        << ".Message: " << e.what();

        return e.code().value();
    }
    return 0;
}

void write_to_socket(asio::ip::tcp::socket& sock)
{
    std::string buf = "hello world";
    std::size_t total_bytes_written = 0;

    while (total_bytes_written != buf.length())
    {
        total_bytes_written += sock.write_some(asio::buffer(buf.c_str() + total_bytes_written,
        buf.length() - total_bytes_written));
    }
    
}

int send_data_by_send()
{
    std::string raw_ip_address = "127.0.0.1";
    unsigned short port_num = 3333;

    try
    {
        asio::ip::tcp::endpoint ep(asio::ip::address::from_string(raw_ip_address),port_num);
        asio::io_context ios;
        asio::ip::tcp::socket sock(ios,ep.protocol());
        sock.connect(ep);
        std::string buf = "hello world";
        int send_length = sock.send(asio::buffer(buf.c_str(),buf.length()));
        if(send_length <= 0)
        {
            std::cout << "send failed" << std::endl;
        }
        return 0;
    }
    catch(boost::system::system_error& e)
    {
       std::cout << "Error occured! Error code = " << e.code() << ".Message: " << e.what();
       return e.code().value();
    }
    
}

int send_data_by_write()
{
    std::string raw_ip_address = "127.0.0.1";
    unsigned short port_num = 3333;

    try
    {
        asio::ip::tcp::endpoint ep(asio::ip::address::from_string(raw_ip_address),port_num);
        asio::io_context ios;
        asio::ip::tcp::socket sock(ios,ep.protocol());

        sock.connect(ep);

        std::string buf = "hello world";
        int send_length = asio::write(sock,asio::buffer(buf.c_str(),buf.length()));
        if (send_length <= 0)
        {
            std::cout << "send failed" << std::endl;
           
        }
        return 0;
    }
    catch(system::system_error& e)
    {
        std::cout << "Error occured! Error code = " << e.code()
        << ".Message: " << e.what();

        return e.code().value();
    }
    
}

std::string read_from_socket(asio::ip::tcp::socket& sock)
{
    const unsigned char MESSAGE_SIZE = 7;
    char buf[MESSAGE_SIZE];

    std::size_t total_bytes_read = 0;

    while (total_bytes_read != MESSAGE_SIZE)
    {
        total_bytes_read += sock.read_some(asio::buffer(buf + total_bytes_read,
        MESSAGE_SIZE -total_bytes_read));
    }
    return std::string(buf,total_bytes_read);

}

int read_data_by_read_some()
{
    std::string raw_ip_address = "127.0.0.1";
    unsigned short port_num = 3333;

    try
    {
        asio::ip::tcp::endpoint ep(asio::ip::address::from_string(raw_ip_address),port_num);
        asio::io_context ios;

        asio::ip::tcp::socket sock(ios,ep.protocol());

        sock.connect(ep);

        read_from_socket(sock);

    }
    catch(system::system_error& e)
    {
       std::cout << "Error occured! Error code = " << e.code()
       << ".Message: " << e.what();

       return e.code().value();
    }
    return 0;
}


int read_data_by_receive()
{
    std::string raw_ip_address = "127.0.0.1";
    unsigned short port_num = 3333;

    try
    {
        asio::ip::tcp::endpoint ep(asio::ip::address::from_string(raw_ip_address),port_num);
        asio::io_context ios;
        
        asio::ip::tcp::socket sock(ios,ep.protocol());

        sock.connect(ep);

        const unsigned char BUFF_SIZE = 7;
        char buffer_receive[BUFF_SIZE];

        int receive_length = sock.receive(asio::buffer(buffer_receive,BUFF_SIZE));
        if (receive_length <= 0)
        {
            std::cout << "receive failed" << std::endl;
        }
    
    }
    catch(system::system_error& e)
    {
        std::cout << "Error occured! Error code = " << e.code()
        << ".Message: " << e.what();
        return e.code().value();
    }
    return 0;
}


 int read_data_by_read()
 {
    std::string raw_ip_address = "127.0.0.1";
    unsigned short port_num = 3333;


    try
    {
        asio::ip::tcp::endpoint ep(asio::ip::address::from_string(raw_ip_address),port_num);
        asio::io_context ios;

        asio::ip::tcp::socket sock(ios,ep.protocol());

        sock.connect(ep);

        const unsigned char BUFF_SIZE = 7;
        char buffer_read[BUFF_SIZE];

        int read_length = asio::read(sock,asio::buffer(buffer_read,BUFF_SIZE));
        if (read_length <= 0)
        {
            std::cout << "read failed" << std::endl;
        }
    }
    catch(system::system_error& e)
    {
        std::cout << "Error occured! Error code = " << e.code()
        << ".Message: " << e.what();

        return e.code().value();
    }
    return 0;
 }


 std::string read_data_by_until(asio::ip::tcp::socket& sock)
 {
    asio::streambuf buf;

    asio::read_until(sock,buf,'\n');

    std::string message;

    std::istream input_stream(&buf);
    std::getline(input_stream,message);
    
    return message;
 }


//  int async_write_data()
//  {
//     std::string raw_ip_address = "127.0.0.1";
//     unsigned short port_num = 3333;

//     try
//     {
//         asio::ip::tcp::endpoint ep(asio::ip::address::from_string(raw_ip_address),port_num);
//         asio::io_context iox;
//         auto socket_ptr = std::make_shared<asio::ip::tcp::socket>(iox,ep.protocol());
//         auto session_ptr = std::make_shared<Session>


//     }
//     catch(const std::exception& e)
//     {
//         std::cerr << e.what() << '\n';
//     }
    


//  }
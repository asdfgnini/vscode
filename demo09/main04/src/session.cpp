#include "../include/session.h"

void Session::start()
{
    memset(data,0,max_length);
    sock.async_read_some(asio::buffer(data,max_length),
        std::bind(&Session::hand_read,this,std::placeholders::_1,std::placeholders::_2));
}
void Session::hand_read(const boost::system::error_code& error,size_t bytes_transfered)
{
    if (!error)
    {
        std::cout << "receive data is: " << data << std::endl;
        asio::async_write(sock,asio::buffer(data,bytes_transfered),
            std::bind(&Session::hand_write,this,std::placeholders::_1));
    }
    else
    {
        delete this;
    }
}

void Session::hand_write(const boost::system::error_code& error)
{
    if (!error)
    {
        memset(data,0,max_length);
        sock.async_read_some(boost::asio::buffer(data,max_length),
            std::bind(&Session::hand_read,this,std::placeholders::_1,std::placeholders::_2));
    }
}

void Server::start_accept()
{
    Session* new_session = new Session(_ioc);
    acceptor.async_accept(new_session->get_socket(),std::bind(&Server::hand_accept,this,new_session,std::placeholders::_1));

}

Server::Server(asio::io_context& ioc,unsigned short port_num):_ioc(ioc)
,acceptor(ioc,asio::ip::tcp::endpoint(asio::ip::tcp::v4(),port_num))
{
    start_accept();
}



 void Server::hand_accept(Session* new_session,const boost::system::error_code& error)
 {
    if (!error)
    {
        new_session->start();
    }
    else
    {
        delete new_session;
    }
    
    start_accept();
 }
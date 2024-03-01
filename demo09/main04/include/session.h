#pragma once
#include <boost/asio.hpp>
#include <iostream>
using namespace boost;

class Session{

public:

    Session(asio::io_context& ioc):sock(ioc){};

    asio::ip::tcp::socket& get_socket()
    {
        return sock;
    }

    void start();
    void hand_read(const boost::system::error_code& error,size_t bytes_transfered);
    void hand_write(const boost::system::error_code& error);

private:
    enum{max_length = 1024};
    asio::ip::tcp::socket sock;
    char data[max_length];
};




    
class Server{

public:
    Server(asio::io_context& ioc,unsigned short port_num);

private:
    void start_accept();
    void hand_accept(Session* new_session,const boost::system::error_code& error);

    asio::io_context& _ioc;
    asio::ip::tcp::acceptor acceptor;

};







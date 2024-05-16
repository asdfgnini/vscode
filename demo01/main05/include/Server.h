#pragma once

//asio 中首先有个acceptor的概念,然后是Session（会话的概念）

#include <boost/asio.hpp>
#include <iostream>
using namespace boost;
#include "Session.h"
#include <map>


class Server
{
private:
    asio::ip::tcp::acceptor _acceptor;
    asio::io_context& _ioc;
    unsigned short port_num;

    void start_Accept();
    void hand_accept(std::shared_ptr<Session>,boost::system::error_code& error);
    std::map<std::string,std::shared_ptr<Session>> _session;

public:
    Server(asio::io_context& ioc,unsigned short port);
    ~Server();
    void clearSession(std::string uuid);
};


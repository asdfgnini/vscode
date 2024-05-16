#pragma once

#include <boost/asio.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
using namespace boost;
class Server;

class Session
{
private:
    asio::ip::tcp::socket _sock;
    Server* _server;
    std::string _uuid;
    enum{MAX_LENGTH = 1024};
    char data[MAX_LENGTH];
    void hand_read(system::error_code& error,size_t bytes_transfer);
    void hand_write(system::error_code& error);
    
    
public:
    Session(asio::io_context& ioc,Server* server);
    ~Session();

    asio::ip::tcp::socket& Get_socket();
    std::string& Get_uuid();
    void start();



};

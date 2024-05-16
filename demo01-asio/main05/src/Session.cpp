#include "../include/Session.h"
#include "../include/Server.h"

Session::Session(asio::io_context& ioc,Server* server):_sock(ioc),_server(server)
{
    boost::uuids::uuid a_uuid =  boost::uuids::random_generator()();
    _uuid = boost::uuids::to_string(a_uuid);
}

Session::~Session()
{


}

asio::ip::tcp::socket& Session::Get_socket()
{
    return _sock;
}

std::string& Session::Get_uuid()
{
    return _uuid;
}

void Session::start()
{
    memset(data,0,MAX_LENGTH);
    _sock.async_read_some(asio::buffer(data,MAX_LENGTH),std::bind(&Session::hand_read,this,std::placeholders::_1,std::placeholders::_2));
}
 
 
void Session::hand_read(system::error_code& error,size_t bytes_transfer)
{
    if (!error)
    {
       std::cout << "read data is " << data << std::endl;
       asio::async_write(_sock,asio::buffer(data,bytes_transfer),std::bind(&Session::hand_write,this,std::placeholders::_1));
    }
    else
    {
        std::cout << "Hand_read failed,error is " << error.what() << std::endl;
        _server->clearSession(_uuid);

    }
}
void Session::hand_write(system::error_code& error)
{


}


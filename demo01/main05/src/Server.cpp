#include "../include/Server.h"



Server::Server(asio::io_context& ioc,unsigned short port):_ioc(ioc),port_num(port)
,_acceptor(ioc,asio::ip::tcp::endpoint(asio::ip::tcp::v4(),port_num))
{
    start_Accept();
}

Server::~Server()
{

}

void Server::start_Accept()
{
    //建立一个会话
    std::shared_ptr<Session> new_session = std::make_shared<Session>(_ioc,this);

    //开始监听
    _acceptor.async_accept(new_session->Get_socket(),std::bind(&Server::hand_accept,this,new_session,std::placeholders::_1));
        
}

void Server::hand_accept(std::shared_ptr<Session> new_session,boost::system::error_code& error)
{
    if (!error)
    {
        new_session->start();
        _session.insert(std::make_pair(new_session->Get_uuid(),new_session));
    }
    else 
    {
        std::cout << "session accept failed, error is " << error.what() << std::endl;
    }

    start_Accept();
}

void Server::clearSession(std::string uuid)
{
    _session.erase(uuid);
}

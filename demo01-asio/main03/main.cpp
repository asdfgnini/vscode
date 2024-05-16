#include <iostream>
#include <boost/asio.hpp>
#include <set>
using namespace boost;

const int max_length = 1024;
typedef std::shared_ptr<asio::ip::tcp::socket> socket_ptr;
std::set<std::shared_ptr<std::thread>> thread_set;

void session(socket_ptr sock)
{
    try
    {
        for(;;)
        {
            char data[max_length];
            memset(data,'\0',max_length);
            boost::system::error_code error;
            size_t length = sock->read_some(boost::asio::buffer(data,max_length));
            if (error == boost::asio::error::eof)
            {
                std::cout << "connection closed by peer" << std::endl;
                break;
            }
            else if (error)
            {
                throw boost::system::system_error(error);
            }
            std::cout << "receive from " << sock->remote_endpoint().address().to_string() << std::endl;
            std::cout << "receive message is " << data << std::endl;
            boost::asio::write(*sock,boost::asio::buffer(data,length));  
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

void server(asio::io_context& io_context,unsigned short port)
{
    asio::ip::tcp::acceptor a(io_context,asio::ip::tcp::endpoint(asio::ip::tcp::v4(),port));
    for(;;)
    {
        socket_ptr socket(new asio::ip::tcp::socket(io_context));
        a.accept(*socket);
        //构造子线程
        auto t = std::make_shared<std::thread>(session,socket);
        thread_set.insert(t);
    }
}

int main()
{
    try
    {
        asio::io_context ioc;
        server(ioc,10086);
        for(auto& t:thread_set)
        {
            t->join();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}



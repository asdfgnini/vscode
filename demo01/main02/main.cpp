
#include <iostream>
#include <boost/asio.hpp>
using namespace boost;
const int MAX_LENGTH = 1024;

int main()  
{
    try
    {
        std::string raw_ip_address = "127.0.0.1";
        unsigned short port_num = 10086;

        asio::ip::tcp::endpoint ep(asio::ip::address::from_string(raw_ip_address),port_num);

        asio::io_context ios;

        asio::ip::tcp::socket sock(ios);
        boost::system::error_code ec;

        sock.connect(ep,ec);
        if (ec.value() != 0)
        {
            std::cout << "Error Occured! Error code = " << ec.value()
            << ".Message: " << ec.message();
        }


        //同步写
        std::cout << "Enter message: ";
        char request[MAX_LENGTH];
        std::cin.getline(request,MAX_LENGTH);
        size_t request_length = strlen(request);
        asio::write(sock,asio::buffer(request,request_length));


        //同步读
        char reply[MAX_LENGTH];
        size_t reply_length = asio::read(sock,asio::buffer(reply,request_length));

        std::cout << "Reply is: ";
        std::cout.write(reply,reply_length);
        std::cout << "\n";
        getchar();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}
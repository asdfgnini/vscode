#include "../include/endpoint.h"
#include <boost/asio.hpp>
using namespace boost;

int client_end_point()
{
    std::string raw_ip_address = "";
    unsigned int port_num = 3333;
    boost::system::error_code ec;
    asio::ip::address ip_address = asio::ip::address::from_string(raw_ip_address,ec);
    if (ec.value() != 0)
    {
        /* code */
    }
    
    return 0;
}



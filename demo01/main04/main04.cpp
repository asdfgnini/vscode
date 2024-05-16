
#include <iostream>
#include "./include/session.h"

//异步服务器
int main()
{
    try
    {
        asio::io_context ioc;
        Server S(ioc,10086);
        ioc.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
   


    return 0;
}
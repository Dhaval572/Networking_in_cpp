#include <asio.hpp>
#include <iostream>

int main()
{
    asio::io_context io;
    std::cout << "Standalone Asio is working!\n";   

    [[maybe_unused]]int a;
        
    return 0;
}
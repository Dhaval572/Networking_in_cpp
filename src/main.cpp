#include <asio.hpp>
#include <iostream>

int main()
{
    asio::io_context io;
    std::cout << "Standalone Asio is working!\n";
    return 0;
}
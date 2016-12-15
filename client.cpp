#include "src/client.h"

int main(int argc, char* argv[])
{
    try
    {
        if(argc == 1)
        {
            Client c;
            c.run();
        }
        else if(argc == 3)
        {
            boost::asio::io_service io_service;

            boost::asio::ip::tcp::resolver resolver(io_service);
            auto endpoint_iterator = resolver.resolve({ argv[1], argv[2] });

            Client c(io_service, endpoint_iterator);
            std::thread t([&io_service](){ io_service.run(); });
            c.run();
            t.join();
        }
        else
        {
            std::cerr << "Usage: client\n";
            std::cerr << "       client <host> <port>\n";
            return 1;
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}

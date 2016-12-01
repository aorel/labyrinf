#include "src/client.h"

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 3)
        {
            std::cerr << "Usage: chat_client <host> <port>\n";
            return 1;
        }

        boost::asio::io_service io_service;

        boost::asio::ip::tcp::resolver resolver(io_service);
        auto endpoint_iterator = resolver.resolve({ argv[1], argv[2] });


        /*
        Chat_client chat_client(io_service, endpoint_iterator);

        std::thread t([&io_service](){ io_service.run(); });

        char line[Message::max_body_length + 1];
        while (std::cin.getline(line, Message::max_body_length + 1))
        {
            Message msg;
            msg.body_length(std::strlen(line));
            std::memcpy(msg.body(), line, msg.body_length());
            msg.encode_header();
            chat_client.write(msg);
        }

        chat_client.close();
        t.join();
        */


        Client c(io_service, endpoint_iterator);
        std::thread t([&io_service](){ io_service.run(); });
        c.run();
        t.join();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}

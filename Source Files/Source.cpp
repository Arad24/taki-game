#include <iostream>
#include <memory>
# include "../Infrastructure/Header Files/Server.h"

int main()
{
    try
    {
        auto db = std::make_shared<SqliteDatabase>();
        auto md_server = std::make_unique<Server>(db);
        std::thread serverThread(&Server::run, md_server.get());
        serverThread.join();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error occurred: " << e.what() << std::endl;
    }

    return 0;
}
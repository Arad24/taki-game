# include "../Header Files/Server.h"

Server::Server(std::shared_ptr<IDatabase> db) : m_handlerFactory(db), m_communicator(m_handlerFactory)
{
	m_database = db;
}

void Server::run()
{
	std::thread(&Communicator::startHandleRequests, &m_communicator).detach();

	getAdminCommands();
}

void Server::getAdminCommands()
{
	std::string command = "";
	while (toLower(command) != toLower(EXIT_COMMAND))
	{
		std::cin >> command;
	}

	std::cout << "Exit.";
}

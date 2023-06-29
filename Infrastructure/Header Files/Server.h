#pragma once
# include "Communicator.h"
# include <string>
# include "../../UsefullFunctions/Header Files/stringFuncs.h"
# include "../../Infrastructure/Header Files/SqliteDatabase.h"
# include <iostream>

# define EXIT_COMMAND "EXIT"

class Server
{
	public:
		Server(std::shared_ptr<IDatabase> db);
		void run();

	private:
		std::shared_ptr<IDatabase> m_database;
		RequestHandlerFactory m_handlerFactory;
		Communicator m_communicator;

		void getAdminCommands();
};
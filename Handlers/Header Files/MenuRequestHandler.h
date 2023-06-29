#pragma once
#include "IRequestHandler.h"
# include "../../UsefullFunctions/Header Files/stringFuncs.h"
# include "../../Infrastructure/Header Files/RequestHandlerFactory.h"
# include <thread>
# include <chrono>

// Forward declarations
class RequestHandlerFactory;

std::vector<int> click;

class MenuRequestHandler : public IRequestHandler
{
	public:
		MenuRequestHandler(RequestHandlerFactory& handlerFactory, RoomManager& roomManager, StatisticsManager& statisticsManager, LoggedUser user);

		bool isRequestRelevant(RequestInfo rInfo) override;
		RequestResult handleRequest(RequestInfo rInfo) override;

	private:
		LoggedUser m_user;
		RoomManager& m_roomManager;
		StatisticsManager& m_statisticsManager;
		RequestHandlerFactory& m_handlerFactory;
		

		RequestResult signout(RequestInfo);
		RequestResult getRooms(RequestInfo);
		RequestResult getPlayersInRoom(RequestInfo);
		RequestResult getPersonalStats(RequestInfo);
		RequestResult getHighScore(RequestInfo);
		RequestResult joinRoom(RequestInfo);
		RequestResult createRoom(RequestInfo);


		void printClick();
};


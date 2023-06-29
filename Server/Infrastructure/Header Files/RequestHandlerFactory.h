# pragma once
#include <memory>
# include "IDatabase.h"
#include "../../Managers/Header Files/LoginManager.h"
#include "../../Managers/Header Files/StatisticsManager.h"
#include "../../Managers/Header Files/RoomManager.h"
#include "../../Request/Header Files/JsonRequestPacketDeserializer.h"
#include "../../Request/Header Files/JsonResponsePacketSerializer.h"
# include "../../Handlers/Header Files/LoginRequestHandler.h"
# include "../../Handlers/Header Files/MenuRequestHandler.h"
# include "../../Handlers/Header Files/RoomAdminRequestHandler.h"
# include "../../Handlers/Header Files/RoomMemberRequestHandler.h"
# include "../../Handlers/Header Files/GameRequestHandler.h"
# include "../../Managers/Header Files/GameManager.h"

// Forward declarations
class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class GameRequestHandler;


class RequestHandlerFactory
{
	public:
		RequestHandlerFactory(std::shared_ptr<IDatabase> db);

		// Login
		std::shared_ptr<LoginRequestHandler> createLoginRequestHandler();
		LoginManager& getLoginManager();

		// Menu & Room
		std::shared_ptr<MenuRequestHandler> createMenuRequestHandler(std::string username);
		RoomManager& getRoomManager();

		// Statistics
		StatisticsManager& getStatisticsManager();

		// Waiting room
		std::shared_ptr<RoomAdminRequestHandler> createRoomAdminRequestHandler(Room room, LoggedUser user);
		std::shared_ptr<RoomMemberRequestHandler> createRoomMemberRequestHandler(Room room, LoggedUser user);
		std::shared_ptr<GameRequestHandler> createGameRequestHandler(Game game, LoggedUser user);
		std::shared_ptr<GameRequestHandler> createGameRequestHandler(Room room, LoggedUser user);

	private:
		std::shared_ptr<IDatabase> m_database;
		LoginManager m_loginManager;
		RoomManager m_roomManager;
		StatisticsManager m_statisticsManager;
		GameManager m_gameManager;
};
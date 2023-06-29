# include "../Header Files/MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactory, RoomManager& roomManager, StatisticsManager& statisticsManager, LoggedUser user)
	: m_handlerFactory(handlerFactory), m_roomManager(roomManager), m_statisticsManager(statisticsManager), m_user(user) 
{
	click.push_back(0); // Join room
	click.push_back(0); // Create room
	click.push_back(0); // High score 

	std::thread t(&MenuRequestHandler::printClick, this);
	t.detach();
}

void MenuRequestHandler::printClick()
{
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		std::cout << "Click: " << click.at(0) << ", " << click.at(1) << ", " << click.at(2) << std::endl;
	}
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo rInfo)
{
	return (rInfo.id >= '3' && rInfo.id <= '9');
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo rInfo)
{
	if (isRequestRelevant(rInfo))
	{
		RequestResult res;
		switch (rInfo.id)
		{
			case LOGOUT_CODE:
				res = signout(rInfo);
				break;

			case GETROOMS_CODE:
				res = getRooms(rInfo);
				break;

			case JOINROOM_CODE:
				res = joinRoom(rInfo);
				break;

			case CREATEROOM_CODE:
				res = createRoom(rInfo);
				break;

			case PLAYERSINROOM_CODE:
				res = getPlayersInRoom(rInfo);
				break;

			case HIGHSCORE_CODE:
				res = getHighScore(rInfo);
				break;

			case PERSONALSTATS_CODE:
				res = getPersonalStats(rInfo);
				break;

			default:
				ErrorResponse res = { "Invalid Request" };
				return { JsonResponsePacketSerializer::SerializeResponse(res), nullptr };
				break;
		}

		return res;
	}
	else
	{
		ErrorResponse res = { "Invalid Request" };
		return { JsonResponsePacketSerializer::SerializeResponse(res), nullptr };
	}
}


RequestResult MenuRequestHandler::signout(RequestInfo rInfo)
{
	try
	{
		m_handlerFactory.getLoginManager().logout(m_user.getUsername());

		LogoutResponse res = { SUCCESS };
		return { JsonResponsePacketSerializer::SerializeResponse(res), m_handlerFactory.createLoginRequestHandler() };
	}
	catch (std::exception& e)
	{
		ErrorResponse res = { e.what() };
		return { JsonResponsePacketSerializer::SerializeResponse(res), nullptr };
	}
	
}


RequestResult MenuRequestHandler::getRooms(RequestInfo rInfo)
{
	try
	{
		GetRoomsResponse res = { SUCCESS, m_roomManager.getRooms() };
		return { JsonResponsePacketSerializer::SerializeResponse(res), std::make_shared<MenuRequestHandler>(*this) };
	}
	catch (std::exception& e)
	{
		ErrorResponse res = { e.what() };
		return { JsonResponsePacketSerializer::SerializeResponse(res), nullptr };
	}
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo rInfo)
{
	try
	{
		GetPlayersInRoomRequest req = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(rInfo.buffer);
		auto room = m_roomManager.getRoomById(req.roomId);
		GetPlayersInRoomResponse res = { room->getAllUsers() };

		return { JsonResponsePacketSerializer::SerializeResponse(res), m_handlerFactory.createMenuRequestHandler(m_user.getUsername()) };
	}
	catch (std::exception& e)
	{
		ErrorResponse res = { e.what() };
		return { JsonResponsePacketSerializer::SerializeResponse(res), nullptr };
	}
	
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo rInfo)
{
	try
	{
		getPersonalStatsResponse res = { SUCCESS, m_statisticsManager.getUserStats(m_user.getUsername()) };

		return { JsonResponsePacketSerializer::SerializeResponse(res), m_handlerFactory.createMenuRequestHandler(m_user.getUsername()) };
	}
	catch (std::exception& e)
	{
		ErrorResponse res = { e.what() };
		return { JsonResponsePacketSerializer::SerializeResponse(res), nullptr };
	}
	
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo rInfo)
{
	getHighScoreResponse res = { SUCCESS, m_statisticsManager.getHighScore() };

	click.at(2)++;
	return { JsonResponsePacketSerializer::SerializeResponse(res), m_handlerFactory.createMenuRequestHandler(m_user.getUsername()) };
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo rInfo)
{
	try
	{
		JoinRoomRequest req = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(rInfo.buffer);
		m_roomManager.getRoomById(req.roomId)->addUser(m_user);

		JoinRoomResponse res = { SUCCESS };
		click.at(0)++;
		return { JsonResponsePacketSerializer::SerializeResponse(res), m_handlerFactory.createRoomMemberRequestHandler(*m_roomManager.getRoomById(req.roomId), m_user) };
	}
	catch (std::exception& e)
	{
		ErrorResponse res = { e.what() };
		return { JsonResponsePacketSerializer::SerializeResponse(res), nullptr };
	}
	
}

RequestResult MenuRequestHandler::createRoom(RequestInfo rInfo)
{
	try
	{
		CreateRoomRequest req = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(rInfo.buffer);
		
		auto rd = m_roomManager.createRoom(m_user, req.roomName, req.maxUsers, req.answerTimeout);
		
		CreateRoomResponse res = CreateRoomResponse();
		res.roomId = rd.id;
		res.status = SUCCESS;
		click.at(1)++;
		return { JsonResponsePacketSerializer::SerializeResponse(res), m_handlerFactory.createRoomAdminRequestHandler(*m_roomManager.getRoomById(rd.id), m_user) };
	}
	catch (std::exception& e)
	{
		ErrorResponse res = { e.what()};
		return { JsonResponsePacketSerializer::SerializeResponse(res), nullptr };
	}
	
}
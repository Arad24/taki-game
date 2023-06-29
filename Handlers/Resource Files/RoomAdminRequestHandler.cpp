# include "../Header Files/RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, RoomManager& roomManager, Room room, LoggedUser user) :
	m_handlerFactory(handlerFactory), m_roomManager(roomManager), m_room(room), m_user(user) {}


bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo rInfo)
{
	return rInfo.id >= CLOSEROOM_CODE && rInfo.id <= GETROOMSTATE_CODE;
}


RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo rInfo)
{
	if (isRequestRelevant(rInfo))
	{
		RequestResult res;

		switch (rInfo.id)
		{
			case CLOSEROOM_CODE:
				res = closeRoom(rInfo);

				break;

			case STARTGAME_CODE:
				res = startGame(rInfo);
				break;

			case GETROOMSTATE_CODE:
				res = getRoomState(rInfo);
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

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo rInfo)
{
	try
	{
		m_roomManager.deleteRoom(m_room.getID());
		CloseRoomResponse res = { SUCCESS };

		return { JsonResponsePacketSerializer::SerializeResponse(res), m_handlerFactory.createMenuRequestHandler(m_user.getUsername()) };
	}
	catch (std::exception& e)
	{
		ErrorResponse res = { e.what() };
		return { JsonResponsePacketSerializer::SerializeResponse(res), nullptr };
	}
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo rInfo)
{
	try
	{
		m_roomManager.getRoomById(m_room.getID())->setRoomState(INGAME_STATE);
		StartGameResponse res = { SUCCESS };

		return { JsonResponsePacketSerializer::SerializeResponse(res), m_handlerFactory.createGameRequestHandler(*(m_roomManager.getRoomById(m_room.getID())), m_user) };
	}
	catch (std::exception& e)
	{
		ErrorResponse res = { e.what() };
		return { JsonResponsePacketSerializer::SerializeResponse(res), nullptr };
	}
}


RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo rInfo)
{
	try
	{
		GetRoomStateResponse res = GetRoomStateResponse();
		

		res.hasGameBegun = m_roomManager.getRoomState(m_room.getID());
		res.players = m_roomManager.getRoomById(m_room.getID())->getAllUsers();
		res.status = SUCCESS;

		return { JsonResponsePacketSerializer::SerializeResponse(res), nullptr };
	}
	catch (std::exception& e)
	{
		ErrorResponse res = { e.what() };
		return { JsonResponsePacketSerializer::SerializeResponse(res), nullptr };
	}
}
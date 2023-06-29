# include "../Header Files/RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, RoomManager& roomManager, Room room, LoggedUser user) :
	m_handlerFactory(handlerFactory), m_roomManager(roomManager), m_room(room), m_user(user) {}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo rInfo)
{
	return rInfo.id >= GETROOMSTATE_CODE && rInfo.id <= LEAVEROOM_CODE;
}


RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo rInfo)
{
	if (isRequestRelevant(rInfo))
	{
		RequestResult res;
		switch (rInfo.id)
		{
			case GETROOMSTATE_CODE:
				res = getRoomState(rInfo);
				break;

			case LEAVEROOM_CODE:
				res = leaveRoom(rInfo);
				break;

		default:
			ErrorResponse res = { "Invalid Request" };
			return { JsonResponsePacketSerializer::SerializeResponse(res),  m_handlerFactory.createMenuRequestHandler(m_user.getUsername()) };
			break;
		}

		return res;
	}
	else
	{
		ErrorResponse res = { "Invalid Request" };
		return { JsonResponsePacketSerializer::SerializeResponse(res),  m_handlerFactory.createMenuRequestHandler(m_user.getUsername()) };
	}
}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo rInfo)
{
	try
	{
		m_roomManager.getRoomById(m_room.getID())->removeUser(m_user);

		LogoutResponse res = { SUCCESS };
		return { JsonResponsePacketSerializer::SerializeResponse(res), m_handlerFactory.createMenuRequestHandler(m_user.getUsername())};
	}
	catch (std::exception& e)
	{
		ErrorResponse res = { e.what() };
		return { JsonResponsePacketSerializer::SerializeResponse(res), nullptr };
	}
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo rInfo)
{
	try
	{
		GetRoomStateResponse res = GetRoomStateResponse();


		res.hasGameBegun = m_roomManager.getRoomState(m_room.getID());
		res.players = m_roomManager.getRoomById(m_room.getID())->getAllUsers();
		res.status = SUCCESS;

		if (res.hasGameBegun == INGAME)
		{
			return { JsonResponsePacketSerializer::SerializeResponse(res), m_handlerFactory.createGameRequestHandler(*m_roomManager.getRoomById(m_room.getID()), m_user) };
		}
		
		return { JsonResponsePacketSerializer::SerializeResponse(res), nullptr };
	}
	catch (std::exception& e)
	{
		ErrorResponse res = { e.what() };
		return { JsonResponsePacketSerializer::SerializeResponse(res),  m_handlerFactory.createMenuRequestHandler(m_user.getUsername()) };
	}
}
#pragma once
# include "IRequestHandler.h"
# include "../../UsefullFunctions/Header Files/stringFuncs.h"
# include "../../Infrastructure/Header Files/RequestHandlerFactory.h"

// Forward declarations
class RequestHandlerFactory;

class RoomMemberRequestHandler : public IRequestHandler
{
	public:
		RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, RoomManager& roomManager, Room room, LoggedUser user);
		bool isRequestRelevant(RequestInfo) override;
		RequestResult handleRequest(RequestInfo) override;

	private:
		Room m_room;
		LoggedUser m_user;
		RoomManager& m_roomManager;
		RequestHandlerFactory& m_handlerFactory;

		RequestResult leaveRoom(RequestInfo);
		RequestResult getRoomState(RequestInfo);
};
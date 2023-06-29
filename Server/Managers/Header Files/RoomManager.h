# pragma once
# include <map>
# include "Room.h"

# define CLOSED  0
# define WAITING 1
# define INGAME	 2


class RoomManager
{
	public:
		RoomData createRoom(LoggedUser user, std::string name, unsigned int maxPlayers, unsigned int answerTimeOut);
		void deleteRoom(int id);
		unsigned int getRoomState(int ID);
		std::vector<RoomData> getRooms();
		std::shared_ptr<Room> getRoomById(unsigned int id);
		RoomManager getRoomManager();

	private:
		std::map<unsigned int, std::shared_ptr<Room>> m_rooms; // <Room id, Room>

		unsigned int randId();
		bool roomExist(unsigned int roomId);
		RoomData createRoomData(std::string name, unsigned int maxPlayers, unsigned int answerTimeOut);
}; ;
;
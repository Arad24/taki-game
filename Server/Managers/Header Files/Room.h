# pragma once
# include "LoggedUser.h"
# include "../../Request/Header Files/json.hpp"
# include <vector>

# define WAIT_STATE    1
# define INGAME_STATE  2
# define OFFLINE_STATE 0

typedef struct RoomData
{
	unsigned int id;
	std::string name;
	unsigned int currPlayers;
	unsigned int maxPlayers;
	unsigned int timePerPlay = 15;
	unsigned int isActive;
	

	nlohmann::json toJson() const
	{
		nlohmann::json js = {
			{"id", id},
			{"name", name},
			{"maxPlayers", maxPlayers},
			{"timePerPlay", timePerPlay},
			{"isActive", isActive},
			{"currPlayers", currPlayers},
		};
		return js;
	}
} RoomData;


class Room
{
public:
    Room();
	Room(LoggedUser roomOwner, RoomData roomData);
    void addUser(LoggedUser);
    void removeUser(LoggedUser);
    std::vector<std::string> getAllUsers();
    RoomData getRoomData();
	unsigned int getID();
	void setRoomState(unsigned int roomState);
	std::vector<LoggedUser> getUsers();

private:
    RoomData m_metadata;
    std::vector<LoggedUser> m_users;

    void copyData(RoomData roomData);
};
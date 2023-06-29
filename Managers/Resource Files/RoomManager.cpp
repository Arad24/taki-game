# include "../Header Files/RoomManager.h"

RoomManager RoomManager::getRoomManager()
{
    return *this;
}

RoomData RoomManager::createRoom(LoggedUser user, std::string name, unsigned int maxPlayers, unsigned int answerTimeOut)
{
    RoomData rm = createRoomData(name, maxPlayers, answerTimeOut);
    auto room = std::make_shared<Room>(user, rm);
    this->m_rooms.insert({ rm.id, room });

    return rm;
}

void RoomManager::deleteRoom(int id)
{
    this->m_rooms.erase(id);
}

unsigned int RoomManager::getRoomState(int id)
{
    if (m_rooms.find(id) == m_rooms.end())
    {
        return CLOSED;
    }
    else
    {
        return this->m_rooms[id]->getRoomData().isActive;
    }
    
}

std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> rooms;

    for (auto const& i : m_rooms)
    {
        auto room = i.second;
        rooms.emplace_back(room->getRoomData());
    }

    return rooms;
}


std::shared_ptr<Room> RoomManager::getRoomById(unsigned int id)
{
    auto it = this->m_rooms.find(id);

    if (it != this->m_rooms.end()) 
    {
        return (it->second); 
    }
    else throw std::out_of_range("Room with the specified id not found");
}

bool RoomManager::roomExist(unsigned int roomId)
{
    return (this->m_rooms.find(roomId) != this->m_rooms.end());
}

unsigned int RoomManager::randId()
{
    bool exist = true;
    unsigned int id = 0;
    const unsigned int min = 0, max = 9999;

    while (exist)
    {
        id = rand() % (max - min + 1) + min;

        exist = roomExist(id);
    }

    return id;
}

RoomData RoomManager::createRoomData(std::string name, unsigned int maxPlayers, unsigned int answerTimeOut)
{
    RoomData rd = RoomData();

    rd.id = randId();
    rd.isActive = 1;
    rd.maxPlayers = maxPlayers;
    rd.name = name;
    rd.timePerPlay = answerTimeOut;

    return rd;
}
# include "../Header Files/Room.h"

Room::Room() {}

Room::Room(LoggedUser roomOwner, RoomData roomData)
{
    this->m_users.push_back(roomOwner);
    this->m_metadata.currPlayers = 1;

    copyData(roomData);
}

void Room::addUser(LoggedUser user)
{
    m_users.push_back(user);
    this->m_metadata.currPlayers++;
}

unsigned int Room::getID()
{
    return m_metadata.id;
}

void Room::removeUser(LoggedUser user)
{

    auto& vec = m_users;
    vec.erase(std::remove_if(vec.begin(), vec.end(), [&user](LoggedUser& currUser) 
    {
        return currUser.getUsername() == user.getUsername();
    }), vec.end());

    this->m_metadata.currPlayers--;

}

std::vector<LoggedUser> Room::getUsers()
{
    return m_users;
}

std::vector<std::string> Room::getAllUsers()
{   
    std::vector<std::string> users;

    for (auto& user : m_users)
    {
        users.push_back(user.getUsername());
    }

    return users;
}

RoomData Room::getRoomData()
{
    return this->m_metadata;
}

void Room::setRoomState(unsigned int roomState)
{
    this->m_metadata.isActive = roomState;
}

void Room::copyData(RoomData roomData)
{
    this->m_metadata.id = roomData.id;
    this->m_metadata.isActive = roomData.isActive;
    this->m_metadata.maxPlayers = roomData.maxPlayers;
    this->m_metadata.timePerPlay = roomData.timePerPlay;
    this->m_metadata.name = roomData.name;
}
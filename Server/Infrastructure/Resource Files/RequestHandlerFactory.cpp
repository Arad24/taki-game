# include "../Header Files/RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(std::shared_ptr<IDatabase> db) : m_loginManager(db), m_statisticsManager(db), m_roomManager(), m_gameManager(db)
{
    m_database = db;
}

std::shared_ptr<LoginRequestHandler> RequestHandlerFactory::createLoginRequestHandler()
{
    return std::make_shared<LoginRequestHandler>(*this);
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return m_loginManager;
}

std::shared_ptr<MenuRequestHandler> RequestHandlerFactory::createMenuRequestHandler(std::string username)
{
    return std::make_shared<MenuRequestHandler>(std::ref(*this), std::ref(m_roomManager), std::ref(m_statisticsManager), LoggedUser(username));
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
    return m_roomManager;
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
    return m_statisticsManager;
}

std::shared_ptr<RoomAdminRequestHandler> RequestHandlerFactory::createRoomAdminRequestHandler(Room room, LoggedUser user)
{
    return std::make_shared<RoomAdminRequestHandler>(std::ref(*this), std::ref(m_roomManager), room, user);
}

std::shared_ptr<RoomMemberRequestHandler> RequestHandlerFactory::createRoomMemberRequestHandler(Room room, LoggedUser user)
{
    return std::make_shared<RoomMemberRequestHandler>(std::ref(*this), std::ref(m_roomManager), room, user);
}

std::shared_ptr<GameRequestHandler> RequestHandlerFactory::createGameRequestHandler(Room room, LoggedUser user)
{
    try
    {
        return std::make_shared<GameRequestHandler>(std::ref(*this), std::ref(m_gameManager), user, *m_gameManager.getGameById(room.getID()));
    }
    catch (...)
    {
        return std::make_shared<GameRequestHandler>(std::ref(*this), std::ref(m_gameManager), user, m_gameManager.createGame(room));
    }
    
}
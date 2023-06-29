# include "../Header Files/GameManager.h"

GameManager::GameManager(std::shared_ptr<IDatabase> db) : m_database(db) 
{}

Game GameManager::createGame(Room room)
{
	auto users = room.getUsers();
	auto game = std::make_shared<Game>(*users.begin(), users, room.getID());

	this->m_games.push_back(game);

	return *game;
}

void GameManager::deleteGame(unsigned int id)
{
	for (auto it = begin(m_games); it != end(m_games); ++it) 
	{
		if (it->get()->getId() == id)
		{
			m_games.erase(it);
			break;
		}
	}
}


std::shared_ptr<Game> GameManager::getGameById(unsigned int id)
{
	for (auto game : m_games)
	{
		if (game->getId() == id) return game;
	}

	throw std::exception("Game not found");
}


void GameManager::addGameResults(unsigned int gameId, std::string username)
{
	auto game = getGameById(gameId);
	auto players = game->getPlayers();

	for (const auto& player : players)
	{
		if (player.username == username) m_database->addUserResult(player.username, player.cardsInHand, player.place, game->getUserGameData(player.username).m_turnNumber);
	}
}
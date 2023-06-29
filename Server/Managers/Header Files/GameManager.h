# pragma once
# include "../../Infrastructure/Header Files/SqliteDatabase.h"
# include "Room.h"
# include "Game.h"
# include <vector>

class GameManager
{
	public:
		GameManager(std::shared_ptr<IDatabase> db);
		Game createGame(Room room);
		void deleteGame(unsigned int id);
		std::shared_ptr<Game> getGameById(unsigned int id);
		void addGameResults(unsigned int gameId, std::string username);

	private:
		std::shared_ptr<IDatabase> m_database;
		std::vector<std::shared_ptr<Game>> m_games;
};
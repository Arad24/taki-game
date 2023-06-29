# pragma once
# include "../../Infrastructure/Header Files/SqliteDatabase.h"
# include <vector>


bool compareScores(const UserScore& user1, const UserScore& user2);

class StatisticsManager
{
	public:
		StatisticsManager(std::shared_ptr<IDatabase> db);

		StatisticsManager getStatisticsManager();

		std::vector<std::string> getHighScore();
		std::vector<std::string> getUserStats(std::string username);

	private:
		std::shared_ptr<IDatabase> m_database;
};
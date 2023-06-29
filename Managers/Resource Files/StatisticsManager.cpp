# include "../Header Files/StatisticsManager.h"

StatisticsManager::StatisticsManager(std::shared_ptr<IDatabase> db)
{
    this->m_database = db;
}

StatisticsManager StatisticsManager::getStatisticsManager()
{
    return *this;
}

std::vector<std::string> StatisticsManager::getUserStats(std::string username)
{
    std::vector<std::string> stats;

    // Games, Wins, AverageCards, AverageTime, Score
    stats.emplace_back(std::to_string(m_database->getNumOfPlayerGames(username)));
    stats.emplace_back(std::to_string(m_database->getNumOfWins(username)));
    stats.emplace_back(std::to_string(m_database->getAverageNumOfCardsLeft(username)));
    stats.emplace_back(std::to_string(m_database->getPlayerAveragePlayedTime(username)));
    stats.emplace_back(std::to_string(m_database->getPlayerScore(username)));
    

    return stats;
}

bool compareScores(const UserScore& user1, const UserScore& user2)
{
    return user1.score > user2.score;
}

std::vector<std::string> StatisticsManager::getHighScore()
{
    std::vector<std::string> users = m_database->getUsersList();
    std::vector<UserScore> userScores;
    std::vector<std::string> hsList;

    for (auto& user : users)
    {
        userScores.emplace_back(user, m_database->getPlayerScore(user));
    }

    std::sort(userScores.begin(), userScores.end(), compareScores);
    int players = 5;
    if (userScores.size() < 5) players = userScores.size();

    for (int i = 0; i < players; i++)
    {
        hsList.push_back(userScores[i].username);
    }

    return hsList;
}
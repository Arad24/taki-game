# pragma once
# include <string>
# include <vector>
# include <algorithm>

# define DB_NAME "taki.sqlite"
# define WIN_POINTS  100
# define GAME_POINTS 10
# define AVG_POINTS  2


class IDatabase
{
    public:
        virtual bool open() = 0;
        virtual bool close() = 0;

        // User
        virtual int doesUserExist(std::string username) = 0;
        virtual int doesPasswordMatch(std::string firstPass, std::string secPass) = 0;
        virtual int addNewUser(std::string name, std::string password, std::string email) = 0;

        // Statics
        virtual float getPlayerAveragePlayedTime(std::string username) = 0;
        virtual int getNumOfWins(std::string username) = 0;
        virtual float getAverageNumOfCardsLeft(std::string username) = 0;
        virtual int getNumOfPlayerGames(std::string username) = 0;
        virtual int getTotalNumOfCards(std::string username) = 0;
        virtual int getTotalNumOfTurns(std::string username) = 0;
        virtual float getTotalTimePlayed(std::string username) = 0;

        virtual float getPlayerScore(std::string username) = 0;
        virtual std::vector<std::string> getUsersList() = 0;
        virtual void addUserResult(std::string username, unsigned int cardsInHand, unsigned int place, unsigned int turns) = 0;

};
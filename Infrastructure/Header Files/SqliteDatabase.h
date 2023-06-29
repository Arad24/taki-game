# pragma once
# include "IDatabase.h"
# include <iostream>
# include "sqlite3.h"
# include <io.h>

# define CREATE_USERS   "CREATE TABLE USERS(\
                        NAME TEXT PRIMARY KEY NOT NULL,\
                        PASSWORD TEXT NOT NULL,\
                        EMAIL TEXT NOT NULL);"

# define CREATE_STATICS "CREATE TABLE STATICS(\
                        USERNAME TEXT PRIMARY KEY NOT NULL,\
                        GAMES INTEGER NOT NULL,\
                        WINS INTEGER NOT NULL,\
                        TOTAL_TIME_PLAYED REAL NOT NULL,\
                        TOTAL_TURNS_PLAYED INTEGER NOT NULL,\
                        TOTAL_CARDS_LEFT INTEGER NOT NULL,\
                        FOREIGN KEY(USERNAME) REFERENCES USERS(NAME));"


struct UserScore
{
    std::string username;
    float score;

    UserScore(std::string name, float scr) : username(name), score(scr) {}
};


// Call back functions
int cbGetUsers(void* ans, int argc, char** argv, char** column);
int cbGetAns(void* ans, int argc, char** argv, char** column);

class SqliteDatabase : public IDatabase
{
    public:
        SqliteDatabase();
        ~SqliteDatabase();

        bool open() override;
        bool close() override;

        // User
        int doesUserExist(std::string username) override;
        int doesPasswordMatch(std::string firstPass, std::string secPass) override;
        int addNewUser(std::string name, std::string password, std::string email) override;

        // Statics
        float getPlayerAveragePlayedTime(std::string username) override;
        int getNumOfWins(std::string username) override;
        float getAverageNumOfCardsLeft(std::string username) override;
        int getNumOfPlayerGames(std::string username) override;
        int getTotalNumOfCards(std::string username) override;
        int getTotalNumOfTurns(std::string username) override;
        float getTotalTimePlayed(std::string username) override;
        float getPlayerScore(std::string username) override;
        std::vector<std::string> getUsersList() override;
        void addUserResult(std::string username, unsigned int cardsInHand, unsigned int place, unsigned int turns);

    private:
        sqlite3* dbHandle;
    
        bool sendQuery(sqlite3* db, std::string sqlStatement);
        std::string sendQueryAndGetAns(sqlite3* db, std::string sqlStatement);
};
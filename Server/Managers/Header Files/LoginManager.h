# pragma once
# include "../Infrastructure/Header Files/SqliteDatabase.h"
# include "LoggedUser.h"
# include <vector>

class LoginManager
{
    public:
        LoginManager(std::shared_ptr<IDatabase> db);
        void signup(std::string, std::string, std::string);
        void login(std::string, std::string);
        void logout(std::string);

    private:
        std::shared_ptr<IDatabase> m_database;
        std::vector<LoggedUser> m_loggedUsers;

        std::vector<LoggedUser>::iterator findUser(std::string username);
};
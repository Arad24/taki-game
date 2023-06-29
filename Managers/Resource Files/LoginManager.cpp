# include "../Header Files/LoginManager.h"

LoginManager::LoginManager(std::shared_ptr<IDatabase> db) : m_database(db)
{}

void LoginManager::signup(std::string username, std::string password, std::string email)
{
    if (!this->m_database->doesUserExist(username))
    {
        m_database->addNewUser(username, password, email);
    }
    else
    {
        throw std::exception("User already exist.");
    }
}

void LoginManager::login(std::string username, std::string password)
{
    if (m_database->doesUserExist(username) && m_database->doesPasswordMatch(username, password))
    {
        LoggedUser user(username);
        m_loggedUsers.push_back(user);
    }
    else
    {
        throw std::exception("User already Logged in / user or password unmatched exist.");
    }
}

void LoginManager::logout(std::string username)
{
    auto user = findUser(username);

    if (user != m_loggedUsers.end()) m_loggedUsers.erase(user);
    else
    {
        throw std::exception("User doesn't exist.");
    }
}

std::vector<LoggedUser>::iterator LoginManager::findUser(std::string username)
{
    auto user = m_loggedUsers.begin();
    for (user; user !=  m_loggedUsers.end(); ++user) 
    {
        if (user->getUsername() == username) return user;
    }

    return user;
}

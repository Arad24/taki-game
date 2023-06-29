# include "../Header Files/LoggedUser.h"

LoggedUser::LoggedUser(std::string username)
{
    m_username = username;
}

std::string LoggedUser::getUsername()
{
    return m_username;
}
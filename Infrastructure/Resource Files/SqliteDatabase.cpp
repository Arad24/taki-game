# include "../Header Files/SqliteDatabase.h"

SqliteDatabase::SqliteDatabase() 
{
	open();
}

SqliteDatabase::~SqliteDatabase() 
{
	close();
}
bool SqliteDatabase::open()
{
	int filesExist = _access(DB_NAME, 0);
	int res = sqlite3_open(DB_NAME, &this->dbHandle);

	if (res != SQLITE_OK)
	{
		dbHandle = nullptr;
		std::cerr << "Failed to open DB" << std::endl;
		return false;
	}

	// If file doesn't exist    -- Create new db
	if (filesExist == -1)
	{
		bool ans1 = sendQuery(dbHandle, CREATE_USERS);
		bool ans2 = sendQuery(dbHandle, CREATE_STATICS);

		return ans1 && ans2;
	}

	return true;
}

bool SqliteDatabase::close()
{
    try
    {
        sqlite3_close(this->dbHandle);
	    dbHandle = nullptr;
        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}

int SqliteDatabase::doesUserExist(std::string username)
{
	std::string sqlStatement = "SELECT * FROM USERS WHERE NAME = '" + username + "'; ";
	std::string user = sendQueryAndGetAns(dbHandle, sqlStatement);

	return user != "";
}

int SqliteDatabase::doesPasswordMatch(std::string username, std::string password)
{
	std::string sqlStatement = "SELECT * FROM USERS WHERE NAME = '" + username + "' AND PASSWORD = '" + password + "'; ";
    return sendQueryAndGetAns(dbHandle, sqlStatement) != "";
} 

int SqliteDatabase::addNewUser(std::string name, std::string password, std::string email)
{
    std::string usersStatement = "INSERT INTO USERS(NAME, PASSWORD, EMAIL) VALUES('" + name + "', '" + password + "', '" + email + "'); ";

	std::string staticsStatement = "INSERT INTO STATICS(USERNAME, GAMES, WINS, TOTAL_TIME_PLAYED, TOTAL_TURNS_PLAYED, TOTAL_CARDS_LEFT) VALUES('" + name + "', 0, 0, 0, 0, 0); ";


    return sendQuery(dbHandle, usersStatement) && sendQuery(dbHandle, staticsStatement);
}

float SqliteDatabase::getPlayerAveragePlayedTime(std::string username)
{
	int turns = getTotalNumOfTurns(username);
	if (turns == 0) return 0;

	return getTotalTimePlayed(username) / turns;
}

int SqliteDatabase::getNumOfWins(std::string username)
{
	int wins = 0;
	if (doesUserExist(username))
	{
		std::string sqlStatement = "SELECT WINS FROM STATICS WHERE USERNAME = '" + username + "'; ";
		wins = std::stoi(sendQueryAndGetAns(dbHandle, sqlStatement));
	}

	return wins;
}

float SqliteDatabase::getAverageNumOfCardsLeft(std::string username)
{
	int games = getNumOfPlayerGames(username);
	if (games == 0) return 0;

	return (((float)getTotalNumOfCards(username)) / games);
}

int SqliteDatabase::getNumOfPlayerGames(std::string username)
{
	int games = 0;
	if (doesUserExist(username))
	{
		std::string sqlStatement = "SELECT GAMES FROM STATICS WHERE USERNAME = '" + username + "'; ";
		games = std::stoi(sendQueryAndGetAns(dbHandle, sqlStatement));
	}

	return games;
}

int SqliteDatabase::getTotalNumOfCards(std::string username)
{
	int numOfCards = 0;
	if (doesUserExist(username))
	{
		std::string sqlStatement = "SELECT TOTAL_CARDS_LEFT FROM STATICS WHERE USERNAME = '" + username + "'; ";
		numOfCards = std::stoi(sendQueryAndGetAns(dbHandle, sqlStatement));
	}

	return numOfCards;
}

int SqliteDatabase::getTotalNumOfTurns(std::string username)
{
	int numOfTurns = 0;
	if (doesUserExist(username))
	{
		std::string sqlStatement = "SELECT TOTAL_TURNS_PLAYED FROM STATICS WHERE USERNAME = '" + username + "'; ";
		numOfTurns = std::stoi(sendQueryAndGetAns(dbHandle, sqlStatement));
	}

	return numOfTurns;
}

float SqliteDatabase::getTotalTimePlayed(std::string username)
{
	float timePlayed = 0;
	if (doesUserExist(username))
	{
		std::string sqlStatement = "SELECT TOTAL_TIME_PLAYED FROM STATICS WHERE USERNAME = '" + username + "'; ";
		timePlayed = std::stof(sendQueryAndGetAns(dbHandle, sqlStatement));
	}

	return timePlayed;
}

float SqliteDatabase::getPlayerScore(std::string username)
{
	/* 
		+ Game     = 10 Points
		+ Win	   = 100 Points
		- AvgTime  = 2 Poits
		- AvgCards = 2 Points
	*/

	return	(
				(getNumOfPlayerGames(username) * GAME_POINTS) +
				(getNumOfWins(username) * WIN_POINTS) -
				(getPlayerAveragePlayedTime(username) * AVG_POINTS) -
				(getAverageNumOfCardsLeft(username) * AVG_POINTS)
			);
}

std::vector<std::string> SqliteDatabase::getUsersList()
{
	std::string sqlStatement = "SELECT NAME FROM USERS;";
	std::vector <std::string> users;

	int res = sqlite3_exec(dbHandle, sqlStatement.c_str(), cbGetUsers, &users, nullptr);
	
	 return users;
}

bool SqliteDatabase::sendQuery(sqlite3* db, std::string sqlStatement)
{
	char** errMessage = nullptr;
	
	int res = sqlite3_exec(db, sqlStatement.c_str(), nullptr, nullptr, errMessage);
	if (res != SQLITE_OK)
	{
		return false;
	}

	return true;
}

int cbGetUsers(void* ans, int argc, char** argv, char** column)
{
	std::vector<std::string>* fullAns = (std::vector<std::string>*)ans;

	for (int i = 0; i < argc; i++)
	{
		fullAns->push_back(std::string(argv[i]));
	}

	return SQLITE_OK;
}

int cbGetAns(void* ans, int argc, char** argv, char** column)
{
    std::string* fullAns = (std::string*)ans;

	for (int i = 0; i < argc;i++)
	{
		*fullAns += argv[i];
	}

	return SQLITE_OK;
}

std::string SqliteDatabase::sendQueryAndGetAns(sqlite3* db, std::string sqlStatement)
{
    char** errMessage = nullptr; 
	std::string ans = "";

    int res = sqlite3_exec(dbHandle, sqlStatement.c_str(), cbGetAns, &ans, errMessage);
	if (res != SQLITE_OK)
	{
		std::cerr << "Error with sendQueryAndGetAns\n";
		return "";
	}

    return ans;
}


void SqliteDatabase::addUserResult(std::string username, unsigned int cardsInHand, unsigned int place, unsigned int turns)
{
	int wins = 0;
	if (place == 1) wins = 1;
	std::string statement = "UPDATE STATICS SET WINS = WINS + " + std::to_string(wins) + ", TOTAL_CARDS_LEFT = TOTAL_CARDS_LEFT + " + std::to_string(cardsInHand) + ", TOTAL_TURNS_PLAYED = TOTAL_TURNS_PLAYED + " + std::to_string(turns) + ", GAMES = GAMES + 1 WHERE USERNAME = '" + username + "'; ";

	if (!sendQuery(dbHandle, statement))
	{
		std::cout << "Error db";
	}
}
# pragma once
# include "LoggedUser.h"
# include "CardDeck.h"
# include "Card.h"
# include <map>
# include "../../Request/Header Files/JsonResponsePacketSerializer.h";

struct GameData
{
	std::shared_ptr<CardDeck> m_playerDeck;
	unsigned int m_turnNumber;
};

# define DECKS_NUM 3


class Game
{
	public:
		Game(LoggedUser currentPlayer, std::vector<LoggedUser> users, unsigned int gameId);
		void playCard(LoggedUser user, Card card);
		void removePlayer(LoggedUser user);
		void moveToNextPlayer();

		std::map<std::shared_ptr<LoggedUser>, GameData> createPlayersMap(std::vector<LoggedUser> users);
		void createGameDeck();
		std::shared_ptr<CardDeck> drawCards(int numOfCardsToDraw, std::string username);

		unsigned int getId();
		std::vector<PlayerResults> getPlayers();
		int getPlus();
		void setPlus(int plus);
		std::map<std::string, unsigned int> getCardsPerPlayer();
		std::shared_ptr<CardDeck> getPlayerCards(LoggedUser user);
		std::string getLastCardPlay();
		std::string getCurrPlayer();
		bool getDirection();
		GameData getUserDeck(std::string username);
		void playSpecialCard(Card card);
		void closeTaki();
		bool getIsGameEnd();
		GameData getUserGameData(std::string username);
		int addPlayerEnd();

	private:
		unsigned int m_gameId;
		std::shared_ptr<LoggedUser> m_currentPlayer;
		CardDeck m_gameDeck;
		bool m_currDir;
		Card m_currentCard;
		std::map<std::shared_ptr<LoggedUser>, GameData> m_players;
		bool isTaki;
		int m_plus;
		bool m_gameEnd;
		bool m_inGame;
		int playersEnd;

		void addNums(char color);
		void addColorTaki(char color);
		void addPlus2(char color);
		void addCards(char color);
		void addChangeDir(char color);
		void addStop(char color);
		void addSpecialCards();
		void addPlus(char color);

};
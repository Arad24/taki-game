# include "../Header Files/Game.h"

Game::Game(LoggedUser currentPlayer, std::vector<LoggedUser> users, unsigned int gameId)
{
	m_inGame = false;
	createGameDeck();
	m_gameId = gameId;
	m_currDir = true;
	m_currentPlayer = std::make_shared<LoggedUser>(currentPlayer);
	m_players = createPlayersMap(users);
	m_currentCard = m_gameDeck.getFirstCard();
	m_gameDeck.removeCard(m_currentCard);
	isTaki = false;
	m_plus = 0;
	m_gameEnd = false;
	m_inGame = true;
	playersEnd = 0;
}


std::map<std::shared_ptr<LoggedUser>, GameData> Game::createPlayersMap(std::vector<LoggedUser> users)
{
	std::map<std::shared_ptr<LoggedUser>, GameData> players;

	for (auto user : users)
	{
		GameData newGD = GameData();
		newGD.m_playerDeck = drawCards(8, user.getUsername());
		newGD.m_turnNumber = 0;

		players.insert({ std::make_shared<LoggedUser>(user.getUsername()), newGD });
	}

	return players;
}


int Game::addPlayerEnd()
{
	playersEnd++;
	std::cout << playersEnd;
	return playersEnd;
}

GameData Game::getUserGameData(std::string username)
{
	for (const auto& player : m_players)
	{
		if (player.first->getUsername() == username) return player.second;
	}
}

void Game::playCard(LoggedUser user, Card card)
{	
	if (user.getUsername() == m_currentPlayer->getUsername())
	{
		if (isTaki && card.getColor() == m_currentCard.getColor())
		{
			GameData playerDeck = getUserDeck(user.getUsername());

			// Handle play
			playerDeck.m_playerDeck->removeCard(card);
			m_currentCard = card;
			m_gameEnd = playerDeck.m_playerDeck->getSize() == 0;
		}
		else if (card.isLegalToPlay(m_currentCard, isTaki) && (m_plus == 0 || card.getName() == PLUS_2))
		{
			try
			{
				
				GameData playerDeck = getUserDeck(user.getUsername());

				if (card.isSpecialCard())
				{
					playSpecialCard(card);
					if (!(card.getName() == PLUS || card.getName() == COLOR_TAKI || card.getName() == SPECIAL_TAKI))
					{
						playerDeck.m_turnNumber++;
					}
				}
				else
				{
					moveToNextPlayer();
					playerDeck.m_turnNumber++;
				}

				char currCol = card.getColor();
				if (card.getName() == CHANGE_COLOR || card.getName() == SPECIAL_TAKI) card.setColor(NONE);

				// Handle play
				playerDeck.m_playerDeck->removeCard(card);
				if (card.getName() == CHANGE_COLOR || card.getName() == SPECIAL_TAKI) card.setColor(currCol);
				m_currentCard = card;
				m_gameEnd = playerDeck.m_playerDeck->getSize() == 0;

			}
			catch (const std::exception e)
			{
				throw e;
			}
		}
	}
	else
	{
		throw std::exception("Not your turn");
	}
}

bool Game::getIsGameEnd()
{
	return m_gameEnd;
}

int Game::getPlus()
{
	return m_plus;
}

void Game::setPlus(int plus)
{
	m_plus = plus;
}


void Game::closeTaki()
{
	if (m_currentCard.isSpecialCard())
	{
		playSpecialCard(m_currentCard);
	}
	else
	{
		moveToNextPlayer();
	}
	isTaki = false;
}


void Game::playSpecialCard(Card card)
{

	if (card.getName() == PLUS) 
	{}
	else if (card.getName() == COLOR_TAKI || card.getName() == SPECIAL_TAKI)
	{ 
		isTaki = true;
	}
	else
	{
		if (card.getName() == STOP)
		{
			moveToNextPlayer();
		}
		else if (card.getName() == CHANGE_DIR)
		{
			m_currDir = !m_currDir;
		}
		else if (card.getName() == PLUS_2)
		{
			m_plus += 2;
		}

		moveToNextPlayer();
	}
}

GameData Game::getUserDeck(std::string username)
{
	for (auto user : m_players)
	{
		if (user.first->getUsername() == username)
		{
			return user.second;
		}
	}

	throw std::exception("user not found");
}


unsigned int Game::getId()
{
	return this->m_gameId;
}


void Game::removePlayer(LoggedUser user)
{

	auto iter = std::find_if(m_players.begin(), m_players.end(), [&user](const auto& pair) {
		return pair.first->getUsername() == user.getUsername();
		});

	if (iter != m_players.end()) {
		m_players.erase(iter);
	}
}

void Game::moveToNextPlayer()
{
	auto players = m_players.begin();

	while(players != m_players.end())
	{
		if (players->first->getUsername() == m_currentPlayer->getUsername())
		{
			auto nextIterator = players;

			if (m_currDir)
			{
				++nextIterator;
				if (nextIterator == m_players.end()) nextIterator = m_players.begin();
			}
			else
			{
				if (nextIterator == m_players.begin()) nextIterator = m_players.end();
				--nextIterator;
			}

			m_currentPlayer = nextIterator->first;
			break;
		}
		players++;
	}
}



void Game::addNums(char color)
{
	for (int num = 1; num < 9; num++)
	{
		Card card = { std::to_string(num), color };
		this->m_gameDeck.addCard(card);
	}
}

void Game::addColorTaki(char color)
{
	Card card = { COLOR_TAKI, color };
	this->m_gameDeck.addCard(card);
}

void Game::addPlus2(char color)
{
	Card card = { PLUS_2, color };
	this->m_gameDeck.addCard(card);
}

void Game::addSpecialCards()
{
	// Special taki
	Card specialTaki = { SPECIAL_TAKI, NONE };
	this->m_gameDeck.addCard(specialTaki);

	// Change color
	Card changeColor = { CHANGE_COLOR, NONE };
	this->m_gameDeck.addCard(changeColor);
}

void Game::addChangeDir(char color)
{
	Card card = { CHANGE_DIR, color };
	this->m_gameDeck.addCard(card);
}

void Game::addPlus(char color)
{
	Card card = { PLUS, color };
	this->m_gameDeck.addCard(card);
}

void Game::addStop(char color)
{
	Card card = { STOP, color };
	this->m_gameDeck.addCard(card);
}

void Game::addCards(char color)
{
	addNums(color);
	addColorTaki(color);
	addPlus2(color);
	addChangeDir(color);
	addStop(color);
	addPlus(color);
}


void Game::createGameDeck()
{
	char COLORS[] = { 'r', 'g', 'y', 'b' };
	int colorsNum = sizeof(COLORS) / sizeof(COLORS[0]);

	for (int i = 0; i < DECKS_NUM; i++)
	{
		addSpecialCards();
		for (int j = 0; j < colorsNum; j++)
		{
			addCards(COLORS[i]);
		}
	}
}


std::shared_ptr<CardDeck> Game::drawCards(int numOfCardsToDraw, std::string username)
{
	if (username == m_currentPlayer->getUsername() || !m_inGame)
	{
		std::shared_ptr<CardDeck> newDeck = std::make_shared<CardDeck>();

		for (int i = 0; i < numOfCardsToDraw; i++)
		{
			auto card = m_gameDeck.getRandomCard();
			newDeck->addCard(card);
			m_gameDeck.removeCard(card);
		}

		return newDeck;
	}
	
	throw std::exception("Not your turn");
}


std::vector<PlayerResults> Game::getPlayers() 
{
	std::vector<PlayerResults> playersRes;
	std::multimap<size_t, std::shared_ptr<LoggedUser>> convertedMap;

	for (const auto& pair : m_players) 
	{
		size_t deckSize = pair.second.m_playerDeck->getSize();
		convertedMap.emplace(deckSize, pair.first);
	}

	int place = 1;

	for (const auto& pair : convertedMap) 
	{
		PlayerResults pr = { pair.second->getUsername(), pair.first, place };
		playersRes.push_back(pr);
		place++;
	}

	return playersRes;
}


std::map<std::string, unsigned int> Game::getCardsPerPlayer()
{
	std::map<std::string, unsigned int> cards;

	for (auto player : m_players)
	{
		cards[player.first->getUsername()] = player.second.m_playerDeck->getSize();
	}

	return cards;
}


std::shared_ptr<CardDeck> Game::getPlayerCards(LoggedUser user)
{
	for (auto player : m_players)
	{
		if (player.first->getUsername() == user.getUsername())
		{
			return player.second.m_playerDeck;
		}
	}
}

std::string Game::getLastCardPlay()
{
	return m_currentCard.toString();
}

std::string Game::getCurrPlayer()
{
	return m_currentPlayer->getUsername();
}

bool Game::getDirection()
{
	return m_currDir;
}
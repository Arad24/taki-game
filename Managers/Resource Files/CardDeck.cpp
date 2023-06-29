# include "../Header Files/CardDeck.h"


void CardDeck::addCard(Card card)
{
	m_cards.push_back(card);
}

void CardDeck::removeCard(Card card)
{
	auto it = std::find(m_cards.begin(), m_cards.end(), card);

	if (it != m_cards.end()) m_cards.erase(it);
	else throw std::exception("Card not found");
}

Card CardDeck::getRandomCard()
{
	if (m_cards.size() > 0)
	{
		int min = 0, max = m_cards.size() - 1;

		int randPlace = rand() % (max - min + 1) + min;

		return m_cards.at(randPlace);
	}

	throw std::exception("Card deck is empty");
}

Card CardDeck::getFirstCard()
{
	if (m_cards.size() > 0)
	{
		int min = 0, max = m_cards.size() - 1;

		int randPlace = rand() % (max - min + 1) + min;

		while (m_cards.at(randPlace).isSpecialCard())
		{
			randPlace = rand() % (max - min + 1) + min;
		}

		return m_cards.at(randPlace);
	}

	throw std::exception("Card deck is empty");
}


int CardDeck::getSize()
{
	return m_cards.size();
}


std::vector<std::string> CardDeck::toString()
{
	std::vector<std::string> cards;

	for (auto card : m_cards)
	{
		cards.push_back(card.toString());
	}

	return cards;
}
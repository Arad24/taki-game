# pragma once
# include <iostream>
# include <vector>
# include <algorithm>
# include "Card.h"

class CardDeck
{
	public:
		void addCard(Card card);
		void removeCard(Card card);
		Card getRandomCard();
		Card getFirstCard();

		int getSize();
		std::vector<std::string> toString();

	private:
		std::vector<Card> m_cards;
};
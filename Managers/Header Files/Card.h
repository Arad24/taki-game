# pragma once
# include <iostream>
# include <string>

# define PLUS_2 "p2"
# define SPECIAL_TAKI "st"
# define COLOR_TAKI "ct"
# define STOP "s"
# define CHANGE_COLOR "cc"
# define CHANGE_DIR "cd"
# define PLUS "p"
# define NONE 'n'

class Card;

class Card
{
	public:
		Card();
		Card(std::string cardName, char cardColor);

		std::string toString();
		std::string getName();
		char getColor();
		void setColor(char color);

		bool isLegalToPlay(Card lastCard, bool isTaki);
		bool isSpecialCard();

		bool operator==(const Card& other) const;

	private:
		char color;
		std::string name;
};

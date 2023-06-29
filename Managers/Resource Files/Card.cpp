# include "../Header Files/Card.h"

Card::Card() {}

Card::Card(std::string cardName, char cardColor) 
	: name(cardName), color(cardColor) {}

bool Card::isSpecialCard()
{
	if (this->name == CHANGE_COLOR ||
		this->name == SPECIAL_TAKI ||
		this->name == STOP ||
		this->name == PLUS_2 ||
		this->name == CHANGE_DIR ||
		this->name == COLOR_TAKI ||
		this->name == PLUS
	)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Card::isLegalToPlay(Card lastCard, bool isTaki)
{
	if (isSpecialCard())
	{
		if (this->name == COLOR_TAKI)
		{
			if (!isTaki && (this->color == lastCard.color || this->name == lastCard.name)) return true;
			else if (isTaki && this->color == lastCard.color) return true;
			else return false;

		}
		else if (this->name == SPECIAL_TAKI)
		{
			return true;
		}
		else if (this->name == STOP ||
			this->name == PLUS_2 ||
			this->name == CHANGE_DIR ||
			this->name == PLUS)
		{
			if (this->color == lastCard.color || this->name == lastCard.name) return true;
			else return false;
		}
		else if (this->name == CHANGE_COLOR) return true;
	}
	else if (lastCard.color == this->color || lastCard.name == this->name)
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::string Card::toString()
{
	return (std::string(1, this->color) + this->name);
}


std::string Card::getName()
{
	return this->name;
}

char Card::getColor()
{
	return this->color;
}

bool Card::operator==(const Card& other) const
{
	return (this->color == other.color) &&
		(this->name == other.name);
}


void Card::setColor(char color)
{
	this->color = color;
}
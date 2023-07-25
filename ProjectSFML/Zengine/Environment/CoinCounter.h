#pragma once

#include<sstream>
#include"../ZenObject/ZenText.h"

class CoinCounter
{
public:
	CoinCounter(int IDIn, string NameIn, sf::Vector2f sizeIn);
	void IncrementCounter();
	void Draw(sf::RenderWindow* window);

private:
	ZenText* coinCounter;
	int coins = 0;
	std::stringstream coinsStringstream;

};


#pragma once

#include<sstream>
#include"../ZenObject/ZenText.h"

class CoinCounter
{
public:
	CoinCounter(int IDIn, string NameIn, sf::Vector2f sizeIn);
	~CoinCounter();

	void IncrementCounter();
	void Draw(class RenderingStack* stack);

private:
	std::stringstream coinsStringstream;
	int coins = 0;
	ZenText* coinCounter = nullptr;
	class RenderObject* renderObject = nullptr;
};

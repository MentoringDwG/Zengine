#pragma once

#include <sstream>
#include <Zengine/ZenObject/ZenText.h>

class CoinCounter
{
public:
	CoinCounter(int IDIn, string NameIn, sf::Vector2f sizeIn);
	~CoinCounter();

	void IncrementCounter();
	void Draw(struct RenderingStack* stack);

private:
	std::stringstream coinsStringstream;
	int coins = 0;
	ZenText* coinCounter = nullptr;
	struct RenderObject* renderObject = nullptr;
};

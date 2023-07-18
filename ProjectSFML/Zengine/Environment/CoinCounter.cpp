#include "CoinCounter.h"

CoinCounter::CoinCounter(int IDIn, string NameIn, sf::Vector2f sizeIn)
{
	coinCounter = new ZenText(IDIn, NameIn, sizeIn);
	coinCounter->SetPosition(sf::Vector2f(500, 0));
	coinCounter->SetColor(sf::Color::White);
	coinCounter->SetSize(20);
	coinCounter->SetFont("Fonts/Super_Mario_Bros_/SuperMarioBros.ttf");

	coinsStringstream << "Coins: " << coins;
	coinCounter->SetText(coinsStringstream.str());
}

void CoinCounter::CoinCounterUpdate()
{
	coinsStringstream.str(std::string());

	coins++;
	coinsStringstream << "Coins: " << coins;
	coinCounter->SetText(coinsStringstream.str());
}

void CoinCounter::DrawCoinCounter(sf::RenderWindow* window)
{
	window->draw(coinCounter->Draw());
}
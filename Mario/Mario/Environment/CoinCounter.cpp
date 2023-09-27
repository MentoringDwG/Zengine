#include "CoinCounter.h"
#include <Zengine/Renderer/Renderer.h>

CoinCounter::CoinCounter(int IDIn, string NameIn, sf::Vector2f sizeIn)
{
	coinCounter = new ZenText(IDIn, NameIn, sizeIn);
	coinCounter->SetPosition(sf::Vector2f(500, 0));
	coinCounter->SetColor(sf::Color::White);
	coinCounter->SetSize(20);
	coinCounter->SetFont("Fonts/Super_Mario_Bros_/SuperMarioBros.ttf");

	coinsStringstream << "Coins: " << coins;
	coinCounter->SetText(coinsStringstream.str());
	renderObject = nullptr;
}

CoinCounter::~CoinCounter()
{
	delete renderObject;
	delete coinCounter;
}

void CoinCounter::IncrementCounter()
{
	coinsStringstream.str(std::string());

	coins++;
	coinsStringstream << "Coins: " << coins;
	coinCounter->SetText(coinsStringstream.str());
}

void CoinCounter::Draw(RenderingStack* stack)
{
	if (renderObject == nullptr)
	{
		renderObject = new RenderObject(coinCounter->GetTextRaw(), 1000, 1);
		stack->renderQueueUI.push_back(renderObject);
	}
}

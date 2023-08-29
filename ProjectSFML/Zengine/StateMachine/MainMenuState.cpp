#include "MainMenuState.h"

#include <iostream>

MainMenuState::MainMenuState(int stateIdIn, RenderingStack* renderStack) : BaseGameState(stateIdIn)
{
	this->renderStack = new  RenderingStack();
	this->renderStack = renderStack;

	spriteSheets.push_back(new sf::Texture());
	spriteSheets.push_back(new sf::Texture());
	spriteSheets.push_back(new sf::Texture());
	spriteSheets.push_back(new sf::Texture());

	spriteSheets[0]->loadFromFile("Graphics/MainMenu/MainMenuSpriteSheet1.png");
	spriteSheets[1]->loadFromFile("Graphics/MainMenu/MainMenuSpriteSheet2.png");
	spriteSheets[2]->loadFromFile("Graphics/MainMenu/MainMenuSpriteSheet3.png");
	spriteSheets[3]->loadFromFile("Graphics/MainMenu/MainMenuSpriteSheet4.png");

	zenShape = new ZenShape(10, "MainMenu", sf::Vector2f(960, 544));
	zenShape->SetSize(sf::Vector2f(960, 544));

	zenShape->Draw()->setTexture(spriteSheets[0]);
	zenShape->Draw()->setTextureRect(rectSpriteSheet);
}

void MainMenuState::OnEnter(int prevStateId)
{
	std::cout << "Main Menu enter" << std::endl;

	renderObject = new RenderObject(zenShape->Draw(), 1, 2);
	renderStack->renderQueue.push_back(renderObject);

	clock.restart();
}

void MainMenuState::OnUpdate()
{
	Animation();
}

void MainMenuState::OnLeave(int nextStateId)
{
	std::cout << "Main Menu leave" << std::endl;
}

void MainMenuState::Animation()
{
	if (clock.getElapsedTime().asMilliseconds() > 150)
	{
		if (zenShape->Draw()->getTexture() == spriteSheets[0] && rectSpriteSheet.left == 14400)
		{
			zenShape->Draw()->setTexture(spriteSheets[1]);
			rectSpriteSheet.left = 0;
		}
		else if (zenShape->Draw()->getTexture() == spriteSheets[1] && rectSpriteSheet.left == 14400)
		{
			zenShape->Draw()->setTexture(spriteSheets[2]);
			rectSpriteSheet.left = 0;
		}
		else if (zenShape->Draw()->getTexture() == spriteSheets[2] && rectSpriteSheet.left == 15360)
		{
			zenShape->Draw()->setTexture(spriteSheets[3]);
			rectSpriteSheet.left = 0;
		}
		else if (zenShape->Draw()->getTexture() == spriteSheets[3] && rectSpriteSheet.left == 14400)
		{
			zenShape->Draw()->setTexture(spriteSheets[0]);
			rectSpriteSheet.left = 0;
		}
		else
		{
			rectSpriteSheet.left += 960;
		}

		zenShape->Draw()->setTextureRect(rectSpriteSheet);
		clock.restart();
	}
}
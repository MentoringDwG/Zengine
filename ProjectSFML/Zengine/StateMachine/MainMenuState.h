#pragma once

#include "BaseGameState.h"
#include "../Renderer/Renderer.h"
#include "../UIinGame/MainMenuPanel.h"

class MainMenuState : public BaseGameState
{
private:
	void Animation();

	MainMenuPanel mainMenuPanel;
	sf::IntRect rectSpriteSheet = sf::IntRect(0, 0, 960, 544);
	sf::Clock clock;
	string spriteSheetPath = "Graphics/MainMenu/MainMenuSpriteSheet.png";
	class ZenShape* zenShape = nullptr;
	std::vector<sf::Texture*> spriteSheets;
	sf::Texture* texture = nullptr;
	RenderObject* renderObject = nullptr;
	RenderingStack* renderStack = nullptr;
	Renderer* renderer = nullptr;
	StateMachine* stateMachine = nullptr;

public:
	virtual void OnEnter(int prevStateId) override;
	virtual void OnUpdate() override;
	virtual void OnLeave(int nextStateId) override;

	MainMenuState(int stateIdIn, RenderingStack* renderStack, class StateMachine* stateMachine, Renderer* renderer);
	~MainMenuState();
};


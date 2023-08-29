#pragma once

#include "BaseGameState.h"
#include "../Renderer/Renderer.h"
#include "../ZenObject/ZenShape.h"
#include "../World/TextureAsset.h"
#include "../UI/UIButton.h"
#include "../InputModule/UIInputHandler.h"

class MainMenuState : public BaseGameState
{
private:
	ZenShape* zenShape = nullptr;
	std::vector<sf::Texture*> spriteSheets;
	sf::Texture* texture = nullptr;
	RenderObject* renderObject = nullptr;
	RenderingStack* renderStack = nullptr;
	UIButton* start = nullptr;

	string spriteSheetPath = "Graphics/MainMenu/MainMenuSpriteSheet.png";
	sf::IntRect rectSpriteSheet = sf::IntRect(0, 0, 960, 544);

	sf::Clock clock;

	ZenShape* logo = nullptr;
	sf::Texture* logoTexture = nullptr;
	RenderObject* logoRenderObject = nullptr;

	void StartHover(int id);

	void Animation();

public:
	virtual void OnEnter(int prevStateId) override;
	virtual void OnUpdate() override;
	virtual void OnLeave(int nextStateId) override;

	MainMenuState(int stateIdIn, RenderingStack* renderStack);

};


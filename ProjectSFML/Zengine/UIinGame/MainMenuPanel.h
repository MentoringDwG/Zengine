#pragma once

#include "../UI/CompoundWidget.h"
#include "../InputModule/UIInputHandler.h"
#include "../Renderer/Renderer.h"

class UIButton;

class MainMenuPanel
{
private:
	void StartPressed(int id);
	void ControlsPressed(int id);
	void AuthorsPressed(int id);
	void ExitPressed(int id);

	CompoundWidget* buttons = nullptr;

	class ZenShape* logo = nullptr;
	sf::Texture* logoTexture = nullptr;
	RenderObject* logoRenderObject = nullptr;

	UIButton* start = nullptr;
	UIButton* controls = nullptr;
	UIButton* authors = nullptr;
	
	UIButton* volumeIcon = nullptr;
	UIButton* exitIcon = nullptr;

	class StateMachine* stateMachine = nullptr;
	class WaitingRoomState* waitingRoonState = nullptr;

public:
	~MainMenuPanel();

	void Initialize(class StateMachine* stateMachine);
	void Draw(RenderingStack* renderStack);
	void ButtonsInputInitialize();
};


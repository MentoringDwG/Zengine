#pragma once

#include "../Structs/Vector2.h"
#include "../UI/CompoundWidget.h"
#include "../UI/UIButton.h"
#include "../InputModule/UIInputHandler.h"
#include "../StateMachine/WaitingRoomState.h"

class MainMenuPanel
{
private:
	CompoundWidget* buttons = nullptr;

	ZenShape* logo = nullptr;
	sf::Texture* logoTexture = nullptr;
	RenderObject* logoRenderObject = nullptr;

	UIButton* start = nullptr;
	UIButton* controls = nullptr;
	UIButton* authors = nullptr;
	
	UIButton* volumeIcon = nullptr;
	UIButton* exitIcon = nullptr;

	class StateMachine* stateMachine = nullptr;

	void StartPressed(int id);
	void ControlsPressed(int id);
	void AuthorsPressed(int id);
	void ExitPressed(int id);

	WaitingRoomState* waitingRoonState = nullptr;

public:
	~MainMenuPanel();

	void Initialize(class StateMachine* stateMachine);
	void Draw(RenderingStack* renderStack);
	void ButtonsInputInitialize();
};


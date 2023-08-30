#pragma once

#include "../Structs/Vector2.h"
#include "../UI/CompoundWidget.h"
#include "../UI/UIButton.h"
#include "../InputModule/UIInputHandler.h"
#include "../StateMachine/WaitingRoomState.h"

class MainMenuPanel
{
private:
	CompoundWidget* buttons;

	ZenShape* logo = nullptr;
	sf::Texture* logoTexture = nullptr;
	RenderObject* logoRenderObject = nullptr;

	UIButton* start;
	UIButton* controls;
	UIButton* authors;
	
	UIButton* volumeIcon;
	UIButton* exitIcon;

	class StateMachine* stateMachine = nullptr;

	void StartHover(int id);
	void StartUnHover(int id);
	void StartPressed(int id);
	void StartUnPressed(int id);

	void ControlsHover(int id);
	void ControlsUnHover(int id);
	void ControlsPressed(int id);
	void ControlsUnPressed(int id);

	void AuthorsHover(int id);
	void AuthorsUnHover(int id);
	void AuthorsPressed(int id);
	void AuthorsUnPressed(int id);

	void VolumeHover(int id);
	void VolumeUnHover(int id);

	void ExitHover(int id);
	void ExitUnHover(int id);
	void ExitPressed(int id);

	WaitingRoomState* waitingRoonState = nullptr;

public:
	void Initialize(class StateMachine* stateMachine);
	void Draw(RenderingStack* renderStack);
	void ButtonsInputInitialize();
};


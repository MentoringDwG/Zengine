#pragma once

#include "../../../Zengine/Zengine/Renderer/Renderer.h"

class AppMarioGame
{
public:
	AppMarioGame(class StateMachine* stateMachine, RenderingStack* renderStack, Renderer* renderModule, class World* world);
	~AppMarioGame();

	void Initialize(class Zengine* zengine);

private:
	void StateInitialize();
	void OnLoading(int id);

	class StateMachine* stateMachine = nullptr;

	class MainMenuState* mainMenuState = nullptr;
	class LoadingState* loadingState = nullptr;
	class GameplayState* gameplayState = nullptr;
	class WaitingRoomState* waitingRoomState = nullptr;
	class ControlsPanelState* controlsPanelState = nullptr;
	class AuthorsState* authorsState = nullptr;
	class GameOverState* gameOverState = nullptr;
	class WinState* winState = nullptr;

	RenderingStack* renderStack = nullptr;
	Renderer* renderModule = nullptr;
	class World* world = nullptr;
	class Zengine* zengine = nullptr;
};


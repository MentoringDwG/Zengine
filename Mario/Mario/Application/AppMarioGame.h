#pragma once

#include <Zengine/Renderer/Renderer.h>
#include "../World/LevelManager.h"

class AppMarioGame
{
public:
	AppMarioGame();
	~AppMarioGame();

	void Initialize(class Zengine* zengine);
	class World* GetWorld();

private:
	void StateInitialize();
	void OnLoading(int id);

	LevelManager levelManager;

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
	class Zengine* zengine = nullptr;
	class Character* playerCharacter = nullptr;

	class UIScene* uiScene = nullptr;
	class Level1* level1 = nullptr;
};


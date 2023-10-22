#pragma once

#include <Zengine/Renderer/Renderer.h>
#include "../World/LevelManager.h"
#include <Zengine/Core/App.h>

class AppMarioGame : public App
{
public:
	AppMarioGame();
	~AppMarioGame();

	void Initialize(class Zengine* zengine);
	class World* GetWorld();
	void Tick(float DeltaTime) override;
	void Uninitialize() override;
	int GetGameState();

private:
	void StateInitialize();
	void OnLoading(int id);

	LevelManager levelManager;

	// Tu znajduje siê g³ówna instancja state machine. A nie w ZenEngine.
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
	class AudioSystem* audioSystem = nullptr;
	class Zengine* zengine = nullptr;
	class Character* playerCharacter = nullptr;

	class UIScene* uiScene = nullptr;
	class Level* level = nullptr;
};


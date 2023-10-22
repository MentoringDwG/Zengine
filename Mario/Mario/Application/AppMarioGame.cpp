#include "AppMarioGame.h"

#include <Zengine/Zengine.h>
#include <Zengine/StateMachine/StateMachine.h>
#include <Zengine/World/World.h>
#include <Zengine/InputModule/CharacterInputHandler.h>
#include <Zengine/InputModule/InputProcessorModule.h>
#include <Zengine/Audio/AudioSystem.h>

#include "../StateMachine/MainMenuState.h"
#include "../StateMachine/LoadingState.h"
#include "../StateMachine/GameplayState.h"
#include "../StateMachine/ControlsPanelState.h"
#include "../StateMachine/AuthorsState.h"
#include "../StateMachine/WaitingRoomState.h"
#include "../StateMachine/GameOverState.h"
#include "../StateMachine/WinState.h"
#include "../World/Level.h"
#include "../Character/Character.h"
#include "../UIinGame/UIScene.h"

AppMarioGame::AppMarioGame()
{
	level = new Level("Tiles/JsonFiles/Level_1.json");

	levelManager.AddLevel(0, level);
}

AppMarioGame::~AppMarioGame()
{
	delete stateMachine;
	delete mainMenuState;
	delete loadingState;
	delete gameplayState;
	delete waitingRoomState;
	delete controlsPanelState;
	delete gameOverState;
	delete authorsState;
	delete renderStack;
	delete renderModule;
	delete zengine;

	delete level;
}

void AppMarioGame::Initialize(Zengine* zengine)
{
	stateMachine = new StateMachine();
	this->zengine = zengine;
	this->renderStack = zengine->GetRenderingStack();
	this->renderModule = zengine->GetRenderer();
	this->audioSystem = zengine->GetAudioSystem();

	audioSystem->sounds.SoundBankPath = "../Mario/Audio/Sounds";
	audioSystem->musics.SoundBankPath = "../Mario/Audio/Music";
	audioSystem->Initialize();

	playerCharacter = new Character("Mario", "Graphics/Mario/Mario.png", 3, audioSystem);
	level->SetPlayer(playerCharacter);

	uiScene = new UIScene(stateMachine);
	level->SetUIScene(uiScene);
	level->SetRendering(renderStack, renderModule);

	StateInitialize();
	stateMachine->TransitionTo(State::MainMenuState);
	audioSystem->PlayMusic("soundtrack");
}

void AppMarioGame::StateInitialize()
{
	mainMenuState = new MainMenuState(State::MainMenuState, renderStack, stateMachine, renderModule);
	loadingState = new LoadingState(State::LoadingState, stateMachine);
	gameplayState = new GameplayState(State::GameplayState, renderStack);
	controlsPanelState = new ControlsPanelState(State::ControlsPanelState, renderStack, stateMachine);
	authorsState = new AuthorsState(State::AuthorsState, renderStack, stateMachine);
	gameOverState = new GameOverState(State::GameOverState, renderStack, stateMachine);
	winState = new WinState(State::WinState, renderStack, stateMachine);

	stateMachine->AddState(mainMenuState);
	stateMachine->AddState(loadingState);
	stateMachine->AddState(gameplayState);
	stateMachine->AddState(controlsPanelState);
	stateMachine->AddState(authorsState);
	stateMachine->AddState(gameOverState);
	stateMachine->AddState(winState);

	loadingState->OnEnterEvent = std::bind(&AppMarioGame::OnLoading, this, std::placeholders::_1);
}

void AppMarioGame::OnLoading(int id)
{
	levelManager.GetLevel(0)->LoadMap("Textures/TexturesLevel_1.txt", "Tiles/JsonFiles/Level_1.json", 0);

	zengine->CharacterInputHandlerInitialize();

	waitingRoomState = new WaitingRoomState((int)State::EAppState::WaitingRoomState, stateMachine, (int)State::EAppState::GameplayState);
	stateMachine->DeleteState((int)State::EAppState::WaitingRoomState);
	stateMachine->AddState(waitingRoomState);
	stateMachine->TransitionTo((int)State::EAppState::WaitingRoomState);

	// To jest brzydki hack i nie powinno tego byæ. 
	// Ale na szczêœcie ¯aneta naprawi.
	zengine->gameMode = true;
}

World* AppMarioGame::GetWorld()
{
	return levelManager.GetLevel(0);
}

void AppMarioGame::Tick(float DeltaTime)
{
	// Tutaj updatujemy state maszyne.
	stateMachine->Update();
	level->gameStateId = GetGameState();
}

void AppMarioGame::Uninitialize()
{
	
}

int AppMarioGame::GetGameState()
{
	return stateMachine->GetCurrentGameStateId();
}

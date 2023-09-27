#include "AppMarioGame.h"

#include <Zengine/Zengine.h>
#include <Zengine/StateMachine/StateMachine.h>
#include <Zengine/World/World.h>
#include <Zengine/InputModule/CharacterInputHandler.h>
#include <Zengine/InputModule/InputProcessorModule.h>

#include "../StateMachine/MainMenuState.h"
#include "../StateMachine/LoadingState.h"
#include "../StateMachine/GameplayState.h"
#include "../StateMachine/ControlsPanelState.h"
#include "../StateMachine/AuthorsState.h"
#include "../StateMachine/WaitingRoomState.h"
#include "../StateMachine/GameOverState.h"
#include "../StateMachine/WinState.h"
#include "../World/Level1.h"
#include "../Character/Character.h"

AppMarioGame::AppMarioGame()
{
	level1 = new Level1();
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
	delete level1;
	delete zengine;
}

void AppMarioGame::Initialize(Zengine* zengine)
{
	this->zengine = zengine;
	this->stateMachine = zengine->GetStateMachine();
	this->renderStack = zengine->GetRenderingStack();
	this->renderModule = zengine->GetRenderer();

	StateInitialize();
	stateMachine->TransitionTo(State::MainMenuState);
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
	level1->Draw(renderStack);

	renderStack->DivisionOfObjectsIntoLayersByLayerId();
	renderModule->SortRenderLayers(renderStack);

	zengine->CharacterInputHandlerInitialize();

	waitingRoomState = new WaitingRoomState(0, stateMachine, 3);
	stateMachine->DeleteState(0);
	stateMachine->AddState(waitingRoomState);
	stateMachine->TransitionTo(0);
}

World* AppMarioGame::GetWorld()
{
	return level1;
}
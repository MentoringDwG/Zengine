#include "AppMarioGame.h"

#include "../StateMachine/StateMachine.h"
#include "../StateMachine/MainMenuState.h"
#include "../StateMachine/LoadingState.h"
#include "../StateMachine/GameplayState.h"
#include "../StateMachine/ControlsPanelState.h"
#include "../StateMachine/AuthorsState.h"
#include "../StateMachine/WaitingRoomState.h"

#include "../World/World.h"
#include "../InputModule/CharacterInputHandler.h"
#include "../InputModule/InputProcessorModule.h"
#include "../Character/Character.h"
#include "../Zengine.h"

AppMarioGame::AppMarioGame(StateMachine* stateMachine, RenderingStack* renderStack, Renderer* renderModule, World* world)
{
	this->stateMachine = stateMachine;
	this->renderStack = renderStack;
	this->renderModule = renderModule;
	this->world = world;
}

AppMarioGame::~AppMarioGame()
{
	delete stateMachine;
	delete mainMenuState;
	delete loadingState;
	delete gameplayState;
	delete waitingRoomState;
	delete controlsPanelState;
	delete authorsState;
	delete renderStack;
	delete renderModule;
	delete world;
	delete zengine;
}

void AppMarioGame::Initialize(Zengine* zengine)
{
	this->zengine = zengine;
	StateInitialize();
	stateMachine->TransitionTo(State::MainMenuState);
}

void AppMarioGame::StateInitialize()
{
	mainMenuState = new MainMenuState(State::MainMenuState, renderStack, stateMachine, renderModule);
	loadingState = new LoadingState(State::LoadingState, stateMachine);
	gameplayState = new GameplayState(State::GameplayState);
	controlsPanelState = new ControlsPanelState(State::ControlsPanelState, renderStack, stateMachine);
	authorsState = new AuthorsState(State::AuthorsState, renderStack, stateMachine);

	stateMachine->AddState(mainMenuState);
	stateMachine->AddState(loadingState);
	stateMachine->AddState(gameplayState);
	stateMachine->AddState(controlsPanelState);
	stateMachine->AddState(authorsState);

	loadingState->OnEnterEvent = std::bind(&AppMarioGame::OnLoading, this, std::placeholders::_1);
}

void AppMarioGame::OnLoading(int id)
{
	world->Draw(renderStack);

	renderStack->DivisionOfObjectsIntoLayersByLayerId();
	renderModule->SortRenderLayers(renderStack);

	zengine->CharacterInputHandlerInitialize();

	waitingRoomState = new WaitingRoomState(0, stateMachine, 3);
	stateMachine->DeleteState(0);
	stateMachine->AddState(waitingRoomState);
	stateMachine->TransitionTo(0);
}
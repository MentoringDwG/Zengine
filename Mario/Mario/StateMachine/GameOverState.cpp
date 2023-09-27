#include "GameOverState.h"
#include <Zengine/InputModule/UIInputHandler.h>
#include <Zengine/UI/UIButton.h>
#include <Zengine/ZenObject/ZenShape.h>
#include "WaitingRoomState.h"

void GameOverState::OnEnter(int prevStateId)
{
	gameOverPanel = new ZenShape(1, "GameOverPanel", sf::Vector2f(960, 544));
	gameOverPanel->SetSize(sf::Vector2f(960, 544));

	panelTexture = new sf::Texture();
	panelTexture->loadFromFile("Graphics/GameOver/gameOver.png");

	gameOverPanel->SetTexture(panelTexture);
	gameOverPanel->SetPosition(sf::Vector2f(0, 0));

	panelRenderObject = new RenderObject(gameOverPanel->Draw(), 1, 1);
	renderStack->renderQueue.push_back(panelRenderObject);

	back = new UIButton(Vector2(30, 230), Vector2(106, 50));
	back->Draw(renderStack, "Graphics/Control/back.png", sf::IntRect(0, 0, 53, 25), 2, "MenuBack");
	back->SetHighlight("Graphics/Control/backH.png");

	UIInputHandler::Get()->AddWidget(back);
	renderStack->DivisionOfObjectsIntoLayersByLayerId();

	back->OnMouseDownEvent.AddListener(&GameOverState::BackToMainMenu, this);
}

void GameOverState::OnUpdate()
{

}

void GameOverState::OnLeave(int nextStateId)
{
	renderStack->Clear();
	delete gameOverPanel;
	delete panelTexture;
	delete panelRenderObject;
	delete back;
}

GameOverState::GameOverState(int stateIdIn, RenderingStack* renderStackIn, StateMachine* stateMachineIn) : BaseGameState(stateIdIn)
{
	renderStack = renderStackIn;
	stateMachine = stateMachineIn;
}

GameOverState::~GameOverState()
{
	delete gameOverPanel;
	delete panelTexture;
	delete panelRenderObject;
	delete renderStack;
	delete back;
	delete waitingRoomState;
	delete stateMachine;
}

void GameOverState::BackToMainMenu(int id)
{
	UIInputHandler::Get()->Clear();

	waitingRoomState = new WaitingRoomState(State::WaitingRoomState, stateMachine, 1);
	stateMachine->DeleteState(State::WaitingRoomState);
	stateMachine->AddState(waitingRoomState);
	stateMachine->TransitionTo(State::WaitingRoomState);
}
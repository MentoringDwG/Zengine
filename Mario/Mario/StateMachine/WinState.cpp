#include "WinState.h"
#include <Zengine/InputModule/UIInputHandler.h>
#include <Zengine/UI/UIButton.h>
#include <Zengine/ZenObject/ZenShape.h>
#include "WaitingRoomState.h"

void WinState::OnEnter(int prevStateId)
{
	winPanel = new ZenShape(1, "GameOverPanel", sf::Vector2f(960, 544));
	winPanel->SetSize(sf::Vector2f(960, 544));

	panelTexture = new sf::Texture();
	panelTexture->loadFromFile("Graphics/Win/win.png");

	winPanel->SetTexture(panelTexture);
	winPanel->SetPosition(sf::Vector2f(0, 0));

	panelRenderObject = new RenderObject(winPanel->Draw(), 1, 1);
	renderStack->renderQueue.push_back(panelRenderObject);

	back = new UIButton(Vector2(40, 210), Vector2(106, 50));
	back->Draw(renderStack, "Graphics/Control/back.png", sf::IntRect(0, 0, 53, 25), 2, "MenuBack");
	back->SetHighlight("Graphics/Control/backH.png");

	UIInputHandler::Get()->AddWidget(back);
	renderStack->DivisionOfObjectsIntoLayersByLayerId();

	back->OnMouseDownEvent.AddListener(&WinState::BackToMainMenu, this);
}

void WinState::OnUpdate()
{

}

void WinState::OnLeave(int nextStateId)
{
	renderStack->Clear();
	renderStack->ClearUI();
	delete winPanel;
	delete panelTexture;
	delete panelRenderObject;
	delete back;
}

WinState::WinState(int stateIdIn, RenderingStack* renderStackIn, StateMachine* stateMachineIn) : BaseGameState(stateIdIn)
{
	renderStack = renderStackIn;
	stateMachine = stateMachineIn;
}

WinState::~WinState()
{
	delete winPanel;
	delete panelTexture;
	delete panelRenderObject;
	delete renderStack;
	delete back;
	delete waitingRoomState;
	delete stateMachine;
}

void WinState::BackToMainMenu(int id)
{
	UIInputHandler::Get()->Clear();

	waitingRoomState = new WaitingRoomState(State::WaitingRoomState, stateMachine, 1);
	stateMachine->DeleteState(State::WaitingRoomState);
	stateMachine->AddState(waitingRoomState);
	stateMachine->TransitionTo(State::WaitingRoomState);
}

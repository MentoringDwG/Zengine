#include "ControlsPanelState.h"
#include "WaitingRoomState.h"
#include <Zengine/StateMachine/StateMachine.h>
#include <Zengine/InputModule/UIInputHandler.h>
#include <Zengine/UI/UIButton.h>
#include <Zengine/ZenObject/ZenShape.h>

ControlsPanelState::~ControlsPanelState()
{
	delete contolsPanel;
	delete contolsPanelTexture;
	delete contolsPanelRenderObject;
	delete renderStack;
	delete back;
	delete waitingRoomState;
	delete stateMachine;
}

void ControlsPanelState::OnEnter(int prevStateId)
{
	contolsPanel = new ZenShape(1, "ControlsPanel", sf::Vector2f(960, 544));
	contolsPanel->SetSize(sf::Vector2f(960, 544));

	contolsPanelTexture = new sf::Texture();
	contolsPanelTexture->loadFromFile("Graphics/Control/controlPanel.png");

	contolsPanel->SetTexture(contolsPanelTexture);
	contolsPanel->SetPosition(sf::Vector2f(0, 0));

	contolsPanelRenderObject = new RenderObject(contolsPanel->Draw(), 1, 1);
	renderStack->renderQueue.push_back(contolsPanelRenderObject);

	back = new UIButton(Vector2(30, 230), Vector2(106, 50));
	back->Draw(renderStack, "Graphics/Control/back.png", sf::IntRect(0, 0, 53, 25), 2, "MenuBack");
	back->SetHighlight("Graphics/Control/backH.png");
	
	UIInputHandler::Get()->AddWidget(back);
	renderStack->DivisionOfObjectsIntoLayersByLayerId();

	back->OnMouseDownEvent.AddListener(&ControlsPanelState::BackToMainMenu, this);
}

void ControlsPanelState::BackToMainMenu(int id)
{
	UIInputHandler::Get()->Clear();

	waitingRoomState = new WaitingRoomState(State::WaitingRoomState, stateMachine, 1);
	stateMachine->DeleteState(State::WaitingRoomState);
	stateMachine->AddState(waitingRoomState);
	stateMachine->TransitionTo(State::WaitingRoomState);
}

void ControlsPanelState::OnUpdate()
{

}

void ControlsPanelState::OnLeave(int nextStateId)
{
	renderStack->Clear();
	renderStack->ClearUI();
	delete contolsPanel;
	delete contolsPanelTexture;
	delete contolsPanelRenderObject;
	delete back;
}
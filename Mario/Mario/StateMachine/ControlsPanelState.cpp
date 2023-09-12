#include "ControlsPanelState.h"
#include "WaitingRoomState.h"
#include "../../../Zengine/Zengine/StateMachine/StateMachine.h"
#include "../../../Zengine/Zengine/InputModule/UIInputHandler.h"
#include "../../../Zengine/Zengine/UI/UIButton.h"
#include "../../../Zengine/Zengine/ZenObject/ZenShape.h"

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

	waitingRoomState = new WaitingRoomState(0, stateMachine, 1);
	stateMachine->DeleteState(0);
	stateMachine->AddState(waitingRoomState);
	stateMachine->TransitionTo(0);
}

void ControlsPanelState::OnUpdate()
{

}

void ControlsPanelState::OnLeave(int nextStateId)
{
	renderStack->Clear();
	delete contolsPanel;
	delete contolsPanelTexture;
	delete contolsPanelRenderObject;
	delete back;
}
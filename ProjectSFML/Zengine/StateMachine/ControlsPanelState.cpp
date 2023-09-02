#include "ControlsPanelState.h"

void ControlsPanelState::OnEnter(int prevStateId)
{
	contolsPanel = new ZenShape(1, "ControlsPanel", sf::Vector2f(960, 544));
	contolsPanel->SetSize(sf::Vector2f(960, 544));

	contolsPanelTexture = new sf::Texture();
	contolsPanelTexture->loadFromFile("Graphics/Sterowanie/SterowaniePanel.png");

	contolsPanel->SetTexture(contolsPanelTexture);
	contolsPanel->SetPosition(sf::Vector2f(0, 0));

	contolsPanelRenderObject = new RenderObject(contolsPanel->Draw(), 1, 1);
	renderStack->renderQueue.push_back(contolsPanelRenderObject);

	back = new UIButton(Vector2(30, 230), Vector2(106, 50));
	back->Draw(renderStack, "Graphics/Sterowanie/back.png", sf::IntRect(0, 0, 53, 25), 2, "MenuBack");
	back->SetHighlight("Graphics/Sterowanie/backH.png");
	
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
#include "AuthorsState.h"

void AuthorsState::OnEnter(int prevStateId)
{
	authorsPanel = new ZenShape(1, "ControlsPanel", sf::Vector2f(960, 544));
	authorsPanel->SetSize(sf::Vector2f(960, 544));

	authorsPanelTexture = new sf::Texture();
	authorsPanelTexture->loadFromFile("Graphics/Autorzy/autorzy.png");

	authorsPanel->SetTexture(authorsPanelTexture);
	authorsPanel->SetPosition(sf::Vector2f(0, 0));

	authorsPanelRenderObject = new RenderObject(authorsPanel->Draw(), 1, 1);
	renderStack->renderQueue.push_back(authorsPanelRenderObject);

	back = new UIButton(Vector2(30, 230), Vector2(106, 50));
	back->Draw(renderStack, "Graphics/Sterowanie/back.png", 2, "MenuBack");
	back->SetHighlight("Graphics/Sterowanie/backH.png");

	UIInputHandler::Get()->AddWidget(back);
	renderStack->DivisionOfObjectsIntoLayersByLayerId();

	back->OnMouseDownEvent.AddListener(&AuthorsState::BackToMainMenu, this);
}

void AuthorsState::OnUpdate()
{

}

void AuthorsState::OnLeave(int nextStateId)
{
	renderStack->Clear();
	delete authorsPanel;
	delete authorsPanelTexture;
	delete authorsPanelRenderObject;
	delete back;
}

void AuthorsState::BackToMainMenu(int id)
{
	UIInputHandler::Get()->Clear();

	waitingRoomState = new WaitingRoomState(0, stateMachine, 1);
	stateMachine->DeleteState(0);
	stateMachine->AddState(waitingRoomState);
	stateMachine->TransitionTo(0);
}
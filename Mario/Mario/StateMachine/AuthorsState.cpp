#include "AuthorsState.h"
#include "WaitingRoomState.h"
#include "../../../Zengine/Zengine/StateMachine/StateMachine.h"
#include "../../../Zengine/Zengine/InputModule/UIInputHandler.h"
#include "../../../Zengine/Zengine/UI/UIButton.h"
#include "../../../Zengine/Zengine/ZenObject/ZenShape.h"

AuthorsState::~AuthorsState()
{
	delete authorsPanel;
	delete authorsPanelTexture;
	delete authorsPanelRenderObject;
	delete renderStack;
	delete back;
	delete waitingRoomState;
	delete stateMachine;
}

void AuthorsState::OnEnter(int prevStateId)
{
	authorsPanel = new ZenShape(1, "AuthorsPanel", sf::Vector2f(960, 544));
	authorsPanel->SetSize(sf::Vector2f(960, 544));

	authorsPanelTexture = new sf::Texture();
	authorsPanelTexture->loadFromFile("Graphics/Authors/authors.png");

	authorsPanel->SetTexture(authorsPanelTexture);
	authorsPanel->SetPosition(sf::Vector2f(0, 0));

	authorsPanelRenderObject = new RenderObject(authorsPanel->Draw(), 1, 1);
	renderStack->renderQueue.push_back(authorsPanelRenderObject);

	back = new UIButton(Vector2(30, 230), Vector2(106, 50));
	back->Draw(renderStack, "Graphics/Control/back.png", sf::IntRect(0, 0, 53, 25), 2, "MenuBack");
	back->SetHighlight("Graphics/Control/backH.png");

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
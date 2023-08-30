#include "MainMenuPanel.h"

#include "../StateMachine/StateMachine.h"

void MainMenuPanel::Initialize(StateMachine* stateMachine)
{
	buttons = new CompoundWidget(Vector2(682, 179), Vector2(228, 188));

	start = new UIButton(Vector2(682, 164), Vector2(228, 46));
	controls = new UIButton(Vector2(682, 225), Vector2(228, 46));
	authors = new UIButton(Vector2(682, 286), Vector2(228, 46));

	buttons->AddChild(1, start);
	buttons->AddChild(2, controls);
	buttons->AddChild(3, controls);

	logo = new ZenShape(11, "Logo", sf::Vector2f(344, 129));
	logo->SetSize(sf::Vector2f(344, 129));
	logoTexture = new sf::Texture();
	logoTexture->loadFromFile("Graphics/MainMenu/logo.png");
	logo->SetTexture(logoTexture);
	logo->SetPosition(sf::Vector2f(566, 20));

	volumeIcon = new UIButton(Vector2(72, 20), Vector2(42, 42));
	exitIcon = new UIButton(Vector2(20, 20), Vector2(42, 42));

	this->stateMachine = stateMachine;
}

void  MainMenuPanel::Draw(RenderingStack* renderStack)
{
	start->Draw(renderStack, "Graphics/MainMenu/Start.png", 13, "Start");
	controls->Draw(renderStack, "Graphics/MainMenu/Sterowanie.png", 14, "Controls");
	authors->Draw(renderStack, "Graphics/MainMenu/Autorzy.png", 15, "Authors");

	start->SetHighlight("Graphics/MainMenu/StartH.png");
	controls->SetHighlight("Graphics/MainMenu/SterowanieH.png");
	authors->SetHighlight("Graphics/MainMenu/AutorzyH.png");

	logoRenderObject = new RenderObject(logo->Draw(), 1, 2);
	renderStack->renderQueue.push_back(logoRenderObject);

	volumeIcon->Draw(renderStack, "Graphics/MainMenu/glosnik.png", 15, "Volume");
	volumeIcon->SetHighlight("Graphics/MainMenu/glosnikH.png");

	exitIcon->Draw(renderStack, "Graphics/MainMenu/wyjscie.png", 16, "Exit");
	exitIcon->SetHighlight("Graphics/MainMenu/wyjscieH.png");
}

void MainMenuPanel::ButtonsInputInitialize()
{
	UIInputHandler::Get()->AddWidget(start);
	UIInputHandler::Get()->AddWidget(controls);
	UIInputHandler::Get()->AddWidget(authors);

	UIInputHandler::Get()->AddWidget(volumeIcon);
	UIInputHandler::Get()->AddWidget(exitIcon);

	start->OnMouseDownEvent.AddListener(&MainMenuPanel::StartPressed, this);
	controls->OnMouseDownEvent.AddListener(&MainMenuPanel::ControlsPressed, this);
	authors->OnMouseDownEvent.AddListener(&MainMenuPanel::AuthorsPressed, this);
	exitIcon->OnMouseDownEvent.AddListener(&MainMenuPanel::ExitPressed, this);
}

void MainMenuPanel::StartPressed(int id)
{
	std::cout << "Start pressed" << std::endl;

	UIInputHandler::Get()->Clear();

	waitingRoonState = new WaitingRoomState(0, stateMachine, 2);
	stateMachine->DeleteState(0);
	stateMachine->AddState(waitingRoonState);
	stateMachine->TransitionTo(0);
}

void MainMenuPanel::ControlsPressed(int id)
{
	std::cout << "Controls pressed" << std::endl;

	UIInputHandler::Get()->Clear();

	waitingRoonState = new WaitingRoomState(0, stateMachine, 4);
	stateMachine->DeleteState(0);
	stateMachine->AddState(waitingRoonState);
	stateMachine->TransitionTo(0);
}


void MainMenuPanel::AuthorsPressed(int id)
{
	std::cout << "Authors pressed" << std::endl;
	UIInputHandler::Get()->Clear();

	waitingRoonState = new WaitingRoomState(0, stateMachine, 5);
	stateMachine->DeleteState(0);
	stateMachine->AddState(waitingRoonState);
	stateMachine->TransitionTo(0);
}

void MainMenuPanel::ExitPressed(int id)
{
	exit(0);
}
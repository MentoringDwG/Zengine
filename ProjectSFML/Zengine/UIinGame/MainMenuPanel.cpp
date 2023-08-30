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

	start->OnMouseHoverEvent.AddListener(&MainMenuPanel::StartHover, this);
	start->OnMouseUnHoverEvent.AddListener(&MainMenuPanel::StartUnHover, this);
	start->OnMouseDownEvent.AddListener(&MainMenuPanel::StartPressed, this);
	start->OnMouseUpEvent.AddListener(&MainMenuPanel::StartUnPressed, this);

	controls->OnMouseHoverEvent.AddListener(&MainMenuPanel::ControlsHover, this);
	controls->OnMouseUnHoverEvent.AddListener(&MainMenuPanel::ControlsUnHover, this);
	controls->OnMouseDownEvent.AddListener(&MainMenuPanel::ControlsPressed, this);
	controls->OnMouseUpEvent.AddListener(&MainMenuPanel::ControlsUnPressed, this);

	authors->OnMouseHoverEvent.AddListener(&MainMenuPanel::AuthorsHover, this);
	authors->OnMouseUnHoverEvent.AddListener(&MainMenuPanel::AuthorsUnHover, this);
	authors->OnMouseDownEvent.AddListener(&MainMenuPanel::AuthorsPressed, this);
	authors->OnMouseUpEvent.AddListener(&MainMenuPanel::AuthorsUnPressed, this);

	volumeIcon->OnMouseHoverEvent.AddListener(&MainMenuPanel::VolumeHover, this);
	volumeIcon->OnMouseUnHoverEvent.AddListener(&MainMenuPanel::VolumeUnHover, this);

	exitIcon->OnMouseHoverEvent.AddListener(&MainMenuPanel::ExitHover, this);
	exitIcon->OnMouseUnHoverEvent.AddListener(&MainMenuPanel::ExitUnHover, this);
	exitIcon->OnMouseDownEvent.AddListener(&MainMenuPanel::ExitPressed, this);
}

void MainMenuPanel::StartHover(int id)
{
	std::cout << "Start hover" << std::endl;
}

void MainMenuPanel::StartUnHover(int id)
{
	std::cout << "Start unhover" << std::endl;
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

void MainMenuPanel::StartUnPressed(int id)
{
	std::cout << "Start unpressed" << std::endl;
}


void MainMenuPanel::ControlsHover(int id)
{
	std::cout << "Controls hover" << std::endl;
}

void MainMenuPanel::ControlsUnHover(int id)
{
	std::cout << "Controls unhover" << std::endl;
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

void MainMenuPanel::ControlsUnPressed(int id)
{
	std::cout << "Controls unpressed" << std::endl;
}


void MainMenuPanel::AuthorsHover(int id)
{
	std::cout << "Authors hover" << std::endl;
}

void MainMenuPanel::AuthorsUnHover(int id)
{
	std::cout << "Authors unhover" << std::endl;
}

void MainMenuPanel::AuthorsPressed(int id)
{
	std::cout << "Authors pressed" << std::endl;
}

void MainMenuPanel::AuthorsUnPressed(int id)
{
	std::cout << "Authors unpressed" << std::endl;
}


void MainMenuPanel::VolumeHover(int id)
{

}

void MainMenuPanel::VolumeUnHover(int id)
{

}

void MainMenuPanel::ExitHover(int id)
{

}

void MainMenuPanel::ExitUnHover(int id)
{

}

void MainMenuPanel::ExitPressed(int id)
{
	exit(0);
}
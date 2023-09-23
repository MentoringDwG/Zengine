#include "MainMenuState.h"
#include "../../../Zengine/Zengine/InputModule/UIInputHandler.h"
#include "../../../Zengine/Zengine/Animation/Animator.h"
#include "../../../Zengine/Zengine/Animation/Animation.h"
#include "../../../Zengine/Zengine/Animation/AnimationDefinitionManager.h"
#include "../../../Zengine/Zengine/Animation/AnimationDefinition.h"
#include "../../../Zengine/Zengine/Animation/AnimationProcesor.h"

MainMenuState::MainMenuState(int stateIdIn, RenderingStack* renderStack, StateMachine* stateMachine, Renderer* renderer) : BaseGameState(stateIdIn)
{
	this->renderStack = new RenderingStack();
	this->renderStack = renderStack;
	this->renderer = renderer;
	this->stateMachine = stateMachine;

	AnimationDefinitionManager::Get()->AddAnimationDefinition("Json/Animations/mainMenu.json", "MainMenu");
	animation = new Animation(AnimationDefinitionManager::Get()->GetAnimationDefinition("MainMenu"));
}

MainMenuState::~MainMenuState()
{
	delete zenShape;
	delete texture;
	delete renderObject;
	delete renderStack;
	delete renderer;
	AnimationProcesor::Get()->DeleteAnimator(animator);
	delete animator;
	delete animation;
}

void MainMenuState::OnEnter(int prevStateId)
{
	zenShape = new ZenShape(10, "MainMenu", sf::Vector2f(960, 544));
	zenShape->SetSize(sf::Vector2f(960, 544));

	mainMenuPanel.Initialize(stateMachine);

	animator = new Animator(zenShape);
	animation = new Animation(AnimationDefinitionManager::Get()->GetAnimationDefinition("MainMenu"));
	animationId = animator->AddAnimation(animation);
	animator->SetCurrentAnimation(animationId);
	animator->Play();

	renderObject = new RenderObject(zenShape->Draw(), 1, 1);
	renderStack->renderQueue.push_back(renderObject);

	mainMenuPanel.Draw(renderStack);
	mainMenuPanel.ButtonsInputInitialize();

	renderStack->DivisionOfObjectsIntoLayersByLayerId();
	renderer->SortRenderLayers(renderStack);
}

void MainMenuState::OnUpdate()
{
	
}

void MainMenuState::OnLeave(int nextStateId)
{
	animator->Stop();
	renderStack->Clear();
	delete zenShape;
	delete texture;
	mainMenuPanel.~MainMenuPanel();
}
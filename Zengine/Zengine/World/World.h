#pragma once

#include "../InputModule/CharacterInputHandler.h"
#include "../Renderer/Renderer.h"

class World
{
public:
	virtual void Initialize(class StateMachine* stateMachine) = 0;
	virtual void MapInitialize() = 0;
	virtual void PhysicalZenObject2DInitialize() = 0;
	virtual void EnvironmentInitialize() = 0;
	virtual void ApplyForceToPhysicsObject() = 0;
	virtual void UpdateObjects() = 0;
	virtual void SetCamera(sf::View* mainCamera, struct Vector2 windowSize) = 0;
	virtual CharacterInputHandler* GetCharacterInputHandler() = 0;
	virtual void Draw(RenderingStack* renderStack) = 0;
};


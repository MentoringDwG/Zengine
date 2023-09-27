#pragma once

#include "../InputModule/CharacterInputHandler.h"

class World
{
public:
	virtual void Initialize(class StateMachine* stateMachine) = 0;
	virtual void MapInitialize() = 0;
	virtual void PhysicalZenObject2DInitialize() = 0;
	virtual void EnvironmentInitialize() = 0;
	virtual void ApplyForceToPhysicsObject() = 0;
	virtual void UpdateObjects() = 0;
	virtual void SetCamera(sf::View* mainCamera) = 0;
	virtual CharacterInputHandler* GetCharacterInputHandler() = 0;
};


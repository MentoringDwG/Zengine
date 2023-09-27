#pragma once

#include "../Character/Character.h"

class World
{
public:
	virtual void Initialize(class StateMachine* stateMachine) = 0;
	virtual void MapInitialize() = 0;
	virtual void PhysicalZenObject2DInitialize() = 0;
	virtual void EnvironmentInitialize() = 0;
	virtual void ApplyForceToPhysicsObject() = 0;
	virtual void UpdateObjects() = 0;
	virtual Character* GetPlayer() = 0;
};


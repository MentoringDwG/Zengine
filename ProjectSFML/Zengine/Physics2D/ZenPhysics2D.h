#pragma once
#include "PhysicalZenObject2D.h"
#include <vector>
#include <chrono>

class ZenPhysics2D
{
public:
	void RegisterPhysicalObject(PhysicalZenObject2D* physicalObject);
	void CalculatePhysics();
	std::chrono::nanoseconds GetPhysicsTimeStep();
	std::vector<PhysicalZenObject2D*> PhysicalObjects;

private:
	std::chrono::nanoseconds physicsTimeStep = (std::chrono::nanoseconds)30; // ms
	float globalGravity = 0.0f;
};


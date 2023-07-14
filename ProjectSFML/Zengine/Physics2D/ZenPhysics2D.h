#pragma once
#include "PhysicalZenObject2D.h"
#include <vector>
#include <chrono>

class ZenPhysics2D
{
public:
	void RegisterPhysicalObject(PhysicalZenObject2D* physicalObject);
	void RemovingObjectFromPhysics(PhysicalZenObject2D* physicalObject);
	void CalculatePhysics();
	int GetPhysicsTimeStep();

private:
	int physicsTimeStep = 30; // ms
	float globalGravity = 0.0f;

	std::vector<PhysicalZenObject2D*> PhysicalObjects;
};


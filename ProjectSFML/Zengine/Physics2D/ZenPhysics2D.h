#pragma once
#include "PhysicalZenObject2D.h"
#include <vector>

class ZenPhysics2D
{
public:
	void RegisterPhysicalObject(PhysicalZenObject2D* physicalObject);
	void CalculatePhysics();

private:
	float physicsTimeStep = 0.03; // 1/30 sekundy
	std::vector<PhysicalZenObject2D*> PhysicalObjects;
	float globalGravity = 0.0f;
};


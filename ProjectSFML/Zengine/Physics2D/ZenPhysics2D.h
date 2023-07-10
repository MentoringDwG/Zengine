#pragma once
#include "PhysicalZenObject2D.h"
#include <vector>

class ZenPhysics2D
{
public:
	void RegisterPhysicalObject(PhysicalZenObject2D* physicalObject);
	void CalculatePhysics();
	std::vector<PhysicalZenObject2D*> PhysicalObjects;

private:
	float physicsTimeStep = 0.03; // 1/30 sekundy
	float globalGravity = 0.0f;
};


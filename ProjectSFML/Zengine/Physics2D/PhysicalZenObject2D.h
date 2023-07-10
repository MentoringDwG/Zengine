#pragma once
#include "../ZenObject/ZenObject.h"

class PhysicalZenObject2D:public ZenObject
{
public:
	void CalculatePhysics();

private:
	float mass = 1.0f;
	float fakeDrag = 0.0f;
	float gravity = 0.0f;

	std::vector<float> velocity;
	std::vector<float> transposition;

	//Variable to debug
	std::vector<float> acceleration;
};


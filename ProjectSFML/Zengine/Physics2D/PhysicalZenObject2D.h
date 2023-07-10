#pragma once
#include "../ZenObject/ZenObject.h"
#include "../Renderer/Renderer.h"

class PhysicalZenObject2D:public ZenObject
{
public:

	PhysicalZenObject2D(int IDIn, string NameIn) :ZenObject(IDIn, NameIn)
	{

	}

	void CalculatePhysics();
	void Draw(RenderingStack* renderStack);

private:
	float mass = 1.0f;
	float fakeDrag = 0.0f;
	float gravity = 0.0f;

	std::vector<float> velocity;
	std::vector<float> transposition;

	RenderObject* physicalRenderObject = nullptr;

	//Variable to debug
	std::vector<float> acceleration;
};


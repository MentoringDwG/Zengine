#pragma once
#include "../ZenObject/ZenObject.h"
#include "../Renderer/Renderer.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class PhysicalZenObject2D:public ZenObject
{
public:
	enum ForceDirection;
	ForceDirection forceDirection;
	PhysicalZenObject2D(int IDIn, string NameIn, string enemySpritePath, sf::Vector2f startPosition);
	void CalculatePhysics();
	void Draw(RenderingStack* renderStack);
	void AddForce(float mass, float force, float time, int direction);
	float GetTransposition();

private:
	float mass = 1.0f;
	float fakeDrag = 0.0f;
	float gravity = 0.0f;
	float force = 1.0f;
	float slowdownPercentage = 1;
	int direction = 1;

	std::vector<float> velocity;
	std::vector<float> transposition;
	std::vector<float> acceleration;

	RenderObject* physicalRenderObject = nullptr;

	void ResettingVariables();
};


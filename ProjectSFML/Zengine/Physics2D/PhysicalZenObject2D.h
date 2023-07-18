#pragma once

#include "../ZenObject/ZenObject.h"
#include "../Renderer/Renderer.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Structs/Vector2.h"
#include "../ZenObject/ZenShape.h"

class PhysicalZenObject2D:public ZenObject
{
public:
	ZenShape* zenShape;
	PhysicalZenObject2D(int IDIn, string NameIn, string enemySpritePath, sf::Vector2f startPosition, sf::Vector2f sizeIn);
	void CalculatePhysics();
	void AddForce(float mass, float force, float time);
	float GetTransposition();
	float GetVelocityX();

private:
	float mass = 1.0f;
	float fakeDrag = 1.0f;
	float gravity = 0.0f;
	float force = 1.0f;

	Vector2* velocity;
	Vector2* transposition;
	Vector2* acceleration;

	void ResettingVariables();
};


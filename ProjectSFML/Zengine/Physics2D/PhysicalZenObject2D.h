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
	PhysicalZenObject2D(int inID, string inName, string enemySpritePath, sf::Vector2f startPosition, sf::Vector2f inSize, class Collider* inCollider);
	void CalculatePhysics();
	void AddForce(float mass, Vector2 force, float time);

	Vector2* GetTransposition();
	Vector2* GetVelocity();

	void SetGravity(float gravity);
	float GetGravity();

private:
	float mass = 1.0f;
	float fakeDrag = 0.05f;
	float gravity = 0.0f;
	Vector2* force;

	Vector2* velocity;
	Vector2* transposition;
	Vector2* acceleration;

	class Collider* collider;
	void ResettingVariables();
};


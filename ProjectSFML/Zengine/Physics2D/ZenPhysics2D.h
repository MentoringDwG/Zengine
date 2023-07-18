#pragma once

#include <vector>
#include "PhysicalZenObject2D.h"
#include "../Colliders/CircleCollider2D.h"

class ZenPhysics2D
{
public:
	void RegisterPhysicalObject(PhysicalZenObject2D* physicalObject);
	void RemovingObjectFromPhysics(PhysicalZenObject2D* physicalObject);
	void CalculatePhysics();
	void RegisterCollider(CircleCollider2D* collider);
	void RemovingCollider(CircleCollider2D* collider);
	void CalculateCollision();
	void Draw(RenderingStack* renderStack);
	void DrawColliders(sf::RenderWindow* window);
	int GetPhysicsTimeStep();

private:
	int physicsTimeStep = 30;	//0.03 seconds
	float globalGravity = 0.0f;

	std::vector<PhysicalZenObject2D*> PhysicalObjects;
	std::vector<CircleCollider2D*> colliders;
};


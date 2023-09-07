#pragma once

#include <vector>
#include "PhysicalZenObject2D.h"
#include "../Colliders/CircleCollider2D.h"
#include "../Colliders/BoxCollider2D.h"

class ZenPhysics2D
{
public:
	static ZenPhysics2D* Get() { return &instance; }

	void RegisterPhysicalObject(PhysicalZenObject2D* physicalObject);
	void RemovingObjectFromPhysics(PhysicalZenObject2D* physicalObject);

	void CalculatePhysics();

	void RegisterCollider(CircleCollider2D* collider);
	void RegisterCollider(BoxCollider2D* collider);

	void UnregisterCollider(CircleCollider2D* collider);
	void UnregisterCollider(BoxCollider2D* collider);

	void CalculateCollision();

	void Draw(RenderingStack* renderStack);
	void DrawColliders(sf::RenderWindow* window);
	int GetPhysicsTimeStep();

	void SetShouldShowDebug(bool bInShowDebug);
private:
	ZenPhysics2D() {}

	static ZenPhysics2D instance;

	int physicsTimeStep = 30;	//0.03 seconds
	float globalGravity = 0.0f;
	bool bShouldDrawDebug = true;

	std::vector<PhysicalZenObject2D*> physicalObjects;
	std::vector<CircleCollider2D*> circleColliders;
	std::vector<BoxCollider2D*> boxColliders;
};


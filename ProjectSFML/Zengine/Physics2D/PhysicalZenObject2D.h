#pragma once

#include "../ZenObject/ZenObject.h"
#include "../Renderer/Renderer.h"
#include "../ZenObject/ZenShape.h"
#include "../Colliders/Collider.h"
#include <SFML/Graphics.hpp>

struct Vector2;
class Collider;

class PhysicalZenObject2D:public ZenObject
{
public:
	enum class CollisionPushSide
	{
		NONE = 0,
		TOP = 1,
		BOTTOM = 2,
		RIGHT = 3,
		LEFT = 4,
		Max,
	};

	PhysicalZenObject2D(int inID, string inName, string enemySpritePath, sf::Vector2f startPosition, sf::Vector2f inSize);
	~PhysicalZenObject2D();

	void CalculatePhysics();
	void AddForce(float mass, Vector2 force, float time);
	Vector2* GetTransposition();
	Vector2* GetVelocity();
	void SetCollider(Collider* collider);
	void SetGravity(float gravity);
	float GetGravity();

	CollisionPushSide collisionPushSide = CollisionPushSide::NONE;
	ZenShape* zenShape = nullptr;

private:
	void CalculationColliderPush();
	void ResettingVariables();
	void HandleCollisionStart(Collider* other);
	void HandleCollisionEnd(Collider* other);

	std::map<Collider::ColliderTags, std::vector<Collider*>> collisionColliders;
	float mass = 1.0f;
	float fakeDrag = 0.05f;
	float gravity = 0.0f;
	Vector2 force = Vector2(0 ,0);
	Vector2 velocity = Vector2(0, 0);
	Vector2 transposition = Vector2(0.1, 0);
	Vector2 acceleration = Vector2(0, 0);
	Collider* collider = nullptr;
	bool canUseGravity = false;
};


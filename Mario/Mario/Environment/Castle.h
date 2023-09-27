#pragma once

#include <iostream>
#include <Zengine/ZenObject/ZenObject.h>

struct Vector2;

class Castle : public ZenObject
{
public:
	Castle(Vector2 size, Vector2 position, class StateMachine* stateMachineIn);
private:
	void HandleCollisionStart(class Collider* other);
	void HandleCollisionEnd(Collider* other);

	class BoxCollider2D* boxCollider = nullptr;
	class StateMachine* stateMachine = nullptr;
	bool isCollisionWithMario = false;

	const std::string MARIO = "Mario";
};


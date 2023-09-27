#pragma once

#include <Zengine/ZenObject/ZenObject.h>

struct Vector2;

class Confiner
{
public:
	Confiner(Vector2 size, Vector2 positionLeftCollider, Vector2 positionRightCollider);
	void SetPositionLeft(Vector2 positionLeftCollider);

private:
	class BoxCollider2D* boxColliderLeft = nullptr;
	class ZenObject* leftConfiner = nullptr;

	class BoxCollider2D* boxColliderRight = nullptr;
	class ZenObject* rightConfiner = nullptr;
};


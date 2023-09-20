#pragma once

struct Vector2;

class Castle
{
public:
	Castle(Vector2 size, Vector2 position);
private:
	void HandleCollisionStart(class Collider* other);
	void HandleCollisionEnd(Collider* other);

	class BoxCollider2D* boxCollider = nullptr;
	class ZenObject* zenObject = nullptr;
	bool isCollisionWithMario = false;
};


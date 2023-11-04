#pragma once

#include <Zengine/Renderer/Renderer.h>
#include <Zengine/ZenObject/ZenShape.h>

class Key
{
public:
	Key(int IDIn, string NameIn, string KeyPath, sf::Vector2f position);
	~Key();

	void Draw(RenderingStack* renderStack);
	void SetCollider(struct Vector2 position, float radius);

private:
	void HandleCollisionStart(class Collider* other);

	int animationId = 0;
	int listenerIndexStart = 0;
	int listenerIndexEnd = 0;
	ZenShape* zenShape = nullptr;
	RenderObject* keyRenderObject = nullptr;
	RenderingStack* renderStack = nullptr;
	class CircleCollider2D* collider = nullptr;
	class Animation* animation = nullptr;
	class Animator* animator = nullptr;
};


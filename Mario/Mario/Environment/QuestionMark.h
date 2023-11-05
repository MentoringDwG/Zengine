#pragma once

#include <Zengine/Renderer/Renderer.h>
#include <Zengine/ZenObject/ZenShape.h>

class QuestionMark
{
public:
	QuestionMark(int IDIn, string NameIn, string KeyPath, sf::Vector2f position);
	~QuestionMark();

	void Draw(RenderingStack* renderStack);
	void SetCollider(struct Vector2 position);

private:
	void HandleCollisionStart(class Collider* other);

	int animationId = 0;
	int listenerIndexStart = 0;
	int listenerIndexEnd = 0;
	ZenShape* zenShape = nullptr;
	RenderObject* questionMarkRenderObject = nullptr;
	RenderingStack* renderStack = nullptr;
	class BoxCollider2D* boxCollider = nullptr;
	class Animation* animation = nullptr;
	class Animator* animator = nullptr;
};


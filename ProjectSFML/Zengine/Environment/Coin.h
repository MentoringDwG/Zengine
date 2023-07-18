#pragma once

#include "../ZenObject/ZenShape.h"
#include "../Renderer/Renderer.h"
#include "../Colliders/CircleCollider2D.h"
#include "../Physics2D/ZenPhysics2D.h"

class Coin
{
public:
	Coin(int IDIn, string NameIn, string CoinPath, sf::Vector2f position);
	void Draw(RenderingStack* renderStack);
	void SetCollider(Vector2* position, float radius, ZenPhysics2D* zenPhysics2D);

private:
	ZenShape* zenShape = nullptr;
	RenderObject* coinRenderObject = nullptr;
	CircleCollider2D* collider = nullptr;
	ZenPhysics2D* zenPhysics2D = nullptr;

	void HandleCollisionStart(CircleCollider2D* other);
};


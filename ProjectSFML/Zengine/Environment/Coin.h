#pragma once

#include "../ZenObject/ZenShape.h"
#include "../Renderer/Renderer.h"
#include "../Colliders/CircleCollider2D.h"
#include "../Physics2D/ZenPhysics2D.h"
#include "../Environment/CoinCounter.h"

class Coin
{
public:
	Coin(int IDIn, string NameIn, string CoinPath, sf::Vector2f position, CoinCounter* coinCounter);
	void Draw(RenderingStack* renderStack);
	void SetCollider(Vector2* position, float radius);

private:
	ZenShape* zenShape = nullptr;
	RenderObject* coinRenderObject = nullptr;
	RenderingStack* renderStack = nullptr;
	CircleCollider2D* collider = nullptr;
	CoinCounter* coinCounter = nullptr;

	void HandleCollisionStart(CircleCollider2D* other);
	void HandleCollisionEnd(BoxCollider2D* other);
};


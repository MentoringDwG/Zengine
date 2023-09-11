#pragma once

#include "../Renderer/Renderer.h"
#include "../ZenObject/ZenShape.h"

class CoinCounter;

class Coin
{
public:
	Coin(int IDIn, string NameIn, string CoinPath, sf::Vector2f position, CoinCounter* coinCounter);
	~Coin();

	void Draw(RenderingStack* renderStack);
	void SetCollider(struct Vector2 position, float radius);

private:
	void HandleCollisionStart(class Collider* other);

	int listenerIndexStart = 0;
	int listenerIndexEnd = 0;
	ZenShape* zenShape = nullptr;
	RenderObject* coinRenderObject = nullptr;
	RenderingStack* renderStack = nullptr;
	class CircleCollider2D* collider = nullptr;
	CoinCounter* coinCounter = nullptr;
};


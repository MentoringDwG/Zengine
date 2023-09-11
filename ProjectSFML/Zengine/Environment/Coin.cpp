#include "Coin.h"
#include "../Environment/CoinCounter.h"
#include "../Physics2D/ZenPhysics2D.h"
#include "../Colliders/CircleCollider2D.h"
#include "../Colliders/Collider.h"
#include "../Structs/Vector2.h"

Coin::Coin(int IDIn, string NameIn, string CoinPath, sf::Vector2f position, CoinCounter* coinCounter)
{
	zenShape = new ZenShape(IDIn, NameIn, sf::Vector2f(32, 32));
	zenShape->SetTexture(CoinPath);
	zenShape->SetPosition(position);
	zenShape->SetSize(sf::Vector2f(32, 32));

	this->coinCounter = coinCounter;
	SetCollider(Vector2(position.x, position.y), 20);
}

Coin::~Coin()
{
	delete zenShape;
	delete coinRenderObject;
	delete renderStack;
	delete collider;
	delete coinCounter;
}

void Coin::Draw(RenderingStack* renderStack)
{
	this->renderStack = renderStack;
	coinRenderObject = new RenderObject(zenShape->Draw(), 100, 1);
	renderStack->renderQueue.push_back(coinRenderObject);
}

void Coin::SetCollider(Vector2 position, float radius)
{
	collider = new CircleCollider2D(position, radius, zenShape, Collider::ColliderTags::COIN);
	listenerIndexStart = collider->OnCollisionStart.AddListener(&Coin::HandleCollisionStart, this);
	ZenPhysics2D::Get()->RegisterCollider(collider);
}

void Coin::HandleCollisionStart(Collider* other)
{
	if (other->GetOwner()->name == "Mario")
	{
		renderStack->RemoveFromRenderLayers(coinRenderObject);
		ZenPhysics2D::Get()->UnregisterCollider(collider);

		coinCounter->IncrementCounter();
	}
}


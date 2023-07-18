#include "Coin.h"

Coin::Coin(int IDIn, string NameIn, string CoinPath, sf::Vector2f position)
{
	zenShape = new ZenShape(IDIn, NameIn, sf::Vector2f(32, 32));
	zenShape->SetTexture(CoinPath);
	zenShape->SetPosition(position);
	zenShape->SetSize(sf::Vector2f(32, 32));
}

void Coin::Draw(RenderingStack* renderStack)
{
	coinRenderObject = new RenderObject(zenShape->Draw(), 100, 1);
	renderStack->renderQueue.push_back(coinRenderObject);
}

void Coin::SetCollider(Vector2* position, float radius, ZenPhysics2D* zenPhysics2D)
{
	collider = new CircleCollider2D(position, radius, zenShape);
	collider->OnCollisionStart = std::bind(&Coin::HandleCollisionStart, this, std::placeholders::_1);
	zenPhysics2D->RegisterCollider(collider);
}

void Coin::HandleCollisionStart(CircleCollider2D* other)
{
	if (other->GetOwner()->Name == "Mario")
	{
		cout << "Jest kolizja z: " << other->GetOwner()->Name<<endl;
	}
}
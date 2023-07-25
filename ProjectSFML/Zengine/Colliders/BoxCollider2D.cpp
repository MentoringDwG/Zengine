#include "BoxCollider2D.h"

BoxCollider2D::BoxCollider2D(Vector2* position, Vector2* size, ZenObject* owner)
{
	this->position = position;
	this->size = size;
	SetOwner(owner);

	debugRectangleShape.setSize(sf::Vector2f(size->x, size->y));

	debugRectangleShape.setFillColor(sf::Color::Transparent);
	debugRectangleShape.setOutlineColor(sf::Color::Green);
	debugRectangleShape.setOutlineThickness(1);

	SetPosition(sf::Vector2f(position->x, position->y));
}

void BoxCollider2D::SetOwner(ZenObject* owner)
{
	this->owner = owner;
}

bool BoxCollider2D::CheckBoxCollision(BoxCollider2D* other)
{
	if (other->debugRectangleShape.getGlobalBounds().intersects(debugRectangleShape.getGlobalBounds()))
	{
		bIsColliding=true;
	}
	else
	{
		bIsColliding=false;
	}

	if (HasCollision())
	{
		OnBoxCollisionStart(other);
	}

	return bIsColliding;
}

bool BoxCollider2D::CheckCircleCollision(CircleCollider2D* other)
{
	//to trzeba przemyœleæ 
}

bool BoxCollider2D::HasCollision()
{
	return bIsColliding;
}

void BoxCollider2D::SetPosition(sf::Vector2f vector)
{
	debugRectangleShape.setPosition(vector);
	position->x = vector.x;
	position->y = vector.y;
}

ZenObject* BoxCollider2D::GetOwner()
{
	return owner;
}
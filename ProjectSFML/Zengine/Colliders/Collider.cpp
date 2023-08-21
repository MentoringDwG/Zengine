
#include "Collider.h"

Collider::Collider(ColliderTags tag)
{
	position = new Vector2(0, 0);
	this->tag = tag;
}

void Collider::SetOwner(ZenObject* inOwner)
{
	owner = inOwner;
}

void Collider::SetPosition(sf::Vector2f vector)
{
	position->x = vector.x + owner->size.x / 2;
	position->y = vector.y + owner->size.y / 2;
}

ZenObject* Collider::GetOwner()
{
	return owner;
}

Vector2* Collider::GetPosition()
{
	return position;
}
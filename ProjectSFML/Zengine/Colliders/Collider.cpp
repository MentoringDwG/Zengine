#include "Collider.h"
#include "../ZenObject/ZenObject.h"

Collider::Collider(ColliderTags tag, Vector2* size)
{
	this->tag = tag;
	this->size = *size;
}

Collider::~Collider()
{
	delete owner;
}

void Collider::SetOwner(ZenObject* inOwner)
{
	owner = inOwner;
}

void Collider::SetPosition(sf::Vector2f vector)
{
	position.x = vector.x + owner->size.x / 2;
	position.y = vector.y + owner->size.y / 2;
}

ZenObject* Collider::GetOwner()
{
	return owner;
}

Vector2* Collider::GetPosition()
{
	return &position;
}

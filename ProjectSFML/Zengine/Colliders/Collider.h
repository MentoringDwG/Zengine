#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include "../Structs/Vector2.h"
#include "../ZenObject/ZenObject.h"
#include "CollisionEventBinder.h"

class Collider
{
public:
	enum ColliderTags
	{
		DEFAULT = 0,
		CHARACTER = 1,
		ENEMY = 2,
		GROUND = 3,
		COIN = 4,
	};

	Collider(ColliderTags tag);

	ZenObject* GetOwner();
	void SetOwner(ZenObject* inOwner);
	void SetPosition(sf::Vector2f vector);
	Vector2* GetPosition();
	ColliderTags tag;

	CollisionEventBinder OnCollisionStart;
	CollisionEventBinder OnCollisionEnd;

private:
	Vector2* position;
	ZenObject* owner;
};

#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include "../Structs/Vector2.h"
#include "../ZenObject/ZenObject.h"
#include "CollisionEventBinder.h"

class Collider
{
public:
	enum class ColliderTags
	{
		DEFAULT = 0,
		CHARACTER = 1,
		ENEMY = 2,
		GROUND = 3,
		COIN = 4,
		Max,
	};

	Collider(ColliderTags tag, Vector2* size);

	ZenObject* GetOwner();
	void SetOwner(ZenObject* inOwner);
	void SetPosition(sf::Vector2f vector);
	Vector2* GetPosition();
	ColliderTags tag;
	Vector2* size;

	CollisionEventBinder OnCollisionStart;
	CollisionEventBinder OnCollisionEnd;

private:
	Vector2* position;
	ZenObject* owner;
};

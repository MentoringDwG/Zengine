// Copyright Z.Z. Zengine (c)

#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include "../Structs/Vector2.h"
#include "CollisionEventBinder.h"

class ZenObject;

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
		CASTLE = 5,
		CONFINER = 6,
		MAP_LOADER = 7,
		Max,
	};

	Collider(ColliderTags tag, Vector2 size);
	~Collider();

	ZenObject* GetOwner();
	void SetOwner(ZenObject* inOwner);
	void SetPosition(sf::Vector2f vector);
	Vector2* GetPosition();

	ColliderTags tag;
	Vector2 size = Vector2(0, 0);
	CollisionEventBinder OnCollisionStart;
	CollisionEventBinder OnCollisionEnd;

private:
	Vector2 position = Vector2(0, 0);
	ZenObject* owner = nullptr;
};

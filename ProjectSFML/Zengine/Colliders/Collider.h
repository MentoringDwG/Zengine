#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include "../Structs/Vector2.h"
#include "../ZenObject/ZenObject.h"

class Collider
{
public:
	Collider()
	{
		owner = new ZenObject();
		position = new Vector2(0, 0);
	}

	ZenObject* GetOwner();
	void SetOwner(ZenObject* inOwner);
	void SetPosition(sf::Vector2f vector);
	Vector2* GetPosition();

	std::function<void(Collider*)> OnCollisionStart;
	std::function<void(Collider*)> OnCollisionEnd;

private:
	Vector2* position;
	ZenObject* owner;
};

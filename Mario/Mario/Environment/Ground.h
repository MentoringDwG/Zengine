#pragma once

#include <Zengine/ZenObject/ZenObject.h>

class Ground
{
public:
	Ground(string pathToGroundTxt)
	{
		SetBoxColliders(pathToGroundTxt);
	}

	~Ground();

	void SetBoxColliders(string pathToGroundTxt);

private:
	void HandleCollisionStart(class Collider* other);
	sf::Vector2f position;
	std::vector<class BoxCollider2D*> boxColliders;
	std::vector<ZenObject*> zenObjects;
	int listenerIndex = 0;
};


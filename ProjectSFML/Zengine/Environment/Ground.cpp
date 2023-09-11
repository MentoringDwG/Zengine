#include "Ground.h"
#include <fstream>
#include "../Colliders/BoxCollider2D.h"
#include "../Colliders/Collider.h"
#include "../Physics2D/ZenPhysics2D.h"

void Ground::SetBoxColliders(string pathToGroundTxt)
{
	ifstream file;
	file.open(pathToGroundTxt);

	string numberOfCollidersFile;
	file >> numberOfCollidersFile;

	int numberOfColliders = std::stoi(numberOfCollidersFile);

	string id, positionX, positionY, sizeX, sizeY;
	for (int i = 0; i < numberOfColliders; i++)
	{
		file >> id;
		file >> positionX;
		file >> positionY;
		file >> sizeX;
		file >> sizeY;

		zenObjects.push_back(new ZenObject(std::stoi(id), "Ground", sf::Vector2f(std::stoi(sizeX), std::stoi(sizeY))));

		boxColliders.push_back(new BoxCollider2D(Vector2(std::stoi(positionX), std::stoi(positionY)), Vector2(std::stoi(sizeX), std::stoi(sizeY)), zenObjects[i], Collider::ColliderTags::GROUND));
	}

	file.close();

	for (int i = 0; i < numberOfColliders; i++)
	{
		boxColliders[i]->OnCollisionStart.AddListener(&Ground::HandleCollisionStart, this);
		ZenPhysics2D::Get()->RegisterCollider(boxColliders[i]);
	}
}

Ground::~Ground()
{
	boxColliders.clear();
	zenObjects.clear();
}

void Ground::HandleCollisionStart(Collider* other)
{

}
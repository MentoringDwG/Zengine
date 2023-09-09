#include "Ground.h"
#include <fstream>

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

		boxColliders.push_back(new BoxCollider2D(new Vector2(std::stoi(positionX), std::stoi(positionY)), new Vector2(std::stoi(sizeX), std::stoi(sizeY)), zenObjects[i], Collider::ColliderTags::GROUND));
	}

	file.close();

	for (int i = 0; i < numberOfColliders; i++)
	{
		boxColliders[i]->OnCollisionStart.AddListener(&Ground::HandleCollisionStart, this);
		ZenPhysics2D::Get()->RegisterCollider(boxColliders[i]);
	}
}

void Ground::HandleCollisionStart(Collider* other)
{

}
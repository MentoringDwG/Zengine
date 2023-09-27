#include "Ground.h"
#include <fstream>
#include "Zengine/Colliders/BoxCollider2D.h"
#include "Zengine/Colliders/Collider.h"
#include "Zengine/Physics2D/ZenPhysics2D.h"

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

		zenObjects.push_back(new ZenObject(std::stoi(id), "Ground", sf::Vector2f((float)(std::stoi(sizeX)), (float)(std::stoi(sizeY)))));

		boxColliders.push_back(new BoxCollider2D(Vector2((float)(std::stoi(positionX)), (float)(std::stoi(positionY))), Vector2((float)(std::stoi(sizeX)), (float)(std::stoi(sizeY))), zenObjects[i], Collider::ColliderTags::GROUND));
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
	for (int i = 0; i < boxColliders.size(); i++)
	{
		ZenPhysics2D::Get()->UnregisterCollider(boxColliders[i]);
	}

	boxColliders.clear();
	zenObjects.clear();
}

void Ground::HandleCollisionStart(Collider* other)
{

}
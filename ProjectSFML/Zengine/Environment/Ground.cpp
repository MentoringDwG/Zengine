#include "Ground.h"
#include <fstream>

#pragma optimize("", off)
void Ground::SetBoxColliders(string pathToGroundTxt)
{
	ifstream file;
	file.open(pathToGroundTxt);
	//string path, name;
	string numberOfColliders;
	file >> numberOfColliders;

	string id, positionX, positionY, sizeX, sizeY;
	for (int i = 0; i < std::stoi(numberOfColliders); i++)
	{
		file >> id >> positionX >> positionY >> sizeX >> sizeY;

		zenObjects.push_back(new ZenObject(std::stoi(id), "Ground", sf::Vector2f(std::stoi(sizeX), std::stoi(sizeY))));

		boxColliders.push_back(new BoxCollider2D(new Vector2(std::stoi(positionX), std::stoi(positionY)), new Vector2(std::stoi(sizeX), std::stoi(sizeY)), zenObjects[i], Collider::GROUND));
	}

	file.close();

	for (int i = 0; i < std::stoi(numberOfColliders); i++)
	{
		boxColliders[i]->OnCollisionStart.AddListener(&Ground::HandleCollisionStart, this);
		ZenPhysics2D::Get()->RegisterCollider(boxColliders[i]);
	}
}
#pragma optimize("", on)
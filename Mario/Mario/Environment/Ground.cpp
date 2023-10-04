#include "Ground.h"
#include <fstream>
#include <Zengine/Colliders/BoxCollider2D.h>
#include <Zengine/Colliders/Collider.h>
#include <Zengine/Physics2D/ZenPhysics2D.h>

void Ground::SetBoxColliders(nlohmann::json groundData)
{
	for (size_t i = 0; i < groundData.size(); i++)
	{
		nlohmann::json ground = groundData.at(i);

		zenObjects.push_back(new ZenObject(ground["id"], "Ground", sf::Vector2f((float)ground["width"]*TILE_SCALE, (float)ground["height"] * TILE_SCALE)));

		boxColliders.push_back(new BoxCollider2D(Vector2((float)ground["x"] * TILE_SCALE, (float)ground["y"] * TILE_SCALE), Vector2((float)ground["width"] * TILE_SCALE, (float)ground["height"] * TILE_SCALE), zenObjects[i], Collider::ColliderTags::GROUND));
	}

	for (int i = 0; i < boxColliders.size(); i++)
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

int Ground::CollidersVectorSize()
{
	return (int)boxColliders.size();
}
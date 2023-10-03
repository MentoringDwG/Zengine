#include "MapLoader.h"
#include <Zengine/Colliders/BoxCollider2D.h>
#include <Zengine/Physics2D/ZenPhysics2D.h>
#include <Zengine/StateMachine/StateMachine.h>
#include <Zengine/World/World.h>

MapLoader::MapLoader(int id, std::string name, Vector2 size, Vector2 position): ZenObject(id, name, sf::Vector2f(size.x, size.y))
{
	this->position = sf::Vector2f(position.x, position.y);

	boxCollider = new BoxCollider2D(position, size, this, Collider::ColliderTags::MAP_LOADER);
	boxCollider->OnCollisionStart.AddListener(&MapLoader::HandleCollisionStart, this);
	boxCollider->OnCollisionEnd.AddListener(&MapLoader::HandleCollisionEnd, this);
	ZenPhysics2D::Get()->RegisterCollider(boxCollider);
}

MapLoader::~MapLoader()
{
	if (boxCollider == nullptr) return;

	ZenPhysics2D::Get()->UnregisterCollider(boxCollider);
	boxCollider->OnCollisionStart.RemoveAllListeners();
	boxCollider->OnCollisionStart.RemoveAllListeners();
	delete boxCollider;
}

void MapLoader::SetMapToLoad(std::string textureFilePath, std::string mapJsonPath, class World* owner)
{
	this->textureFilePath = textureFilePath;
	this->mapJsonPath = mapJsonPath;
	this->owner = owner;
}

void MapLoader::HandleCollisionStart(Collider* other)
{
	if (other->GetOwner()->name == MARIO && !isCollisionWithMario)
	{
		isCollisionWithMario = true;

		owner->LoadMap(textureFilePath, mapJsonPath);
		ZenPhysics2D::Get()->UnregisterCollider(boxCollider);
	}
}

void MapLoader::HandleCollisionEnd(Collider* other)
{
	if (other->GetOwner()->name == MARIO)
	{
		isCollisionWithMario = false;
	}
}


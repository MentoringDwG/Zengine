#include "MapLoader.h"
#include <Zengine/Colliders/BoxCollider2D.h>
#include <Zengine/Physics2D/ZenPhysics2D.h>
#include <Zengine/StateMachine/StateMachine.h>
#include <Zengine/World/World.h>

#include "Level.h"
#include "../Character/Character.h"

const static std::string CASTLE = "castle";
const static std::string TUBE = "tube";
const static std::string MARIO = "Mario";

MapLoader::MapLoader(int id, std::string name, Vector2 size, Vector2 position, std::string tag, Character* playerCharacter): ZenObject(id, name, sf::Vector2f(size.x, size.y))
{
	this->position = sf::Vector2f(position.x, position.y);
	this->tag = tag;
	this->playerCharacter = playerCharacter;

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

void MapLoader::SetMapToLoad(std::string textureFilePath, std::string mapJsonPath, Level* owner, int playerPositionId)
{
	this->textureFilePath = textureFilePath;
	this->mapJsonPath = mapJsonPath;
	this->owner = owner;
	this->playerPositionId = playerPositionId;
}

void MapLoader::HandleCollisionStart(Collider* other)
{
	if (other->GetOwner()->name == MARIO && !isCollisionWithMario)
	{
		if (tag == CASTLE)
		{
			isCollisionWithMario = true;
			owner->canCheckKays = true;
			owner->LoadMap(textureFilePath, mapJsonPath, playerPositionId);
		}

		//TO DO wyliczenie punktu kolizji

		if (tag == TUBE && playerCharacter->GetInputHandler()->movingStates==CharacterInputHandler::MovingStates::movingDown)
		{
			isCollisionWithMario = true;
			owner->canCheckKays = false;
			owner->LoadMap(textureFilePath, mapJsonPath, playerPositionId);
		}
	}
}

void MapLoader::HandleCollisionEnd(Collider* other)
{
	if (other->GetOwner()->name == MARIO)
	{
		isCollisionWithMario = false;
	}
}


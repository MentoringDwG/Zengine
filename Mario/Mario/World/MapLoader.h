#pragma once

#include <Zengine/Structs/Vector2.h>
#include <Zengine/ZenObject/ZenObject.h>

class MapLoader : public ZenObject
{
public:
	MapLoader(int id, std::string name, Vector2 size, Vector2 position, std::string tag, class Character* playerCharacter);
	~MapLoader();
	void SetMapToLoad(std::string textureFilePath, std::string mapJsonPath, class World* owner, int playerPositionId);
private:
	void HandleCollisionStart(class Collider* other);
	void HandleCollisionEnd(Collider* other);

	std::string tag = "";
	std::string textureFilePath = "";
	std::string mapJsonPath = "";
	int playerPositionId = 0;
	class World* owner = nullptr;
	class BoxCollider2D* boxCollider = nullptr;
	class Character* playerCharacter = nullptr;
	bool isCollisionWithMario = false;

	const std::string MARIO = "Mario";
};


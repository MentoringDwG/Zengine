#pragma once

#include <Zengine/Structs/Vector2.h>
#include <Zengine/ZenObject/ZenObject.h>

class MapLoader : public ZenObject
{
public:
	MapLoader(int id, std::string name, Vector2 size, Vector2 position);
	~MapLoader();
	void SetMapToLoad(std::string textureFilePath, std::string mapJsonPath, class World* owner);
private:
	void HandleCollisionStart(class Collider* other);
	void HandleCollisionEnd(Collider* other);

	std::string textureFilePath = "";
	std::string mapJsonPath = "";
	class World* owner = nullptr;
	class BoxCollider2D* boxCollider = nullptr;
	bool isCollisionWithMario = false;

	const std::string MARIO = "Mario";
};


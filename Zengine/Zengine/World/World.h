// Copyright Z.Z. Zengine (c)

#pragma once

#include "../InputModule/CharacterInputHandler.h"
#include "../Renderer/Renderer.h"

class World
{
public:
	virtual void Initialize(class AudioSystem* audioSystem) = 0;
	virtual void MapInitialize() = 0;
	virtual void EnvironmentClear() = 0;
	virtual void EnvironmentInitialize() = 0;
	virtual void ApplyForceToPhysicsObject() = 0;
	virtual void UpdateObjects() = 0;
	virtual void SetCamera(sf::View* mainCamera, struct Vector2 windowSize) = 0;
	virtual CharacterInputHandler* GetCharacterInputHandler() = 0;
	virtual void Draw(RenderingStack* renderStack) = 0;
	virtual void SetRendering(RenderingStack* renderStack, Renderer* renderModule) = 0;
	virtual void LoadMap(std::string textureFilePath, std::string levelJsonPath, int playerPositionId) = 0;
	virtual bool IsWorldLoaded() = 0;
};

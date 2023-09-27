#pragma once

#include <vector>
#include <Zengine/World/World.h>
#include <Zengine/Renderer/Renderer.h>

class Level1: public World
{
public:
	Level1() {};
	~Level1();

	virtual void Initialize(StateMachine* stateMachine) override;
	virtual void MapInitialize() override;
	virtual void PhysicalZenObject2DInitialize() override;
	virtual void EnvironmentInitialize() override;
	virtual void ApplyForceToPhysicsObject() override;
	virtual void UpdateObjects() override;
	virtual class CharacterInputHandler* GetCharacterInputHandler() override;

	void Draw(RenderingStack* renderStack);
	class CoinCounter* coinCounter = nullptr;

private:
	class StateMachine* stateMachine = nullptr;
	class Map* map = nullptr;
	class Character* playerCharacter = nullptr;
	class Enemy* enemy = nullptr;
	class Ground* ground = nullptr;
	std::vector<class Coin*> coins;
	class HeartsPanel* heartPanel = nullptr;
	class Castle* castle = nullptr;
};


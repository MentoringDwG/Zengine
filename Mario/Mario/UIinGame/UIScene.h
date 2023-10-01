#pragma once

#include <Zengine/Renderer/Renderer.h>

class UIScene
{
public:
	UIScene(class StateMachine* stateMachine);
	~UIScene();
	void Draw(RenderingStack* renderStack);
	class CoinCounter* GetCoinCounter();
	class HeartsPanel* GetHeartPanel();
private:
	class CoinCounter* coinCounter = nullptr;
	class HeartsPanel* heartPanel = nullptr;
};


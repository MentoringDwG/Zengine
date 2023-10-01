#include "UIScene.h"
#include <Zengine/StateMachine/StateMachine.h>
#include "HeartsPanel.h"
#include "../Environment/CoinCounter.h"

UIScene::UIScene(StateMachine* stateMachine)
{
	coinCounter = new CoinCounter(1, "coinCounter", sf::Vector2f(0, 0));
	heartPanel = new HeartsPanel(stateMachine);
}

UIScene::~UIScene()
{
	delete heartPanel;
	delete coinCounter;
}

void UIScene::Draw(RenderingStack* renderStack)
{
	heartPanel->Draw(renderStack);
	coinCounter->Draw(renderStack);
}

class CoinCounter* UIScene::GetCoinCounter()
{
	return coinCounter;
}

class HeartsPanel* UIScene::GetHeartPanel()
{
	return heartPanel;
}
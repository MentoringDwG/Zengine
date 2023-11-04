#include "UIScene.h"
#include <Zengine/StateMachine/StateMachine.h>
#include "HeartsPanel.h"
#include "KeyPanel.h"
#include "../Environment/CoinCounter.h"

UIScene::UIScene(StateMachine* stateMachine)
{
	coinCounter = new CoinCounter(1, "coinCounter", sf::Vector2f(0, 0));
	heartPanel = new HeartsPanel(stateMachine);
	keyPanel = new KeyPanel();
}

UIScene::~UIScene()
{
	delete heartPanel;
	delete coinCounter;
	delete keyPanel;
}

void UIScene::Draw(RenderingStack* renderStack)
{
	heartPanel->Draw(renderStack);
	coinCounter->Draw(renderStack);
	keyPanel->Draw(renderStack);
}

CoinCounter* UIScene::GetCoinCounter()
{
	return coinCounter;
}

HeartsPanel* UIScene::GetHeartPanel()
{
	return heartPanel;
}

KeyPanel* UIScene::GetKeyPanel()
{
	return keyPanel;
}
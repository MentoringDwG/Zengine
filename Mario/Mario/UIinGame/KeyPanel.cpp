#include "KeyPanel.h"

KeyPanel::KeyPanel()
{
	keys.push_back(make_shared<UIButton>(Vector2(128, 0), Vector2(32, 32)));
	keys.push_back(make_shared<UIButton>(Vector2(160, 0), Vector2(32, 32)));
	keys.push_back(make_shared<UIButton>(Vector2(192, 0), Vector2(32, 32)));
}

KeyPanel::~KeyPanel()
{
	keys.clear();
}

void KeyPanel::Draw(RenderingStack* renderStack)
{
	keys[0]->Draw(renderStack, "Graphics/Key/keys.png", sf::IntRect(0, 0, 32, 32), 23, "KeyLeft");
	keys[1]->Draw(renderStack, "Graphics/Key/keys.png", sf::IntRect(0, 0, 32, 32), 24, "KeyMiddle");
	keys[2]->Draw(renderStack, "Graphics/Key/keys.png", sf::IntRect(0, 0, 32, 32), 25, "KeyRight");
}

void KeyPanel::UpdateKeysState()
{
	for (int i = 0; i<=(int)keys.size(); i++)
	{
		if (keys[i]->GetIntRect().left == 0)
		{
			keys[i]->SetIntRect(sf::IntRect(32, 0, 32, 32));

			return;
		}
	}
}
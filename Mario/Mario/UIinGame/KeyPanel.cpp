#include "KeyPanel.h"

KeyPanel::KeyPanel()
{
	keys.push_back(make_shared<UIButton>(Vector2(128, 0), Vector2(32, 32)));
	keys.push_back(make_shared<UIButton>(Vector2(160, 0), Vector2(32, 32)));
	keys.push_back(make_shared<UIButton>(Vector2(192, 0), Vector2(32, 32)));

	intRects.push_back(new sf::IntRect(0, 0, 32, 32));
	intRects.push_back(new sf::IntRect(0, 0, 32, 32));
	intRects.push_back(new sf::IntRect(0, 0, 32, 32));
}

KeyPanel::~KeyPanel()
{
	keys.clear();
	intRects.clear();
}

void KeyPanel::Draw(RenderingStack* renderStack)
{
	keys[0]->Draw(renderStack, "Graphics/Key/keys.png", *intRects[0], 23, "KeyLeft");
	keys[1]->Draw(renderStack, "Graphics/Key/keys.png", *intRects[1], 24, "KeyMiddle");
	keys[2]->Draw(renderStack, "Graphics/Key/keys.png", *intRects[2], 25, "KeyRight");
}

void KeyPanel::UpdateKeysState()
{
	for (int i = 0; i<(int)keys.size(); i++)
	{
		if (keys[i]->GetIntRect().left == 0)
		{
			keys[i]->SetIntRect(sf::IntRect(32, 0, 32, 32));
			*intRects[i] = sf::IntRect(32, 0, 32, 32);

			if (i == 2)
				allKeyCollected = true;

			return;
		}
	}
}

void KeyPanel::Clear()
{
	for (int i = 0; i < (int)keys.size(); i++)
	{
		keys[i]->SetIntRect(sf::IntRect(0, 0, 32, 32));
		*intRects[i] = sf::IntRect(0, 0, 32, 32);
	}

	allKeyCollected = false;
}
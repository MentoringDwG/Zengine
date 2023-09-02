#include "HeartsPanel.h"

HeartsPanel::HeartsPanel()
{
	hearts.push_back(make_shared<UIButton>(Vector2(0, 0), Vector2(32, 32)));
	hearts.push_back(make_shared<UIButton>(Vector2(32, 0), Vector2(32, 32)));
	hearts.push_back(make_shared<UIButton>(Vector2(64, 0), Vector2(32, 32)));
}

void HeartsPanel::Draw(RenderingStack* renderStack)
{
	hearts[0]->Draw(renderStack, "Graphics/Heart.png", sf::IntRect(0, 0, 32, 32), 20, "HeartLeft");
	hearts[1]->Draw(renderStack, "Graphics/Heart.png", sf::IntRect(0, 0, 32, 32), 21, "HeartMiddle");
	hearts[2]->Draw(renderStack, "Graphics/Heart.png", sf::IntRect(0, 0, 32, 32), 22, "HeartRight");
}

void HeartsPanel::UpdateHeartsState()
{
	for (int i = hearts.size() - 1; i >= 0; i--)
	{
		if (hearts[i]->GetIntRect().left == 0)
		{
			hearts[i]->SetIntRect(sf::IntRect(32, 0, 32, 32));

			if (i == 0)
			{
				exit(0);
			}

			return;
		}
	}
}
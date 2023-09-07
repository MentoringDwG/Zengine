#pragma once

#include "../UI/UIButton.h"
#include <memory>
#include <vector>

class HeartsPanel
{
	std::vector<shared_ptr<UIButton>> hearts;

public:
	HeartsPanel();
	void Draw(class RenderingStack* renderStack);
	void UpdateHeartsState();
};

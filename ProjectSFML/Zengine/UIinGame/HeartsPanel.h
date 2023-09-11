#pragma once

#include "../UI/UIButton.h"
#include <memory>
#include <vector>

class HeartsPanel
{
	std::vector<shared_ptr<UIButton>> hearts;

public:
	HeartsPanel();
	~HeartsPanel();

	void Draw(struct RenderingStack* renderStack);
	void UpdateHeartsState();
};

#pragma once

#include "../UI/CompoundWidget.h"
#include "../UI/UIButton.h"
#include "../Renderer/Renderer.h"
#include <memory>
#include <vector>

class HeartsPanel
{
	std::vector< shared_ptr<UIButton>> hearts;

public:
	HeartsPanel();
	void Draw(RenderingStack* renderStack);
	void UpdateHeartsState();
};


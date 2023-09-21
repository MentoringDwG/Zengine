#pragma once

#include "../../../Zengine/Zengine/UI/UIButton.h"
#include <memory>
#include <vector>

class HeartsPanel
{
private:
	std::vector<shared_ptr<UIButton>> hearts;
	class StateMachine* stateMachine = nullptr;

public:
	HeartsPanel(class StateMachine* stateMachineIn);
	~HeartsPanel();

	void Draw(struct RenderingStack* renderStack);
	void UpdateHeartsState();
};

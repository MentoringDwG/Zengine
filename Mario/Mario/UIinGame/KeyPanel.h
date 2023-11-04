#pragma once

#include <Zengine/UI/UIButton.h>
#include <memory>
#include <vector>

class KeyPanel
{
private:
	std::vector<shared_ptr<UIButton>> keys;
	class StateMachine* stateMachine = nullptr;

public:
	KeyPanel();
	~KeyPanel();

	void Draw(struct RenderingStack* renderStack);
	void UpdateKeysState();
};


#pragma once

#include "InputHandler.h"
#include <vector>
#include "../UI/Widget.h"

class UIInputHandler : public InputHandler
{
public:
	static UIInputHandler* Get() { return &instance; }

	virtual bool ProcessInput(sf::Event& event, sf::RenderWindow* inWindow) override;
	virtual bool CanConsumeInput() override;

	void AddWidget(Widget* widget);
	void Clear();

private:
	UIInputHandler() {}

	static UIInputHandler instance;

	std::vector<Widget*> widgets;

};


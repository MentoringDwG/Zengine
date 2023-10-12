// Copyright Z.Z. Zengine (c)

#pragma once

#include "InputHandler.h"
#include <vector>

class UIInputHandler : public InputHandler
{
public:
	static UIInputHandler* Get() { return &instance; }

	virtual bool ProcessInput(sf::Event& event, sf::RenderWindow* inWindow) override;
	virtual bool CanConsumeInput() override;

	void AddWidget(class Widget* widget);
	void DeleteWidget(class Widget* widget);
	void Clear();

private:
	UIInputHandler() {}

	static UIInputHandler instance;
	std::vector<class Widget*> widgets;
};


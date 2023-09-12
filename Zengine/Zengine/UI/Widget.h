#pragma once

#include "../Structs/Vector2.h"
#include <SFML/Graphics.hpp>
#include "WidgetEventHandler.h"

class Widget
{
public:
	virtual void OnMouseHover() = 0;
	virtual void OnMouseUnHover() = 0;
	virtual void OnMousePressed() = 0;
	virtual void OnMouseUnPressed() = 0;

	enum class State
	{
		MouseHover = 0,
		UnHover = 1,
		Pressed = 2,
		UnPressed = 3
	};

	Widget(Vector2 positionIn, Vector2 sizeIn);
	~Widget();

	void SetParent(Widget* parent);
	sf::FloatRect GetWidgetRect();
	void SetPosition(Vector2 positionIn);
	void SetSize(Vector2 sizeIn);
	Vector2 GetSize();
	Vector2 GetPosition();
	bool IsMouseOver(sf::Vector2f* InMousePos);

	WidgetEventHandler OnMouseDownEvent;
	WidgetEventHandler OnMouseUpEvent;
	WidgetEventHandler OnMouseHoverEvent;
	WidgetEventHandler OnMouseUnHoverEvent;
	State state = State::UnHover;

private:
	Vector2 position;
	Vector2 size;
	sf::FloatRect widgetRect;
	Widget* parent = nullptr;
};


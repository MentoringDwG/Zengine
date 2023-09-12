#include "Widget.h"

Widget::Widget(Vector2 positionIn, Vector2 sizeIn): position(positionIn), size(sizeIn)
{
	widgetRect.left = positionIn.x;
	widgetRect.top = positionIn.y;
	widgetRect.width = sizeIn.x;
	widgetRect.height = sizeIn.y;
}

Widget::~Widget()
{
	delete parent;
}

bool Widget::IsMouseOver(sf::Vector2f* InMousePos)
{
	return widgetRect.contains(*InMousePos);
}

void Widget::SetParent(Widget* parent)
{
	this->parent = parent;
}

sf::FloatRect Widget::GetWidgetRect()
{
	return widgetRect;
}

void Widget::SetPosition(Vector2 positionIn)
{
	position = positionIn;
}

void Widget::SetSize(Vector2 sizeIn)
{
	size = sizeIn;
}

Vector2 Widget::GetSize()
{
	return size;
}

Vector2 Widget::GetPosition()
{
	return position;
}

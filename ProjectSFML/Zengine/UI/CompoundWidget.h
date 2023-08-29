#pragma once

#include <map>
#include "Widget.h"

class CompoundWidget: public Widget
{
private:
	std::map<int, Widget*> children;

public:
	CompoundWidget(Vector2 positionIn, Vector2 sizeIn): Widget(positionIn, sizeIn)
	{

	}

	void AddWidget(int id, Widget* widget);
	Widget* GetChild(int childId);
};


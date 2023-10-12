// Copyright Z.Z. Zengine (c)

#pragma once

#include <map>
#include "Widget.h"

class CompoundWidget: public Widget
{
private:
	std::map<int, Widget*> children;

public:
	CompoundWidget(Vector2 positionIn, Vector2 sizeIn);

	virtual void OnMouseHover() override;
	virtual void OnMouseUnHover() override;
	virtual void OnMousePressed() override;
	virtual void OnMouseUnPressed() override;

	void AddChild(int id, Widget* widget);
	void DeleteChild(int id);
	Widget* GetChild(int childId);
};


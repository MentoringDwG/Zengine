#include "CompoundWidget.h"

void CompoundWidget::AddWidget(int id, Widget* widget)
{
	children[id] = widget;
}

Widget* CompoundWidget::GetChild(int childId)
{
	return children[childId];
}
#include "CompoundWidget.h"

CompoundWidget::CompoundWidget(Vector2 positionIn, Vector2 sizeIn) : Widget(positionIn, sizeIn)
{

}

void CompoundWidget::AddChild(int id, Widget* widget)
{
	children[id] = widget;
}

Widget* CompoundWidget::GetChild(int childId)
{
	return children[childId];
}

void CompoundWidget::OnMouseHover()
{
	OnMouseHoverEvent.Invoke();
}

void CompoundWidget::OnMouseUnHover()
{
	OnMouseUnHoverEvent.Invoke();
}

void CompoundWidget::OnMousePressed()
{
	OnMouseDownEvent.Invoke();
}

void CompoundWidget::OnMouseUnPressed()
{
	OnMouseUpEvent.Invoke();
}
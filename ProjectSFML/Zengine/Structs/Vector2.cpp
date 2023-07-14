#include "Vector2.h"

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

bool Vector2::IsThisVector2EqualToOtherVector2(Vector2* otherVector2)
{
	return (x == otherVector2->x && y == otherVector2->y) ? true : false;
}

void Vector2::SetVector2(float x, float y)
{
	this->x = x;
	this->y = y;
}
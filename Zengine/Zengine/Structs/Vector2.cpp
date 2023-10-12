// Copyright Z.Z. Zengine (c)

#include "Vector2.h"
#include<cmath>

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

float Vector2::GetDistance(const Vector2* other)
{
	return (float)sqrt(pow(x - other->x, 2) + pow(y - other->y, 2));
}
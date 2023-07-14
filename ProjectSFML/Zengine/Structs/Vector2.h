#pragma once

struct Vector2
{
public:
	Vector2(float x, float y);
	bool IsThisVector2EqualToOtherVector2(Vector2* otherVector2);
	void SetVector2(float x, float y);

	float x;
	float y;
}; 



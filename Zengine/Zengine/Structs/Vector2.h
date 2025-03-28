// Copyright Z.Z. Zengine (c)

#pragma once

struct Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	bool IsThisVector2EqualToOtherVector2(Vector2* otherVector2);
	void SetVector2(float x, float y);
	float GetDistance(const Vector2* other);

	float x;
	float y;
}; 

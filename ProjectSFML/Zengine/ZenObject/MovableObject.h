#pragma once

class MovableObject
{
public:
	virtual void MoveLeft()=0;
	virtual void MoveRight()=0;
	virtual void MoveUp() = 0;
	virtual void MoveDown() = 0;
};


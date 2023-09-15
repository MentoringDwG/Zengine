#pragma once

#include "../Structs/Vector2.h"

struct KeyFrame
{
public:
	KeyFrame(int keyFrameIdIn, int spriteSheetIdIn, Vector2 startPointInSpriteSheetIn, Vector2 spriteSizeIn, int TimeStampIn) : 
		keyFrameId(keyFrameIdIn),
		spriteSheetId(spriteSheetIdIn),
		startPointInSpriteSheet(startPointInSpriteSheetIn),
		spriteSize (spriteSizeIn),
		timeStamp(TimeStampIn) {}

	int keyFrameId = 0;
	int spriteSheetId = 0;
	Vector2 startPointInSpriteSheet = Vector2(0, 0);
	Vector2 spriteSize = Vector2(0, 0);
	int timeStamp = 0;
};

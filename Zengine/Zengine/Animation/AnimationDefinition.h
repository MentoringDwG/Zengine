#pragma once

#include <iostream>

class Animation;

struct AnimationDefinition
{
	AnimationDefinition(std::string animationDefimitionJsonPathIn, Animation* ownerIn);

	std::string animationDefimitionJsonPath = "";
	Animation* owner = nullptr;

	void AddKeyFrame(int keyFrameIdIn, int spriteSheetIdIn, struct Vector2 startPointInSpriteSheetIn, struct Vector2 spriteSizeIn, int TimeStampIn);
	void AddSpriteSheets(std::string spriteSheetPath);
};


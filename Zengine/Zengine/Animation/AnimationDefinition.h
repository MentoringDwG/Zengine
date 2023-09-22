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

	//json
	const std::string SPRITESHEETS = "SpriteSheets";
	const std::string PATH = "Path";
	const std::string KEYFRAMES = "KeyFrames";
	const std::string KEYFRAMEID = "KeyFrameId";
	const std::string SPRITESHEETID = "SpriteSheetId";
	const std::string STARTPOINTINSPRITESHEETX = "StartPointInSpriteSheetX";
	const std::string STARTPOINTINSPRITESHEETY = "StartPointInSpriteSheetY";
	const std::string SPRITESIZEX = "SpriteSizeX";
	const std::string SPRITESIZEY = "SpriteSizeY";
	const std::string TIMESTAMP = "TimeStamp";
};


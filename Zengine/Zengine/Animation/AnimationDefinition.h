#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

struct AnimationDefinition
{
	AnimationDefinition(std::string animationDefimitionJsonPathIn, std::string nameIn);

	void AddKeyFrame(int keyFrameIdIn, int spriteSheetIdIn, struct Vector2 startPointInSpriteSheetIn, struct Vector2 spriteSizeIn, int TimeStampIn);
	void AddSpriteSheets(std::string spriteSheetPath);

	std::string animationDefimitionJsonPath = "";
	std::string name = "";

	//json
	const std::string SPRITE_SHEETS = "SpriteSheets";
	const std::string PATH = "Path";
	const std::string KEY_FRAMES = "KeyFrames";
	const std::string KEY_FRAME_ID = "KeyFrameId";
	const std::string SPRITE_SHEET_ID = "SpriteSheetId";
	const std::string START_POINT_IN_SPRITE_SHEET_X = "StartPointInSpriteSheetX";
	const std::string START_POINT_IN_SPRITE_SHEET_Y = "StartPointInSpriteSheetY";
	const std::string SPRITE_SIZE_X = "SpriteSizeX";
	const std::string SPRITE_SIZE_Y = "SpriteSizeY";
	const std::string TIME_STAMP = "TimeStamp";

	std::vector<struct KeyFrame*> keyFrames;
	std::vector<sf::Texture*> spriteSheets;
};


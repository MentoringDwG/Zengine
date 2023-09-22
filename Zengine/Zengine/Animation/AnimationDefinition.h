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

	std::vector<struct KeyFrame*> keyFrames;
	std::vector<sf::Texture*> spriteSheets;
};


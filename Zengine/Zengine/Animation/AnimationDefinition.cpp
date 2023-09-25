#include "AnimationDefinition.h"
#include "../Structs/Vector2.h"
#include "../../../nlohmann/json.hpp"
#include "KeyFrame.h"
#include <fstream>

AnimationDefinition::AnimationDefinition(std::string animationDefimitionJsonPathIn, std::string nameIn) : animationDefimitionJsonPath(animationDefimitionJsonPath), name(nameIn)
{
	std::ifstream jsonFileStream(animationDefimitionJsonPathIn);
	nlohmann::json jsonData = nlohmann::json::parse(jsonFileStream);

	if (jsonData.contains(SPRITE_SHEETS))
	{
		nlohmann::json spriteSheets = jsonData[SPRITE_SHEETS];

		for (size_t idx = 0; idx < spriteSheets.size(); idx++)
		{
			nlohmann::json pathObj = spriteSheets.at(idx);

			AddSpriteSheets(pathObj[PATH]);
		}
	}

	if (jsonData.contains(KEY_FRAMES))
	{
		nlohmann::json keyFrames = jsonData[KEY_FRAMES];

		for (size_t idx = 0; idx < keyFrames.size(); idx++)
		{
			nlohmann::json keyFrame = keyFrames.at(idx);

			AddKeyFrame(keyFrame[KEY_FRAME_ID], keyFrame[SPRITE_SHEET_ID], Vector2(keyFrame[START_POINT_IN_SPRITE_SHEET_X], keyFrame[START_POINT_IN_SPRITE_SHEET_Y]), Vector2(keyFrame[SPRITE_SIZE_X], keyFrame[SPRITE_SIZE_Y]), keyFrame[TIME_STAMP]);
		}
	}
}

void AnimationDefinition::AddKeyFrame(int keyFrameIdIn, int spriteSheetIdIn, Vector2 startPointInSpriteSheetIn, Vector2 spriteSizeIn, int TimeStampIn)
{
	KeyFrame* keyFrame = new KeyFrame(keyFrameIdIn, spriteSheetIdIn, startPointInSpriteSheetIn, spriteSizeIn, TimeStampIn);
	keyFrames.push_back(keyFrame);
}

void AnimationDefinition::AddSpriteSheets(std::string spriteSheetPath)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(spriteSheetPath);

	spriteSheets.push_back(texture);
}

AnimationDefinition::~AnimationDefinition()
{
	for (int i = 0; i < keyFrames.size(); i++)
	{
		delete keyFrames[i];
	}
	keyFrames.clear();

	for (int i = 0; i < spriteSheets.size(); i++)
	{
		delete spriteSheets[i];
	}
	spriteSheets.clear();
}
#include "AnimationDefinition.h"
#include "../Structs/Vector2.h"
#include "../../../nlohmann/json.hpp"
#include "KeyFrame.h"
#include <fstream>

AnimationDefinition::AnimationDefinition(std::string animationDefimitionJsonPathIn, std::string nameIn) : animationDefimitionJsonPath(animationDefimitionJsonPath), name(nameIn)
{
	std::ifstream jsonFileStream(animationDefimitionJsonPathIn);
	nlohmann::json jsonData = nlohmann::json::parse(jsonFileStream);

	if (jsonData.contains(SPRITESHEETS))
	{
		nlohmann::json spriteSheets = jsonData[SPRITESHEETS];

		for (size_t idx = 0; idx < spriteSheets.size(); idx++)
		{
			nlohmann::json pathObj = spriteSheets.at(idx);

			AddSpriteSheets(pathObj[PATH]);
		}
	}

	if (jsonData.contains(KEYFRAMES))
	{
		nlohmann::json keyFrames = jsonData[KEYFRAMES];

		for (size_t idx = 0; idx < keyFrames.size(); idx++)
		{
			nlohmann::json keyFrame = keyFrames.at(idx);

			AddKeyFrame(keyFrame[KEYFRAMEID], keyFrame[SPRITESHEETID], Vector2(keyFrame[STARTPOINTINSPRITESHEETX], keyFrame[STARTPOINTINSPRITESHEETY]), Vector2(keyFrame[SPRITESIZEX], keyFrame[SPRITESIZEY]), keyFrame[TIMESTAMP]);
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
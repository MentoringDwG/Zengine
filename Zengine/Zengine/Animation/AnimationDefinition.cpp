#include "AnimationDefinition.h"
#include "Animation.h"
#include "../Structs/Vector2.h"
#include "../../../nlohmann/json.hpp"
#include <fstream>

AnimationDefinition::AnimationDefinition(std::string animationDefimitionJsonPathIn, Animation* ownerIn) : animationDefimitionJsonPath(animationDefimitionJsonPath), owner(ownerIn)
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
	owner->AddKeyFrame(keyFrameIdIn, spriteSheetIdIn, startPointInSpriteSheetIn, spriteSizeIn, TimeStampIn);
}

void AnimationDefinition::AddSpriteSheets(std::string spriteSheetPath)
{
	owner->AddSpriteSheets(spriteSheetPath);
}
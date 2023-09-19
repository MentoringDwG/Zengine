#include "AnimationDefinition.h"
#include "Animation.h"
#include "../Structs/Vector2.h"
#include "../../../nlohmann/json.hpp"
#include <fstream>

AnimationDefinition::AnimationDefinition(std::string animationDefimitionJsonPathIn, Animation* ownerIn) : animationDefimitionJsonPath(animationDefimitionJsonPath), owner(ownerIn)
{
	std::ifstream jsonFileStream(animationDefimitionJsonPathIn);
	nlohmann::json jsonData = nlohmann::json::parse(jsonFileStream);

	if (jsonData.contains("SpriteSheets"))
	{
		nlohmann::json spriteSheets = jsonData["SpriteSheets"];

		for (size_t idx = 0; idx < spriteSheets.size(); idx++)
		{
			nlohmann::json pathObj = spriteSheets.at(idx);

			AddSpriteSheets(pathObj["Path"]);
		}
	}

	if (jsonData.contains("KeyFrames"))
	{
		nlohmann::json keyFrames = jsonData["KeyFrames"];

		for (size_t idx = 0; idx < keyFrames.size(); idx++)
		{
			nlohmann::json keyFrame = keyFrames.at(idx);

			AddKeyFrame(keyFrame["KeyFrameId"], keyFrame["SpriteSheetId"], Vector2(keyFrame["StartPointInSpriteSheetX"], keyFrame["StartPointInSpriteSheetY"]), Vector2(keyFrame["SpriteSizeX"], keyFrame["SpriteSizeY"]), keyFrame["TimeStamp"]);
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
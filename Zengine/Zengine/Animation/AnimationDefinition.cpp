#include "AnimationDefinition.h"
#include "Animation.h"
#include "../Structs/Vector2.h"

AnimationDefinition::AnimationDefinition(std::string animationDefimitionJsonPathIn, Animation* ownerIn) : animationDefimitionJsonPath(animationDefimitionJsonPath), owner(ownerIn)
{

}

void AnimationDefinition::AddKeyFrame(int keyFrameIdIn, int spriteSheetIdIn, Vector2 startPointInSpriteSheetIn, Vector2 spriteSizeIn, int TimeStampIn)
{
	owner->AddKeyFrame(keyFrameIdIn, spriteSheetIdIn, startPointInSpriteSheetIn, spriteSizeIn, TimeStampIn);
}

void AnimationDefinition::AddSpriteSheets(std::string spriteSheetPath)
{
	owner->AddSpriteSheets(spriteSheetPath);
}
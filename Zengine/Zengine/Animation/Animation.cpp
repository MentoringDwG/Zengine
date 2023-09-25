#include "Animation.h"
#include "KeyFrame.h"
#include "../Structs/Vector2.h"
#include "AnimationDefinition.h"

Animation::Animation(std::shared_ptr<AnimationDefinition> animationDefinition)
{
	this->animationDefinition = animationDefinition;

	keyFrames = animationDefinition->keyFrames;
	spriteSheets = animationDefinition->spriteSheets;
}

Animation::~Animation()
{
	animationDefinition = nullptr;

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

std::vector<struct KeyFrame*> Animation::GetKeyFrames()
{
	return keyFrames;
}

sf::Texture* Animation::GetSpriteSheet(int spriteSheetId)
{
	return spriteSheets[spriteSheetId];
}
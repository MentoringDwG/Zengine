#include "Animation.h"
#include "KeyFrame.h"
#include "../Structs/Vector2.h"
#include "Animator.h"
#include "AnimationDefinition.h"

Animation::Animation(std::string animationDefinitionJsonPathIn)
{
	animationDefinition = new AnimationDefinition(animationDefinitionJsonPathIn, this);
}

Animation::~Animation()
{
	delete animationDefinition;

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

void Animation::AddKeyFrame(int keyFrameIdIn, int spriteSheetIdIn, Vector2 startPointInSpriteSheetIn, Vector2 spriteSizeIn, int TimeStampIn)
{
	KeyFrame* keyFrame = new KeyFrame(keyFrameIdIn, spriteSheetIdIn, startPointInSpriteSheetIn, spriteSizeIn, TimeStampIn);
	keyFrames.push_back(keyFrame);
}

std::vector<struct KeyFrame*> Animation::GetKeyFrames()
{
	return keyFrames;
}

void Animation::AddSpriteSheets(std::string spriteSheetPath)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(spriteSheetPath);

	spriteSheets.push_back(texture);
}

sf::Texture* Animation::GetSpriteSheet(int spriteSheetId)
{
	return spriteSheets[spriteSheetId];
}
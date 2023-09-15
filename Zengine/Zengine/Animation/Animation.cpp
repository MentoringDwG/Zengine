#include "Animation.h"
#include "KeyFrame.h"

void Animation::AddKeyFrame(KeyFrame* keyFrame)
{
	keyFrames.push_back(keyFrame);
}

std::vector<struct KeyFrame*> Animation::GetKeyFrames()
{
	return keyFrames;
}

void Animation::AddSpriteSheets(sf::Texture* texture)
{
	spriteSheets.push_back(texture);
}

sf::Texture* Animation::GetSpriteSheet(int spriteSheetId)
{
	return spriteSheets[spriteSheetId];
}
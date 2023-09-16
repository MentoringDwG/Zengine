#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Animation
{
public:
	void AddKeyFrame(int keyFrameIdIn, int spriteSheetIdIn, struct Vector2 startPointInSpriteSheetIn, struct Vector2 spriteSizeIn, int TimeStampIn);
	std::vector<struct KeyFrame*> GetKeyFrames();
	void AddSpriteSheets(std::string spriteSheetPath);
	sf::Texture* GetSpriteSheet(int spriteSheetId);

private:
	std::vector<struct KeyFrame*> keyFrames;
	std::vector<sf::Texture*> spriteSheets;
};


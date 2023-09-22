#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Animation
{
public:
	Animation(std::string animationDefinitionJsonPathIn);
	~Animation();
	void AddKeyFrame(int keyFrameIdIn, int spriteSheetIdIn, struct Vector2 startPointInSpriteSheetIn, struct Vector2 spriteSizeIn, int TimeStampIn);
	std::vector<struct KeyFrame*> GetKeyFrames();
	void AddSpriteSheets(std::string spriteSheetPath);
	sf::Texture* GetSpriteSheet(int spriteSheetId);

private:
	struct AnimationDefinition* animationDefinition = nullptr;
	std::vector<struct KeyFrame*> keyFrames;
	std::vector<sf::Texture*> spriteSheets;
};


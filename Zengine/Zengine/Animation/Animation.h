#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Animation
{
public:
	Animation(struct AnimationDefinition* animationDefinition);
	~Animation();
	std::vector<struct KeyFrame*> GetKeyFrames();
	sf::Texture* GetSpriteSheet(int spriteSheetId);

private:
	struct AnimationDefinition* animationDefinition = nullptr;
	std::vector<struct KeyFrame*> keyFrames;
	std::vector<sf::Texture*> spriteSheets;
};


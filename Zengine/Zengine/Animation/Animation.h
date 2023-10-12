// Copyright Z.Z. Zengine (c)

#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class Animation
{
public:
	Animation(std::shared_ptr<struct AnimationDefinition> animationDefinition);
	~Animation();
	std::vector<struct KeyFrame*> GetKeyFrames();
	sf::Texture* GetSpriteSheet(int spriteSheetId);

private:
	std::shared_ptr<struct AnimationDefinition> animationDefinition = nullptr;
	std::vector<struct KeyFrame*> keyFrames;
	std::vector<sf::Texture*> spriteSheets;
};


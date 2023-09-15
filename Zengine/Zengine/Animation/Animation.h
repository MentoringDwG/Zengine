#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Animation
{
public:
	void AddKeyFrame(struct KeyFrame* keyFrame);
	std::vector<struct KeyFrame*> GetKeyFrames();
	void AddSpriteSheets(sf::Texture* texture);
	sf::Texture* GetSpriteSheet(int spriteSheetId);

private:
	std::vector<struct KeyFrame*> keyFrames;
	std::vector<sf::Texture*> spriteSheets;
};


#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Animation;

class Animator
{
public:
	Animator(class ZenShape* ownerIn);
	void Play();
	void AddAnimation(Animation* animation);
	void DeleteAnimation(Animation* animation);
	void SetCurrentAnimation(int id);
	int GetCurrentAnimation();

	bool canPlayAnimation = false;

private:
	class ZenShape* owner = nullptr;
	std::vector<Animation*> animations;
	sf::IntRect rectSpriteSheet = sf::IntRect(0, 0, 0, 0);
	Animation* currentAnimation = nullptr;
	int currentKeyFrameId = 0;
	int currentAnimationID = 0;
	sf::Clock clock;
};


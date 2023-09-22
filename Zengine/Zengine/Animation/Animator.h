#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Animation;

class Animator
{
public:
	Animator(class ZenShape* ownerIn);
	void Update();
	int AddAnimation(Animation* animation);
	void DeleteAnimation(Animation* animation);
	void SetCurrentAnimation(int id);
	int GetCurrentAnimation();

	void Play();
	void Pause();
	void Stop();

private:
	sf::Clock clock;
	sf::IntRect rectSpriteSheet = sf::IntRect(0, 0, 0, 0);
	std::vector<Animation*> animations;
	int currentKeyFrameId = 0;
	int currentAnimationID = 0;
	class ZenShape* owner = nullptr;
	Animation* currentAnimation = nullptr;
	bool canPlayAnimation = false;
};


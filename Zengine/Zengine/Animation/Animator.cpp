#include "Animator.h"
#include "Animation.h"
#include "../ZenObject/ZenShape.h"
#include "../Animation/AnimationProcesor.h"
#include "KeyFrame.h"

#include <iostream>

Animator::Animator(ZenShape* ownerIn): owner(ownerIn)
{
	clock.restart();
	AnimationProcesor::Get()->AddAnimator(this);
}

void Animator::Play()
{
	if (canPlayAnimation == false) return;
	if (currentAnimation == nullptr) return;

	int numberOfKeyFrames = (int)currentAnimation->GetKeyFrames().size();
	KeyFrame keyFrame = *currentAnimation->GetKeyFrames()[currentKeyFrameId];

	if (clock.getElapsedTime().asMilliseconds() >= currentAnimation->GetKeyFrames()[currentKeyFrameId]->timeStamp)
	{
		rectSpriteSheet = sf::IntRect((int)keyFrame.startPointInSpriteSheet.x, (int)keyFrame.startPointInSpriteSheet.y, (int)keyFrame.spriteSize.x, (int)keyFrame.spriteSize.y);
		owner->SetTexture(currentAnimation->GetSpriteSheet(keyFrame.spriteSheetId));
		owner->Draw()->setTextureRect(rectSpriteSheet);

		if (currentKeyFrameId < numberOfKeyFrames - 1)
		{
			currentKeyFrameId++;
		}
		else
		{
			currentKeyFrameId = 0;
		}

		clock.restart();
	}
}

void Animator::AddAnimation(Animation* animation)
{
	animations.push_back(animation);
}

void Animator::DeleteAnimation(Animation* animation)
{
	for (auto itr = animations.begin(); itr <= animations.end(); itr++)
	{
		if (*itr == animation)
		{
			animations.erase(itr);
			return;
		}
	}
}

void Animator::SetCurrentAnimation(int id)
{
	if (currentAnimationID != id)
	{
		currentAnimation = animations[id];
		currentKeyFrameId = 0;
		currentAnimationID = id;
	}
}

int Animator::GetCurrentAnimation()
{
	return currentAnimationID;
}

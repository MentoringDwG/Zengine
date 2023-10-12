// Copyright Z.Z. Zengine (c)

#include "AnimationProcesor.h"
#include "Animator.h"

AnimationProcesor AnimationProcesor::instance;

void AnimationProcesor::AddAnimator(Animator* animator)
{
	animators.push_back(animator);
}

void AnimationProcesor::DeleteAnimator(Animator* animator)
{
	for (auto itr = animators.begin(); itr <= animators.end(); itr++)
	{
		if (*itr == animator)
		{
			animators.erase(itr);
			return;
		}
	}
}

void AnimationProcesor::PlayAnimations()
{
	for (int i = 0; i < animators.size(); i++)
	{
		animators[i]->Update();
	}
}
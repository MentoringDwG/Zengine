// Copyright Z.Z. Zengine (c)

#pragma once

#include <vector>

class Animator;

class AnimationProcesor
{
public:
	static AnimationProcesor* Get() { return &instance; }

	void AddAnimator(Animator* animator);
	void DeleteAnimator(Animator* animator);
	void PlayAnimations();

private:
	AnimationProcesor() {}
	~AnimationProcesor() {};

	static AnimationProcesor instance;

	std::vector<Animator*> animators;
};


// Copyright Z.Z. Zengine (c)

#pragma once

#include <iostream>
#include <vector>
#include <memory>

class AnimationDefinitionManager
{
public:
	static AnimationDefinitionManager* Get() { return &instance; }

	void AddAnimationDefinition(std::string animationDefimitionJsonPathIn, std::string nameIn);
	std::shared_ptr<struct AnimationDefinition> GetAnimationDefinition(std::string name);
	void DeleteAnimationDefinition(std::shared_ptr<struct AnimationDefinition> animationDefinition);

private:
	AnimationDefinitionManager() {}
	~AnimationDefinitionManager() {};

	static AnimationDefinitionManager instance;
	std::vector<std::shared_ptr<struct AnimationDefinition>> animationDefinitions;
};


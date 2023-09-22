#pragma once

#include <iostream>
#include <vector>

class AnimationDefinitionManager
{
public:
	static AnimationDefinitionManager* Get() { return &instance; }

	void AddAnimationDefinition(std::string animationDefimitionJsonPathIn, std::string nameIn);
	struct AnimationDefinition* GetAnimationDefinition(std::string name);
	void DeleteAnimationDefinition(struct AnimationDefinition* animationDefinition);


private:
	AnimationDefinitionManager() {}
	~AnimationDefinitionManager() {};

	static AnimationDefinitionManager instance;
	std::vector<struct AnimationDefinition*> animationDefinitions;
};


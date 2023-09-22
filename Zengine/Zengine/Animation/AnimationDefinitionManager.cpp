#include "AnimationDefinitionManager.h"
#include "AnimationDefinition.h"

AnimationDefinitionManager AnimationDefinitionManager::instance;

void AnimationDefinitionManager::AddAnimationDefinition(std::string animationDefimitionJsonPathIn, std::string nameIn)
{
	AnimationDefinition* animationDefinition = new AnimationDefinition(animationDefimitionJsonPathIn, nameIn);
	animationDefinitions.push_back(animationDefinition);
}

AnimationDefinition* AnimationDefinitionManager::GetAnimationDefinition(std::string name)
{
	for (int i = 0; i < animationDefinitions.size(); i++)
	{
		if (animationDefinitions[i]->name == name)
		{
			return animationDefinitions[i];
		}
	}

	return nullptr;
}

void AnimationDefinitionManager::DeleteAnimationDefinition(struct AnimationDefinition* animationDefinition)
{
	for (auto itr = animationDefinitions.begin(); itr <= animationDefinitions.end(); itr++)
	{
		if (*itr == animationDefinition)
		{
			animationDefinitions.erase(itr);
		}
	}
}
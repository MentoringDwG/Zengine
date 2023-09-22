#pragma once
class AnimationDefinitionManager
{
public:
	static AnimationDefinitionManager* Get() { return &instance; }


private:
	AnimationDefinitionManager() {}
	~AnimationDefinitionManager() {};

	static AnimationDefinitionManager instance;

};


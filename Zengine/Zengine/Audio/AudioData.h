// Copyright Z.Z. Zengine (c)

#include <string>
#include <vector>

struct SoundDefinition
{
	std::string SoundKey;
	std::string SoundName;
};

struct Soundbank
{
	std::string SoundBankPath;
	std::vector<SoundDefinition> Sounds;

	void LoadSoundDefinitionsFromPath();
};

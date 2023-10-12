// Copyright Z.Z. Zengine (c)

#include "AudioSystem.h"
#include <iostream>

sf::Sound* AudioSystem::GetSoundFromPool()
{
	// ¯aneta znajdzie pierwszy wolny dŸwiêk z puli.
	return soundPool[0];
}

void AudioSystem::Initialize()
{
	soundPool.push_back(new sf::Sound());

	sounds.SoundBankPath = "../Mario/Audio/Sounds";
	musics.SoundBankPath = "../Mario/Audio/Music";
	
	LoadSoundbanks();
}

void AudioSystem::LoadSoundbanks()
{
	sounds.LoadSoundDefinitionsFromPath();
	if (sounds.Sounds.size() == 0)
	{
		std::cout << std::endl << "The sounds folder is empty";
	}
	else
	{
		for (int i = 0; i < sounds.Sounds.size(); i++)
		{
			zenSound.push_back(ZenSound(sounds.Sounds[i].SoundKey));
		}
	}

	musics.LoadSoundDefinitionsFromPath();
	if (musics.Sounds.size() == 0)
	{
		std::cout<< std::endl << "The music folder is empty";
	}
	else
	{
		for (int i = 0; i < musics.Sounds.size(); i++)
		{
			zenSound.push_back(ZenSound(musics.Sounds[i].SoundKey));
		}
	}
}

void AudioSystem::PlaySingleShot(std::string SoundKey)
{	
	std::string path = sounds.GetSoundDefinition(SoundKey).SoundName;
	
	for (int i = 0; i < zenSound.size(); i++)
	{
		if (zenSound[i].soundKey == SoundKey)
		{
			if (!zenSound[i].GetSoundBuffer().loadFromFile(path))
			{
				std::cout << std::endl << "Failed to load audio file: " << path << std::endl;
				return;
			}

			sf::Sound* sound = GetSoundFromPool();
			sound->setBuffer(zenSound[i].GetSoundBuffer());
			sound->play();

			return;
		}
	}

	std::cout << std::endl << "There is no ZenSound with the given key in the pool";
}


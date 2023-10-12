// Copyright Z.Z. Zengine (c)

#include "AudioSystem.h"
#include <iostream>

sf::Sound* AudioSystem::GetSoundFromPool()
{
	if (soundPool.size() == 0)
	{
		soundPool.push_back(new sf::Sound());

		return soundPool[0];
	}
	else
	{
		for (int i = 0; i < soundPool.size(); i++)
		{
			if (soundPool[i]->getStatus() != sf::SoundSource::Playing)
			{
				return soundPool[i];
			}
		}

		if (soundPool.size() < 250)
		{
			soundPool.push_back(new sf::Sound());

			return soundPool[soundPool.size()-1];
		}
		else
		{
			return soundPool[0];
		}
	}
}

void AudioSystem::Initialize()
{	
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
		AddZenSounds(sounds);
	}

	musics.LoadSoundDefinitionsFromPath();
	if (musics.Sounds.size() == 0)
	{
		std::cout<< std::endl << "The music folder is empty";
	}
	else
	{
		AddZenSounds(musics);
	}
}

void AudioSystem::AddZenSounds(Soundbank soundBank)
{
	for (int i = 0; i < soundBank.Sounds.size(); i++)
	{
		if (zenSound.size() < 250)
		{
			zenSound.push_back(ZenSound(soundBank.Sounds[i].SoundKey));
		}
		else
		{
			std::cout << std::endl << "Too many ZenSounds";
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

void AudioSystem::PlayMusic(std::string SoundKey)
{
	std::string path = musics.GetSoundDefinition(SoundKey).SoundName;

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
			sound->setLoop(true);
			sound->setVolume(80);
			sound->play();

			return;
		}
	}

	std::cout << std::endl << "There is no ZenSound with the given key in the pool";
}


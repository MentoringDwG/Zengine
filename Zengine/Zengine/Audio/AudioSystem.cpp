// Copyright Z.Z. Zengine (c)

#include "AudioSystem.h"
#include <iostream>

#pragma optimize("", off)

sf::Sound& AudioSystem::GetSoundFromPool()
{
	// ¯aneta znajdzie pierwszy wolny dŸwiêk z puli.
	return soundPool[0];
}

void AudioSystem::Initialize()
{
	sounds.SoundBankPath = "../Mario/Audio/Sounds";
	musics.SoundBankPath = "../Mario/Audio/Music";
	
	LoadSoundbanks();
}

void AudioSystem::LoadSoundbanks()
{
	sounds.LoadSoundDefinitionsFromPath();
	// #TODO: ¯aneta zrobi ³adowanie muzyki i obs³u¿y przypadek gdy œcie¿ka bêdzie pusta.
	// musics.LoadSoundDefinitionsFromPath();
}

void AudioSystem::PlaySingleShot()
{	
	std::string path = "../Mario/Audio/Sounds/cricket.wav";
	if (!soundBuffer.loadFromFile(path))
	{
		std::cout<<"Failed to load audio file: "<< path << std::endl;
		return;
	}

	cricket.setBuffer(soundBuffer);

	cricket.setLoop(true);
	cricket.play();
}

#pragma optimize("", on)

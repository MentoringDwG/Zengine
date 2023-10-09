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
	sounds.SoundBankPath = "Z:/KnowHow/Mentoring/Zengine/Zengine/Mario/Audio/Sounds";
	musics.SoundBankPath = "Z:/KnowHow/Mentoring/Zengine/Zengine/Mario/Audio/Music";
	
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
	std::string path = "Z:/KnowHow/Mentoring/Zengine/Zengine/Mario/Audio/Sounds/cricket.wav";
	if (!soundBuffer.loadFromFile(path))
	{
		std::cout<<"Failed to load audio file: "<< path << std::endl;
		return;
	}

	cricket.setBuffer(soundBuffer);

	cricket.play();
}

#pragma optimize("", on)

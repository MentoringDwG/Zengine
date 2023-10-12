// Copyright Z.Z. Zengine (c)

#include "AudioData.h"

#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

void Soundbank::LoadSoundDefinitionsFromPath()
{
	const std::filesystem::path soundbankPathName{ "soundbank" };

	if (SoundBankPath == "")
	{
		std::cout << std::endl << "No path to load Soundbank";
		return;
	}
	
	try
	{
		for (const auto& entry : fs::directory_iterator(SoundBankPath))
		{
			SoundDefinition soundDefinition;
			soundDefinition.SoundName = entry.path().generic_string();
			
			std::string key = entry.path().filename().generic_string();

			for (int i = 0; i < key.size(); i++)
			{
				if (key[i] == '.')
				{
					i = key.size();
				}
				else
				{
					soundDefinition.SoundKey += key[i];
				}
			}

			Sounds.push_back(soundDefinition);
		}
	}

	catch (fs::filesystem_error const& ex)
	{
		std::cout << "what():  " << ex.what() << '\n'
			<< "path1(): " << ex.path1() << '\n'
			<< "path2(): " << ex.path2() << '\n'
			<< "code().value():    " << ex.code().value() << '\n'
			<< "code().message():  " << ex.code().message() << '\n'
			<< "code().category(): " << ex.code().category().name() << '\n';
	}
}

SoundDefinition Soundbank::GetSoundDefinition(std::string SoundKey)
{
	for (int i = 0; i < Sounds.size(); i++)
	{
		if (Sounds[i].SoundKey == SoundKey)
		{
			return Sounds[i];
		}
	}

	SoundDefinition soundDefinition;
	return soundDefinition;
}
#include "AudioData.h"

#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

void Soundbank::LoadSoundDefinitionsFromPath()
{
	const std::filesystem::path soundbankPathName{ "soundbank" };

	// #TODO: Sprawdzic poprawnosc sciezki. Wczytac tylko wspierane formaty.

	// #TODO: Co siê stanie jeœli SoundBankPath bêdzie pusty.
	for (const auto& entry : fs::directory_iterator(SoundBankPath))
	{
		std::cout << entry.path() << std::endl;
		SoundDefinition soundDefinition;
		soundDefinition.SoundName = entry.path().generic_string();

		// #TODO: Nazwa utworu, bez rozszerzenia		
		soundDefinition.SoundKey = entry.path().filename().generic_string();			
	}
}
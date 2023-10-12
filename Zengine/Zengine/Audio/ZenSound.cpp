// Copyright Z.Z. Zengine (c)

#include "ZenSound.h"

ZenSound::ZenSound(std::string soundKeyIn) : soundKey(soundKeyIn)
{

};

sf::SoundBuffer& ZenSound::GetSoundBuffer()
{
	return soundBuffer;
}
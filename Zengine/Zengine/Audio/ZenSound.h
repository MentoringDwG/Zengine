// Copyright Z.Z. Zengine (c)

#include <string>
#include <SFML/Audio.hpp>

// Instancja dŸwiêku
class ZenSound
{
public:
	ZenSound(std::string soundKeyIn);
	sf::SoundBuffer& GetSoundBuffer();
	
	std::string soundKey = "";

private:
	sf::SoundBuffer soundBuffer;
	int soundId = 0;
};

#include <vector>

#include "ZenSound.h"
#include "AudioData.h"

class AudioSystem
{	
	sf::Sound& GetSoundFromPool();

public:

	void Initialize();
	void LoadSoundbanks();
	void PlaySingleShot();

	std::vector<ZenSound> zenSound;

	Soundbank sounds;
	Soundbank musics;

	sf::SoundBuffer soundBuffer;

	std::vector<sf::Sound> soundPool;
	std::vector<sf::Sound> musicPool;

	sf::Sound cricket;
};

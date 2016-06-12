#pragma once
#include <SFML/Audio.hpp>
#include <string>
#include <vector>

class Audio
{
public:
	Audio();
	~Audio();
	void setBackgroundMusic(std::string);
	void playTestSound();
private:
	sf::Music backgroundMusic;
	std::vector<sf::SoundBuffer> buffers;
	std::vector<sf::Sound> sounds;
};
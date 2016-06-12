#pragma once
#include <SFML/Audio.hpp>
#include <string>

class Audio
{
public:
	Audio();
	~Audio();
	void setBackgroundMusic(std::string);
	void playGunSound();
	void playMeleeSound();
	void playBackgroundMusic();
	void stopBackgroundMusic();
	void setSoundsVolume(float);
	void setMusicVolume(float);
private:
	sf::Music backgroundMusic;
	sf::SoundBuffer gunSoundBuffer;
	sf::SoundBuffer meleeSoundBuffer;
	sf::Sound gunSound;
	sf::Sound meleeSound;
};
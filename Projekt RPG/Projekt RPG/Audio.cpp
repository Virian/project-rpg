#include "Audio.h"

Audio::Audio()
{
	gunSoundBuffer.loadFromFile("sounds/gun.ogg");
	gunSound.setBuffer(gunSoundBuffer);
	meleeSoundBuffer.loadFromFile("sounds/melee.ogg");
	meleeSound.setBuffer(meleeSoundBuffer);
	backgroundMusic.setLoop(true);
	setSoundsVolume(65.f);
	setMusicVolume(45.f);
}

Audio::~Audio()
{

}

void Audio::setBackgroundMusic(std::string filePath)
{
	backgroundMusic.openFromFile(filePath);
}

void Audio::playGunSound()
{
	gunSound.play();
}

void Audio::playMeleeSound()
{
	meleeSound.play();
}

void Audio::playBackgroundMusic()
{
	backgroundMusic.play();
}

void Audio::stopBackgroundMusic()
{
	backgroundMusic.stop();
}

void Audio::setSoundsVolume(float volume)
{
	gunSound.setVolume(volume);
	meleeSound.setVolume(volume);
}

void Audio::setMusicVolume(float volume)
{
	backgroundMusic.setVolume(volume);
}
#include "Audio.h"

Audio::Audio()
{
	sf::SoundBuffer buffer;
	sf::Sound testSound;

	buffer.loadFromFile("test2.ogg");
	buffers.push_back(buffer);
	testSound.setBuffer(buffers[0]);
	sounds.push_back(testSound);
}

Audio::~Audio()
{

}

void Audio::setBackgroundMusic(std::string filePath)
{
	backgroundMusic.openFromFile(filePath);
}

void Audio::playTestSound()
{
	sounds[0].play();
}
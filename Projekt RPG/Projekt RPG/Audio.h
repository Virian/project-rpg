#pragma once
#include <SFML/Audio.hpp>
#include <string>

class Audio
{
public:
	Audio();
	~Audio();
	void setBackgroundMusic(std::string);	/*ustawia muzyke w tle na muzyke podana przez argument jako sciezke*/
	void playGunSound();					/*odtwarza dzwiek broni palnej*/
	void playMeleeSound();					/*odtwarza dzwiek uderzenia z bliska*/
	void playBackgroundMusic();				/*odtwarza muzyke w tle*/
	void stopBackgroundMusic();				/*przerywa odtwarzanie muzyki w tle*/
	void setSoundsVolume(float);			/*ustawia poziom glosnosci dzwiekow*/
	void setMusicVolume(float);				/*ustawia poziom glosnosci muzyki*/
private:
	sf::Music backgroundMusic;				/*muzyka w tle*/
	sf::SoundBuffer gunSoundBuffer;			/*bufor na dzwiek broni palnej*/
	sf::SoundBuffer meleeSoundBuffer;		/*bufor na dzwiek uderzenia z bliska*/
	sf::Sound gunSound;						/*dzwiek broni palnej*/
	sf::Sound meleeSound;					/*dzwiek uderzenia z bliska*/
};
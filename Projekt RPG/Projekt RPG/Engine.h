#pragma once
#include "Player.h"
#include "Gui.h"
#include "Npc.h"
#include "Audio.h"

class Engine
{
private:
	Player* player;																/*gracz*/
	Gui gui;
	sf::View view;
	Level level;
	Audio audio;
	std::vector<Npc*> npcs;														/*wektor npcow*/
	enum Attacker { PLAYER, NPC };												/*wspomaga rozpoznawanie czy atakuje gracz czy npc*/
	sf::Texture tileTextures[Tile::COUNT];										/*tablica na tekstury wszystkich mozliwych kafli*/
	std::vector<std::vector<sf::Sprite>> tileSprites;							/*kontener sprite'ow kafli do narysowania*/
	unsigned short tileCountHeight;												/*ilosc wyswietlanych kafli w pionie*/
	unsigned short tileCountWidth;												/*ilosc wyswietlanych kafli w poziomie*/
	void draw(sf::RenderWindow&, sf::Sprite&, bool, bool, bool, bool, short);	/*odpowiada za rysowanie wszyskiego na ekranie*/
	void setMap(sf::RenderWindow&, std::string, unsigned short);				/*ustawia odpowiedni poziom(mape)*/
	void updateMap();															/*ustawia kamere oraz ktore kafle maja byc rysowane*/
	void fight(size_t, Attacker);												/*odpowiada za walke gracza z npc*/
	void saveGame(unsigned short);												/*zapisuje stan gry do pliku*/
	bool checkCursor();															/*sprawdza czy kursor jest nad ktoryms z przeciwnikow*/
public:
	Engine(sf::RenderWindow&, sf::Sprite&, std::string, int);					/*konstruktor gdy zaczynamy nowa gre*/
	Engine(sf::RenderWindow&, sf::Sprite&, std::fstream&);						/*konstruktor gdy wczytujemy gre*/
	~Engine();
	void startEngine(sf::RenderWindow&, sf::Sprite&);							/*metoda odpowiadajaca za dzialanie calej gry*/
};
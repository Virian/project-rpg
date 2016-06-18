#pragma once
#include "Player.h"
#include "Gui.h"
#include "Npc.h"
#include "Audio.h"

class Engine
{
private:
	Player* player;
	Gui gui;
	sf::View view;
	Level level;
	Audio audio;
	std::vector<Npc*> npcs;
	enum Attacker { PLAYER, NPC };
	sf::Texture tileTextures[Tile::COUNT]; /*tablica na tekstury kafli*/
	std::vector<std::vector<sf::Sprite>> tileSprites; /*kontener sprite'ow kafli*/
	unsigned short tileCountHeight; /*ilosc wyswietlanych kafli w pionie*/
	unsigned short tileCountWidth; /*ilosc wyswietlanych kafli w poziomie*/
	void draw(sf::RenderWindow&, sf::Sprite&, bool, bool, bool, bool, short);
	void setMap(sf::RenderWindow&, std::string, unsigned short);
	void updateMap();
	void fight(size_t, Attacker);
	void saveGame(unsigned short);
	bool checkCursor();
public:
	Engine(sf::RenderWindow&, sf::Sprite&, std::string, int);
	Engine(sf::RenderWindow&, sf::Sprite&, std::fstream&);
	~Engine();
	void startEngine(sf::RenderWindow&, sf::Sprite&);
};
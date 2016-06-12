#pragma once
#include "Player.h"
#include "Gui.h"
#include "Npc.h"

using namespace sf;

class Engine
{
private:
	Player* player;
	Gui gui;
	View view;
	Level level;
	vector<Npc*> npcs;
	enum Attacker { PLAYER, NPC };
	Texture tileTextures[Tile::COUNT]; /*tablica na tekstury kafli*/
	vector<vector<Sprite>> tileSprites; /*kontener sprite'ow kafli*/
	unsigned short tileCountHeight; /*ilosc wyswietlanych kafli w pionie*/
	unsigned short tileCountWidth; /*ilosc wyswietlanych kafli w poziomie*/
	void draw(RenderWindow&, bool, bool, bool, short);
	void setMap(RenderWindow&, string, unsigned short);
	void updateMap();
	void fight(size_t, Attacker);
	void saveGame(unsigned short);
public:
	Engine(RenderWindow&, string, int);
	Engine(RenderWindow&, fstream&);
	~Engine();
	void startEngine(RenderWindow&);
};
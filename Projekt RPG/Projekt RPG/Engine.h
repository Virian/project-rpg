#pragma once
#include "Player.h"
#include "Gui.h"
#include "Npc.h"
#include "Audio.h"

using namespace sf;

class Engine
{
private:
	Player* player;
	Gui gui;
	View view;
	Level level;
	Audio audio;
	vector<Npc*> npcs;
	enum Attacker { PLAYER, NPC };
	Texture tileTextures[Tile::COUNT]; /*tablica na tekstury kafli*/
	vector<vector<Sprite>> tileSprites; /*kontener sprite'ow kafli*/
	unsigned short tileCountHeight; /*ilosc wyswietlanych kafli w pionie*/
	unsigned short tileCountWidth; /*ilosc wyswietlanych kafli w poziomie*/
	void draw(RenderWindow&, Sprite&, bool, bool, bool, bool, short);
	void setMap(RenderWindow&, string, unsigned short);
	void updateMap();
	void fight(size_t, Attacker);
	void saveGame(unsigned short);
	bool checkCursor();
public:
	Engine(RenderWindow&, Sprite&, string, int);
	Engine(RenderWindow&, Sprite&, fstream&);
	~Engine();
	void startEngine(RenderWindow&, Sprite&);
};
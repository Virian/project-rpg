#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Level.h"
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
	Texture tileTextures[Level::COUNT]; /*tablica na tekstury kafli*/
	vector<vector<Sprite>> tileSprites; /*kontener sprite'ow kafli*/
	unsigned short tileCountHeight; /*ilosc wyswietlanych kafli w pionie*/
	unsigned short tileCountWidth; /*ilosc wyswietlanych kafli w poziomie*/
	void draw(RenderWindow&, bool);
	void setMap(RenderWindow&, string);
	void updateMap();
public:
	Engine(RenderWindow&);
	~Engine();
	void startEngine(RenderWindow&);
};
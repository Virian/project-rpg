#pragma once
#include <string>
#include <vector>
#include "Tile.h"

using namespace std;

class Level
{
private:
	vector<Tile::Coord> npcsCoords;
	vector<vector<Tile*>> map;
	unsigned short height;
	unsigned short width;
	Tile::Coord playerSpawn;

	Tile* getTile(short);
public:	
	Level();
	~Level();
	bool load(string); /*bool - false jesli sie nie udalo wczytac*/
	unsigned short getHeight();
	unsigned short getWidth();
	Tile::Coord getPlayerSpawnCoords();
	vector<Tile::Coord> getNpcCoords();
	vector<vector<Tile*>> getMap();
};
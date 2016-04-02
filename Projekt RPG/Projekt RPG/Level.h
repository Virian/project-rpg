#pragma once
#include <string>
#include <vector>
#include "Tile.h"

using namespace std;

class Level
{
public:
	struct SpawnCoord
	{
		unsigned short x;
		unsigned short y;
	};
private:
	vector<SpawnCoord> npcsCoords;
	vector<vector<Tile*>> map;
	unsigned short height;
	unsigned short width;
	SpawnCoord playerSpawn;

	Tile* getTile(short);
public:	
	Level();
	~Level();
	bool load(string); /*bool - false jesli sie nie udalo wczytac*/
	unsigned short getHeight();
	unsigned short getWidth();
	SpawnCoord getPlayerSpawnCoords();
	vector<SpawnCoord> getNpcCoords();
	vector<vector<Tile*>> getMap();
};
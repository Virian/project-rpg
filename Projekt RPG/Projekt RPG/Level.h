#pragma once
#include <string>
#include <vector>
#include "Tile.h"
#include <SFML/System/Vector2.hpp>

using namespace std;

class Level
{
public:
	struct CoordAndType
	{
		Tile::Coord npcCoords;
		string enemyType;
	};
private:
	vector<CoordAndType> npcsCoordsAndTypes;
	vector<vector<Tile*>> map;
	unsigned short height;
	unsigned short width;
	Tile::Coord playerSpawn;
	string levelPath;

	Tile* getTile(short);
public:	
	Level();
	~Level();
	bool load(string); /*bool - false jesli sie nie udalo wczytac*/
	unsigned short getHeight();
	unsigned short getWidth();
	Tile::Coord getPlayerSpawnCoords();
	vector<CoordAndType> getNpcCoordsAndTypes();
	vector<vector<Tile*>> getMap();
	void spawnLootChest(sf::Vector2f);
	void deleteLootChest(sf::Vector2f);
	string getLevelPath();
	Tile::Coord getSaveCoords(unsigned short);
};
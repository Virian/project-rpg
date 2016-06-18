#pragma once
#include <string>
#include <vector>
#include "Tile.h"
#include <SFML/System/Vector2.hpp>

class Level
{
public:
	struct CoordAndType
	{
		Tile::Coord npcCoords;
		std::string enemyType;
	};
private:
	std::vector<CoordAndType> npcsCoordsAndTypes;
	std::vector<std::vector<Tile*>> map;
	unsigned short height;
	unsigned short width;
	Tile::Coord playerSpawn;
	std::string levelPath;

	Tile* getTile(short);
public:	
	Level();
	~Level();
	void clearMap();
	bool load(std::string); /*bool - false jesli sie nie udalo wczytac*/
	unsigned short getHeight();
	unsigned short getWidth();
	Tile::Coord getPlayerSpawnCoords();
	std::vector<CoordAndType> getNpcCoordsAndTypes();
	std::vector<std::vector<Tile*>> getMap();
	void spawnLootChest(sf::Vector2f);
	void deleteLootChest(sf::Vector2f);
	std::string getLevelPath();
	Tile::Coord getSaveCoords(unsigned short);
};
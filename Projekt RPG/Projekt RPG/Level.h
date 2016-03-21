#pragma once
#include <string>
#include <vector>

using namespace std;

class Level
{
public:
	struct SpawnCoord
	{
		unsigned short x;
		unsigned short y;
	};
	enum TileType { FLOOR1, WALL1, FLOOR2, CHEST1, TYPE5, TYPE6, TYPE7, TYPE8, COUNT }; /*Reminder - do zmiany na jakies normalne nazwy*/
	struct Tile
	{
		TileType type;
		//string interaction //rodzaj interakcji //jeszcze nie wiadomo jak to w ogole wykorzystac
		bool isWall;
		bool isInteraction;
	};
private:
	vector<SpawnCoord> npcsCoords;
	vector<vector<Tile>> map;
	unsigned short height;
	unsigned short width;
	SpawnCoord playerSpawn;

	Tile getTile(short);
public:	
	Level();
	~Level();
	bool load(string); /*bool - false jesli sie nie udalo wczytac*/
	unsigned short getHeight();
	unsigned short getWidth();
	SpawnCoord getPlayerSpawnCoords();
	vector<SpawnCoord> getNpcCoords();
	vector<vector<Tile>> getMap();
};
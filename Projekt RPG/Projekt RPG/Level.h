#pragma once
#include <string>
#include <vector>

using namespace std;

class Level
{
public:
	enum TileType { FLOOR1, WALL1, FLOOR2, CHEST1, TYPE5, TYPE6, TYPE7, TYPE8, COUNT }; /*Reminder - do zmiany na jakies normalne nazwy*/
	struct Tile
	{
		TileType type;
		//string interaction //rodzaj interakcji //jeszcze nie wiadomo jak to w ogole wykorzystac
		bool isWall;
		bool isInteraction;
	};
private:
	
	vector<vector<Tile>> map;
	unsigned short height;
	unsigned short width;
	unsigned short spawnCoordX;
	unsigned short spawnCoordY;

	Tile getTile(short);
public:	
	Level();
	~Level();
	bool load(string); /*bool - false jesli sie nie udalo wczytac*/
	unsigned short getHeight();
	unsigned short getWidth();
	unsigned short getSpawnCoordX();
	unsigned short getSpawnCoordY();
	vector<vector<Tile>> getMap();
};
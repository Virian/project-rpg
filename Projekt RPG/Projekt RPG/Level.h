#pragma once
#include <string>
#include <vector>

using namespace std;

class Level
{
private:
	enum TileType {TYPE1, TYPE2, TYPE3, TYPE4}; /*Reminder - do zmiany na jakies normalne nazwy*/
	struct Tile
	{
		TileType type;
		//string interaction //rodzaj interakcji //jeszcze nie wiadomo jak to w ogole wykorzystac
		bool isWall;
		bool isInteraction;
	};
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
};
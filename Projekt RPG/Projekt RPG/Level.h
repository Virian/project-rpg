#pragma once
#include <string>
#include <vector>
#include <SFML/System/Clock.hpp>

using namespace std;

class Tile
{
public:
	enum TileType { FLOOR1, WALL1, FLOOR2, CHEST1, TYPE5, TYPE6, TYPE7, TYPE8, COUNT }; /*Reminder - do zmiany na jakies normalne nazwy*/
	Tile();
	virtual ~Tile();
	void setType(short);
	void setProperties(bool, bool);
	bool isWall();
	bool isInteraction();
	TileType getType();
protected:
	TileType type;
	//string interaction //rodzaj interakcji //jeszcze nie wiadomo jak to w ogole wykorzystac
	bool wall;
	bool interaction;
};

class TrapFountain : public Tile
{
public:
	enum Character { TRAP, FOUNTAIN };
	Character character;
	TrapFountain();
	~TrapFountain();
	short getHpChange();
private:
	sf::Clock delay;
};

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
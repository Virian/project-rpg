#pragma once
#include <SFML/System/Clock.hpp>

class Tile
{
public:
	struct Coord
	{
		unsigned short x;
		unsigned short y;
	};
	enum TileType { FLOOR1, WALL1, FLOOR2, CHEST1, TRAP1, FOUNTAIN1, TELEPORT1, LOOTCHEST1, COUNT }; /*Reminder - do zmiany na jakies normalne nazwy*/
	Tile();
	Tile(short, bool, bool);
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
	TrapFountain(short, bool, bool, Character);
	~TrapFountain();
	short getHpChange();
private:
	sf::Clock delay;
};

class LootChest : public Tile
{
public:
	enum Content { POTION, ITEM };
	LootChest(short, bool, bool);
	LootChest(short, bool, bool, Tile*);
	~LootChest();
	Tile* getTileUnder();
	bool containsPotion();
private:
	Tile* tileUnder;
	Content content;
};

class Teleport : public Tile
{
public:
	Teleport();
	Teleport(short, bool, bool);
	~Teleport();
	Coord getDestination();
	void setDestination(Coord);
private:
	Coord destination;
};
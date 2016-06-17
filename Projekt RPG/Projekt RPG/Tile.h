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
	enum TileType { FLOOR1, WALL1, FLOOR2, CHEST1, TRAP1, FOUNTAIN1, SAVE1, LOOTCHEST1, FLOOR3, COUNT }; /*Reminder - do zmiany na jakies normalne nazwy*/
	Tile();
	Tile(short, bool);
	virtual ~Tile();
	void setType(short);
	void setProperties(bool);
	bool isWall();
	TileType getType();
protected:
	TileType type;
	bool wall;
};

class TrapFountain : public Tile
{
public:
	enum Character { TRAP, FOUNTAIN };
	Character character;
	TrapFountain();
	TrapFountain(short, bool, Character);
	~TrapFountain();
	short getHpChange();
private:
	sf::Clock delay;
};

class LootChest : public Tile
{
public:
	enum Content { POTION, ITEM };
	LootChest(short, bool);
	LootChest(short, bool, Tile*);
	~LootChest();
	Tile* getTileUnder();
	bool containsPotion();
private:
	Tile* tileUnder;
	Content content;
};

class Save : public Tile
{
public:
	Save(short, bool);
	~Save();
	unsigned short getId();
	static unsigned short saveCount;
private:
	unsigned short id;
};
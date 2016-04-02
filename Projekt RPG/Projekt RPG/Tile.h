#pragma once
#include <SFML/System/Clock.hpp>

class Tile
{
public:
	enum TileType { FLOOR1, WALL1, FLOOR2, CHEST1, TRAP1, FOUNTAIN1, TYPE7, TYPE8, COUNT }; /*Reminder - do zmiany na jakies normalne nazwy*/
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
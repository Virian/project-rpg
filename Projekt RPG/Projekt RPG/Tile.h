#pragma once
#include <SFML/System/Clock.hpp>

class Tile					
/*bazowa klasa kafelkow*/
{
public:
	struct Coord						/*struktura koordynatow*/
	{
		unsigned short x;
		unsigned short y;
	};
	enum TileType { FLOOR1, WALL1, FLOOR2, CHEST1, TRAP1, FOUNTAIN1, SAVE1, LOOTCHEST1, FLOOR3, COUNT }; /*typy kafli*/
	Tile(short, bool);
	virtual ~Tile();
	bool isWall();						/*zwraca true gdy kafel jest sciana i false gdy nia nie jest*/
	TileType getType();					/*zwraca typ kafla*/
protected:
	TileType type;						/*typ kafla*/
	bool wall;							/*true gdy kafel jest sciana*/
};

class TrapFountain : public Tile
/*po wejsciu na kafel tej klasy graczowi zmieniaja sie punkty zycia*/
{
public:
	enum Character { TRAP, FOUNTAIN };
	Character character;				/*jesli bedzie to pulapka, graczowi beda ubywac punkty zycia, jesli bedzie to fontanna, punkty zycia beda dodawane*/
	TrapFountain(short, bool, Character);
	~TrapFountain();
	short getHpChange();				/*zwraca ilosc hp do zmiany*/
private:
	sf::Clock delay;					/*hp moze przybywac/ubywac jedynie co okreslona ilosc czasu*/
};

class LootChest : public Tile
/*kafel tworzony jedynie w momencie gdy umiera przeciwnik*/
/*skrzynka z przedmiotem w srodku*/
{
public:
	enum Content { POTION, ITEM };		/*moze zawierac albo miksture zycia albo przedmiot(bron/zbroje)*/
	LootChest(short, bool, Tile*);
	~LootChest();
	Tile* getTileUnder();				/*zwraca jaki kafel znajduje sie pod skrzynia*/
	bool containsPotion();				/*zwraca true jesli zawiera miksture*/
private:
	Tile* tileUnder;					/*kafel ktory jest pod skrzynia*/
	Content content;					/*zawartosc skrzyni*/
};

class Save : public Tile
/*kafel na ktorym trzeba stanac aby zapisac gre/zmienic poziom*/
{
public:
	Save(short, bool);
	~Save();
	unsigned short getId();				/*zwraca id miejsca do zapisu*/
	static unsigned short saveCount;	/*ilosc miejsc do zapisu na danym poziomie*/
private:
	unsigned short id;					/*id konkretnego miejsca do zapisu - musze byc rozroznialne miedzy soba*/
};
#pragma once
#include <string>
#include <vector>
#include "Tile.h"
#include <SFML/System/Vector2.hpp>

class Level
{
public:
	struct CoordAndType									/*struktura zawierajaca koordynaty oraz typ przecziwnika ktory ma sie znalezc na tych koordynatach*/
	{
		Tile::Coord npcCoords;
		std::string enemyType;
	};
private:
	std::vector<CoordAndType> npcsCoordsAndTypes;		/*kontener koordynatow i typow przeciwnikow ktorzy maja sie znalezc na danym poziomie*/
	std::vector<std::vector<Tile*>> map;				/*dwuwymiarowy kontener kafli, ktory jest reprezentacja calego poziomu*/
	unsigned short height;								/*wysokosc poziomu*/
	unsigned short width;								/*szerokosc poziomu*/
	Tile::Coord playerSpawn;							/*koordynaty na ktorych pojawia sie gracz po wejsciu na poziom*/
	std::string levelPath;								/*sciezka dostepu do poziomu*/

	Tile* getTile(short);								/*zwraca kafel o podanym kodzie*/
public:	
	Level();
	~Level();
	void clearMap();									/*czysci caly kontener z mapa*/
	bool load(std::string);								/*zwraca true jesli poziom zostanie poprawnie wczytany*/
	unsigned short getHeight();							/*zwraca wysokosc poziomu*/
	unsigned short getWidth();							/*zwraca szerokosc poziomu*/
	Tile::Coord getPlayerSpawnCoords();					/*zwraca koordynaty na ktorych pojawia sie gracz po wejsciu na poziom*/
	std::vector<CoordAndType> getNpcCoordsAndTypes();	/*zwraca kontener koordynatow i typow przeciwnikow ktorzy maja sie znalezc na danym poziomie*/
	std::vector<std::vector<Tile*>> getMap();			/*zwraca mape poziomu*/
	void spawnLootChest(sf::Vector2f);					/*wstawia skrzynke z nagroda na podanej pozycji*/
	void deleteLootChest(sf::Vector2f);					/*usuwa skrzynke z nagroda z podanej pozycji*/
	std::string getLevelPath();							/*zwraca sciezke dostepu do poziomu*/
	Tile::Coord getSaveCoords(unsigned short);			/*zwraca koordynaty kafla zapisu o podanym id*/
};
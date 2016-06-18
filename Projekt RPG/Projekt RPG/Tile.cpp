#include "Tile.h"
#include <Windows.h>

Tile::Tile(short tileCode, bool _wall) : wall(_wall)
{
	type = TileType(tileCode); /*przypisanie typu w zaleznosci od kodu kafla*/
}

Tile::~Tile()
{

}

bool Tile::isWall()
{
	return wall;
}

Tile::TileType Tile::getType()
{
	return type;
}

TrapFountain::TrapFountain(short tileCode, bool _wall, TrapFountain::Character _character) : Tile(tileCode, _wall), character(_character)
{

}

TrapFountain::~TrapFountain()
{

}

short TrapFountain::getHpChange()
{
	if (delay.getElapsedTime().asSeconds() > 2) /*zadawanie obrazen/leczenie moze sie odbywac co 2 sekundy*/
	{
		if (character == TRAP)
		{
			delay.restart();
			return -10; /*jesli jest to pulapka - zadawanie obrazen*/
		}
		else
		{
			delay.restart();
			return 10; /*jesli jest to fontanna - leczenie*/
		}
	}
	else return 0;
}

LootChest::LootChest(short tileCode, bool _wall, Tile* _tileUnder) : Tile(tileCode, _wall), tileUnder(_tileUnder)
{
	/*40% szans na przedmiot, 60% na miksture*/
	if (rand() % 101 > 59) content = ITEM;
	else content = POTION;
}

LootChest::~LootChest()
{
	
}

Tile* LootChest::getTileUnder()
{
	return tileUnder;
}

bool LootChest::containsPotion()
{
	if (content == POTION) return true;
	else return false;
}

unsigned short Save::saveCount = 0;

Save::Save(short tileCode, bool _wall) : Tile(tileCode, _wall)
{
	id = ++saveCount;	/*id indeksowane od 1*/
}

Save::~Save()
{
	--saveCount;
}

unsigned short Save::getId()
{
	return id;
}
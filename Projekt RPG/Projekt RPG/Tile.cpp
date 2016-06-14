#include "Tile.h"
#include <Windows.h>

Tile::Tile()
{

}

Tile::Tile(short tileCode, bool _wall) : wall(_wall)
{
	type = TileType(tileCode);
}

Tile::~Tile()
{

}

void Tile::setType(short tileCode)
{
	type = TileType(tileCode);
}

void Tile::setProperties(bool _wall)
{
	wall = _wall;
}

bool Tile::isWall()
{
	return wall;
}

Tile::TileType Tile::getType()
{
	return type;
}

TrapFountain::TrapFountain()
{

}

TrapFountain::TrapFountain(short tileCode, bool _wall, TrapFountain::Character _character) : Tile(tileCode, _wall), character(_character)
{

}

TrapFountain::~TrapFountain()
{

}

short TrapFountain::getHpChange()
{
	if (delay.getElapsedTime().asSeconds() > 2)
	{
		if (character == TRAP)
		{
			delay.restart();
			return -10;
		}
		else
		{
			delay.restart();
			return 10;
		}
	}
	else return 0;
}

LootChest::LootChest(short tileCode, bool _wall) : Tile(tileCode, _wall)
{
	tileUnder = nullptr;
	if (rand() % 100 + 1 > 60) content = ITEM;
	else content = POTION;
}

LootChest::LootChest(short tileCode, bool _wall, Tile* _tileUnder) : Tile(tileCode, _wall), tileUnder(_tileUnder)
{
	if (rand() % 100 + 1 > 60) content = ITEM;
	else content = POTION;
}

LootChest::~LootChest()
{
	/*Reminder - gdy wychodzimy z gry gdy chest stoi to pewnie bedzie wyciek pamieci*/
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
	id = ++saveCount;	
}

Save::~Save()
{
	--saveCount;
}

unsigned short Save::getId()
{
	return id;
}
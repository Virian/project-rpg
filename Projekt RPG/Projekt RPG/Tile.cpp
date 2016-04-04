#include "Tile.h"

Tile::Tile()
{

}

Tile::Tile(short tileCode, bool _wall, bool _interaction) : wall(_wall), interaction(_interaction)
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

void Tile::setProperties(bool _wall, bool _interaction)
{
	wall = _wall;
	interaction = _interaction;
}

bool Tile::isWall()
{
	return wall;
}

bool Tile::isInteraction()
{
	return interaction;
}

Tile::TileType Tile::getType()
{
	return type;
}

TrapFountain::TrapFountain()
{

}

TrapFountain::TrapFountain(short tileCode, bool _wall, bool _interaction, TrapFountain::Character _character) : Tile(tileCode, _wall, _interaction), character(_character)
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

Teleport::Teleport()
{

}

Teleport::Teleport(short tileCode, bool _wall, bool _interaction) : Tile(tileCode, _wall, _interaction)
{

}

Teleport::~Teleport()
{

}

Tile::Coord Teleport::getDestination()
{
	return destination;
}

void Teleport::setDestination(Tile::Coord dest)
{
	destination.x = dest.x;
	destination.y = dest.y;
}
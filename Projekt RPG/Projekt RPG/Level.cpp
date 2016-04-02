#include "Level.h"
#include <fstream>

Tile::Tile()
{

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

TrapFountain::~TrapFountain()
{

}

short TrapFountain::getHpChange()
{
	if (delay.getElapsedTime().asSeconds() > 2)
	{
		if (character == TRAP) return -10;
		else return 10;
	}
	else return 0;
}

Level::Level()
{
	height = 0;
	width = 0;
	playerSpawn.x = 0;
	playerSpawn.y = 0;
}

Level::~Level()
{

}

Tile Level::getTile(short tileCode)
{
	Tile tile;

	//tile.type = TileType(tileCode);
	tile.setType(tileCode);
	switch (Tile::TileType(tileCode))
	{
	case Tile::FLOOR1:
		/*tile.isWall = false;
		tile.isInteraction = false;*/
		tile.setProperties(false, false);
		break;
	case Tile::WALL1:
		/*tile.isWall = true;
		tile.isInteraction = false;*/
		tile.setProperties(true, false);
		break;
	case Tile::FLOOR2:
		/*tile.isWall = false;
		tile.isInteraction = false;*/
		tile.setProperties(false, false);
		break;
	case Tile::CHEST1:
		/*tile.isWall = true;
		tile.isInteraction = true;*/
		tile.setProperties(true, true);
		break;
	case Tile::TYPE5:
		/*tile.isWall = true;
		tile.isInteraction = true;*/
		tile.setProperties(true, true);
		break;
	case Tile::TYPE6:
		/*tile.isWall = true;
		tile.isInteraction = true;*/
		tile.setProperties(true, true);
		break;
	case Tile::TYPE7:
		/*tile.isWall = true;
		tile.isInteraction = true;*/
		tile.setProperties(true, true);
		break;
	case Tile::TYPE8:
		/*tile.isWall = true;
		tile.isInteraction = true;*/
		tile.setProperties(true, true);
		break;
	/*case Tile::TYPE9:
		//tile.isWall = true;
		//tile.isInteraction = true;
		tile.setProperties(true, true);
		break;*/
	default:
		/*tile.isWall = false;
		tile.isInteraction = false;*/
		tile.setProperties(false, false);
		break;
	}
	return tile;
}

bool Level::load(string filePath)
{
	fstream file;

	file.open(filePath);
	if (!file.is_open()) return false;
	file >> width >> height;
	if ((height == 0) || (width == 0))
	{
		file.close();
		return false;
	}
	map.resize(height);
	for (unsigned short i = 0; i < height; i++) map[i].resize(width);
	for (unsigned short y = 0; y < height; y++)
	{
		for (unsigned short x = 0; x < width; x++)
		{
			short tileCode;

			file >> tileCode;
			map[y][x] = getTile(tileCode);
		}
	}
	while (!file.eof())
	{
		string name;
		unsigned short x, y;

		file >> name;
		file >> x >> y;
		if (name == "[SPAWN]")
		{
			playerSpawn.x = x;
			playerSpawn.y = y;
		}
		else if (name == "[ENEMY]")
		{
			SpawnCoord tmp;
			tmp.x = x;
			tmp.y = y;
			npcsCoords.push_back(tmp);
		}
		/* else if reszta specjalnych kafelkow*/
	}
	file.close();
	return true;
}

unsigned short Level::getHeight()
{
	return height;
}

unsigned short Level::getWidth()
{
	return width;
}

Level::SpawnCoord Level::getPlayerSpawnCoords()
{
	return playerSpawn;
}

vector<Level::SpawnCoord> Level::getNpcCoords()
{
	return npcsCoords;
}

vector<vector<Tile>> Level::getMap()
{
	return map;
}
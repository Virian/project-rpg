#include "Level.h"
#include <fstream>

Level::Level()
{
	height = 0;
	width = 0;
	playerSpawn.x = 0;
	playerSpawn.y = 0;
}

Level::~Level()
{
	for (size_t i = 0; i < map.size(); ++i)
	{
		for (size_t j = 0; j < map[i].size(); ++j)
		{
			delete map[i][j];
		}
		map[i].clear();
	}
	map.clear();
}

Tile* Level::getTile(short tileCode)
{
	Tile* tile;

	switch (Tile::TileType(tileCode))
	{
	case Tile::FLOOR1:
		tile = new Tile(tileCode, false, false);
		break;
	case Tile::WALL1:
		tile = new Tile(tileCode, true, false);
		break;
	case Tile::FLOOR2:
		tile = new Tile(tileCode, false, false);
		break;
	case Tile::CHEST1:
		tile = new Tile(tileCode, true, true);
		break;
	case Tile::TRAP1:
		tile = new TrapFountain(tileCode, false, true, TrapFountain::TRAP);
		break;
	case Tile::FOUNTAIN1:
		tile = new TrapFountain(tileCode, false, true, TrapFountain::FOUNTAIN);
		break;
	case Tile::TELEPORT1:
		tile = new Tile(tileCode, false, true);
		break;
	case Tile::TYPE8:
		tile = new Tile(tileCode, true, true);
		break;
	/*case Tile::TYPE9:
		tile = new Tile(tileCode, true, true);
		break;*/
	default:
		tile = new Tile(tileCode, true, true);
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
			Tile::Coord tmp;
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

Tile::Coord Level::getPlayerSpawnCoords()
{
	return playerSpawn;
}

vector<Tile::Coord> Level::getNpcCoords()
{
	return npcsCoords;
}

vector<vector<Tile*>> Level::getMap()
{
	return map;
}
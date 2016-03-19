#include "Level.h"
#include <fstream>

Level::Level()
{
	height = 0;
	width = 0;
	spawnCoordX = 0;
	spawnCoordY = 0;
}

Level::~Level()
{

}

Level::Tile Level::getTile(short tileCode)
{
	Tile tile;

	tile.type = TileType(tileCode);
	switch (TileType(tileCode))
	{
	case FLOOR1:
		tile.isWall = false;
		tile.isInteraction = false;
		break;
	case WALL1:
		tile.isWall = true;
		tile.isInteraction = false;
		break;
	case FLOOR2:
		tile.isWall = false;
		tile.isInteraction = false;
		break;
	case CHEST1:
		tile.isWall = true;
		tile.isInteraction = true;
		break;
	case TYPE5:
		tile.isWall = true;
		tile.isInteraction = true;
		break;
	case TYPE6:
		tile.isWall = true;
		tile.isInteraction = true;
		break;
	case TYPE7:
		tile.isWall = true;
		tile.isInteraction = true;
		break;
	case TYPE8:
		tile.isWall = true;
		tile.isInteraction = true;
		break;
	/*case TYPE9:
		tile.isWall = true;
		tile.isInteraction = true;
		break;*/
	default:
		tile.isWall = false;
		tile.isInteraction = false;
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
			spawnCoordX = x;
			spawnCoordY = y;
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

unsigned short Level::getSpawnCoordX()
{
	return spawnCoordX;
}

unsigned short Level::getSpawnCoordY()
{
	return spawnCoordY;
}

vector<vector<Level::Tile>> Level::getMap()
{
	return map;
}
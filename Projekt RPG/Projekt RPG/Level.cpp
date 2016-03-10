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
	case TYPE1:
		tile.isWall = false;
		tile.isInteraction = false;
		break;
	case TYPE2:
		tile.isWall = false;
		tile.isInteraction = false;
		break;
	case TYPE3:
		tile.isWall = true;
		tile.isInteraction = false;
		break;
	case TYPE4:
		tile.isWall = true;
		tile.isInteraction = true;
		break;
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
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

void Level::clearMap()
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
		tile = new Tile(tileCode, false);
		break;
	case Tile::WALL1:
		tile = new Tile(tileCode, true);
		break;
	case Tile::FLOOR2:
		tile = new Tile(tileCode, false);
		break;
	case Tile::CHEST1:
		tile = new Tile(tileCode, true);
		break;
	case Tile::TRAP1:
		tile = new TrapFountain(tileCode, false, TrapFountain::TRAP);
		break;
	case Tile::FOUNTAIN1:
		tile = new TrapFountain(tileCode, false, TrapFountain::FOUNTAIN);
		break;
	case Tile::SAVE1:
		tile = new Save(tileCode, false);
		break;
	case Tile::LOOTCHEST1:
		tile = new LootChest(tileCode, true);
		break;
	case Tile::FLOOR3:
		tile = new Tile(tileCode, false);
		break;
	default:
		tile = new Tile(tileCode, true);
		break;
	}
	return tile;
}

bool Level::load(std::string filePath)
{
	std::fstream file;

	file.open(filePath);
	if (!file.is_open()) return false;
	levelPath = filePath;
	npcsCoordsAndTypes.clear();
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
		std::string name;
		unsigned short x, y;

		file >> name;
		file >> x >> y;
		if (name == "[SPAWN]")
		{
			playerSpawn.x = x;
			playerSpawn.y = y;
		}
		else if (name == "[ALIEN]")
		{
			CoordAndType tmp;
			tmp.npcCoords.x = x;
			tmp.npcCoords.y = y;
			tmp.enemyType = "[ALIEN]";
			npcsCoordsAndTypes.push_back(tmp);
		}
		else if (name == "[GUNNER]")
		{
			CoordAndType tmp;
			tmp.npcCoords.x = x;
			tmp.npcCoords.y = y;
			tmp.enemyType = "[GUNNER]";
			npcsCoordsAndTypes.push_back(tmp);
		}
		else if (name == "[NEUTRAL]")
		{
			CoordAndType tmp;
			tmp.npcCoords.x = x;
			tmp.npcCoords.y = y;
			tmp.enemyType = "[NEUTRAL]";
			npcsCoordsAndTypes.push_back(tmp);
		}
		else if (name == "[CANNON]")
		{
			CoordAndType tmp;
			tmp.npcCoords.x = x;
			tmp.npcCoords.y = y;
			tmp.enemyType = "[CANNON]";
			npcsCoordsAndTypes.push_back(tmp);
		}
		/* else if reszta typow przeciwnikow*/
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

std::vector<Level::CoordAndType> Level::getNpcCoordsAndTypes()
{
	return npcsCoordsAndTypes;
}

std::vector<std::vector<Tile*>> Level::getMap()
{
	return map;
}

void Level::spawnLootChest(sf::Vector2f chestPosition)
{
	int y = static_cast<int>(chestPosition.y / 64);
	int x = static_cast<int>(chestPosition.x / 64);
	Tile* tileUnder = map[y][x];
	
	Tile* newChest = new LootChest(Tile::LOOTCHEST1, true, tileUnder);
	map[y][x] = newChest;
}

void Level::deleteLootChest(sf::Vector2f chestPosition)
{
	int y = static_cast<int>(chestPosition.y / 64);
	int x = static_cast<int>(chestPosition.x / 64);
	LootChest* chest = dynamic_cast<LootChest*>(map[y][x]);
	Tile* tileUnder = chest->getTileUnder();
	delete chest;
	map[y][x] = tileUnder;
}

std::string Level::getLevelPath()
{
	return levelPath;
}

Tile::Coord Level::getSaveCoords(unsigned short _id)
{
	Save* temp;
	Tile::Coord coord;

	coord = playerSpawn;
	for (unsigned short y = 0; y < height; ++y)
	{
		for (unsigned short x = 0; x < width; ++x)
		{
			if (temp = dynamic_cast<Save*>(map[y][x]))
			{
				if (temp->getId() == _id)
				{
					coord.x = x;
					coord.y = y;
					return coord;
				}
			}
		}
	}
	return coord;
}
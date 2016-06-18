#include "Level.h"
#include <fstream>

Level::Level()
{
	/*wartosci domyslne*/
	height = 0;
	width = 0;
	playerSpawn.x = 0;
	playerSpawn.y = 0;
}

Level::~Level()
{
	/*wyczyszczenie mapy*/
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
	/*wyczyszczenie mapy*/
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
	/*stworzenie odpowiedniego kafla w zaleznosci od podanego kodu*/
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

	file.open(filePath); /*proba otwarcia pliku*/
	if (!file.is_open()) return false;
	levelPath = filePath;
	npcsCoordsAndTypes.clear(); /*wyczyszczenie kontenera*/
	file >> width >> height;
	if ((height == 0) || (width == 0))
	{
		file.close();
		return false;
	}
	/*przygotowanie odpowiedniej wielkosci kontenera*/
	map.resize(height);
	for (unsigned short i = 0; i < height; i++) map[i].resize(width);
	/*wypelnienie mapy zgodnie z plikiem zrodlowym*/
	for (unsigned short y = 0; y < height; y++)
	{
		for (unsigned short x = 0; x < width; x++)
		{
			short tileCode;

			file >> tileCode;
			map[y][x] = getTile(tileCode);
		}
	}
	while (!file.eof()) /*wczytanie specjalnych wlasnosci poziomu oraz przeciwnikow*/
	{
		std::string name;
		unsigned short x, y;

		file >> name;
		file >> x >> y;
		if (name == "[SPAWN]") /*wczytanie spawnu*/
		{
			playerSpawn.x = x;
			playerSpawn.y = y;
		}
		else if (name == "[ALIEN]") /*wczytanie przeciwnika typu Alien*/
		{
			CoordAndType tmp;
			tmp.npcCoords.x = x;
			tmp.npcCoords.y = y;
			tmp.enemyType = "[ALIEN]";
			npcsCoordsAndTypes.push_back(tmp);
		}
		else if (name == "[GUNNER]") /*wczytanie przeciwnika typu Gunner*/
		{
			CoordAndType tmp;
			tmp.npcCoords.x = x;
			tmp.npcCoords.y = y;
			tmp.enemyType = "[GUNNER]";
			npcsCoordsAndTypes.push_back(tmp);
		}
		else if (name == "[NEUTRAL]") /*wczytanie neutralnego npc*/
		{
			CoordAndType tmp;
			tmp.npcCoords.x = x;
			tmp.npcCoords.y = y;
			tmp.enemyType = "[NEUTRAL]";
			npcsCoordsAndTypes.push_back(tmp);
		}
		else if (name == "[CANNON]") /*wczytanie przeciwnika typu Cannon*/
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
	/*przeliczenie pozycji na koordynaty*/
	int y = static_cast<int>(chestPosition.y / 64);
	int x = static_cast<int>(chestPosition.x / 64);
	Tile* tileUnder = map[y][x]; /*zapisanie kafla ktory ma byc "pod skrzynka"*/
	
	Tile* newChest = new LootChest(Tile::LOOTCHEST1, true, tileUnder); /*stworzenie nowej skrzynki*/
	map[y][x] = newChest; /*akutalizacja mapy*/
}

void Level::deleteLootChest(sf::Vector2f chestPosition)
{
	/*przeliczenie pozycji na koordynaty*/
	int y = static_cast<int>(chestPosition.y / 64);
	int x = static_cast<int>(chestPosition.x / 64);
	LootChest* chest = dynamic_cast<LootChest*>(map[y][x]); /*przerzutowanie aby dostac sie do kafla ktory jest pod spodem*/
	Tile* tileUnder = chest->getTileUnder(); /*wydobycie kafla spod skrzynki*/
	delete chest; /*usuniecie skrzyni z pamieci*/
	map[y][x] = tileUnder; /*akutalizacja mapy*/
}

std::string Level::getLevelPath()
{
	return levelPath;
}

Tile::Coord Level::getSaveCoords(unsigned short _id)
{
	Save* temp;
	Tile::Coord coord;

	coord = playerSpawn; /*jesli zostalo podane bledne id, zostanie zwrocony spawn*/
	/*przeszukanie calej mapy*/
	for (unsigned short y = 0; y < height; ++y)
	{
		for (unsigned short x = 0; x < width; ++x)
		{
			if (temp = dynamic_cast<Save*>(map[y][x])) /*sprawdzenie czy badany kafel jest kaflem zapisu*/
			{
				if (temp->getId() == _id) /*jesli tak, nastepuje sprawdzenie czy zgadzaja sie id*/
				{
					/*jesli tak, zwracamy te koordynaty*/
					coord.x = x;
					coord.y = y;
					return coord;
				}
			}
		}
	}
	return coord;
}
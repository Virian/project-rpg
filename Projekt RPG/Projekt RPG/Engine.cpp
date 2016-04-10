#include "Engine.h"
#include <Windows.h>

void Engine::updateMap()
{
	// wyliczamy pozycjê minimalnych granic kamery
	Vector2f min = Vector2f(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2);

	// ustawienie kamery w poziomie
	float leftBorder = min.x / 64;
	float rightBorder = leftBorder + tileCountWidth - 3;

	// je¿eli jest za daleko na lewo
	if (min.x < 0)
	{
		float difference = abs(min.x);		// ró¿nica pomiêdzy 0, a lew¹ krawêdzi¹
		min.x += difference;
		view.move(difference, 0);

		leftBorder = min.x / 64;
	}
	else if (leftBorder > 0 && rightBorder - 1 < level.getWidth() - 1)
	{
		min.x -= 64;
		//view.move(-64, 0);

		leftBorder = min.x / 64;
	}

	else if (rightBorder - 1 >= level.getWidth() - 1)
	{
		// MAGIC!
		float difference = view.getCenter().x + view.getSize().x / 2 - (level.getWidth() - 1) * 64;

		difference = -difference - 64;
		min.x += difference;

		leftBorder = (min.x) / 64;

		view.setCenter((leftBorder + (tileCountWidth) / 2) * 64 + 64, view.getCenter().y);
	}
	else if (leftBorder == 0)
		view.move(-64 / 2, 0);



	// ustawienie kamery w pionie
	float upBorder = min.y / 64;
	float bottomBorder = upBorder + tileCountHeight - 3;

	// analogicznie: je¿eli jest za bardzo wysuniêta do góry
	if (min.y < 0)
	{
		float difference = abs(min.y);
		min.y += difference;
		view.move(0, difference);

		upBorder = min.y / 64;

	}
	else if (upBorder > 0 && bottomBorder - 1 + 1.0 / 4.0 < level.getHeight() - 1)
	{
		min.y -= 64;
		//view.move(0, -64);
		
		upBorder = min.y / 64;
	}
	else if (bottomBorder - 1 + 1.0 / 4.0 >= level.getHeight() - 1)
	{
		/*float difference = view.getCenter().y + view.getSize().y / 2 - (level.getHeight() - 1) * 64;

		difference = -difference - 64;
		min.y += difference;
		//min.y -= 64;

		upBorder = (min.y) / 64;

		view.setCenter(view.getCenter().x, (upBorder + (tileCountHeight) / 2) * 64 + 64);*/
		float difference = level.getHeight() * 64 - bottomBorder * 64;
		min.y += difference;
		view.move(0, difference - 64/4);
		min.y -= 64;
		upBorder = min.y / 64;

		//if (bottomBorder - 1 == level.getHeight() - 1)			// !!!
		//	view.move(0, -64 / 2);
	}
	else if (upBorder == 0)
		view.move(0, -64 / 2);

	// ustawienie kafli na scenie
	//for (int y = 0, h = (int)upBorder; y < tileCountHeight; y++)
	for (int y = 0, h = static_cast<int>(upBorder); y < tileCountHeight && h < level.getHeight(); y++)
	{																											// h - horizontal
		for (int x = 0, v = static_cast<int>(leftBorder); x < tileCountWidth && v < level.getWidth(); x++)		// v - vertical
		{
			tileSprites[y][x].setPosition(v * 64, h * 64);
			tileSprites[y][x].setTexture(tileTextures[level.getMap()[h][v]->getType()]);
			v++;
		}
		h++;
	}
}

void Engine::setMap(RenderWindow &window, string filePath)
{
	/*Reminder - przy zmianie mapy upewnic sie ze mapa zostaje wyczyszczona*/
	if (!level.load(filePath))
	{
		MessageBox(NULL, "Level file not found!", "ERROR", NULL);
		return;
	}
	for (size_t i = 0; i < npcs.size(); ++i)
	{
		delete npcs[i];
	}
	npcs.clear();
	player->setPosition(level.getPlayerSpawnCoords());
	view.setCenter(player->getPosition());
	for (size_t i = 0; i < level.getNpcCoords().size(); ++i)
	{
		Npc* tmp = new Enemy(level.getNpcCoords()[i]);
		npcs.push_back(tmp);
	}
	updateMap();
	window.setView(view);
}

Engine::Engine(RenderWindow &_window)
{
	view.setSize(1280, 720);
	view.setCenter(1280 / 2, 720 / 2);
	for (unsigned short i = 0; i < Tile::COUNT; i++) /*zalozenie ze wszystkie kafle sa w jednej linii*/
	{
		tileTextures[i].loadFromFile("placeholder.png", IntRect(i * 64, 512, 64, 64));
	}
	tileCountHeight = (_window.getSize().y / 64) + 3;
	tileCountWidth = (_window.getSize().x / 64) + 3;
	Sprite standard(tileTextures[0]);
	tileSprites.resize(tileCountHeight);
	for (unsigned short y = 0; y < tileCountHeight; y++)
	{
		tileSprites[y].resize(tileCountWidth, standard);
	}
	player = new Player(); /*Reminder - np. tu mozna zmieniac na Soldiera, Juggernauta, Sentinela*/
	setMap(_window, "test.level"); /*Reminder - do zmiany sciezka*/
	startEngine(_window);	
}

Engine::~Engine()
{
	delete player;
	for (size_t i = 0; i < npcs.size(); ++i)
	{
		delete npcs[i];
	}
}

void Engine::draw(RenderWindow &window, bool pause, bool equipment)
{
	window.clear();
	for (unsigned short y = 0; y < tileCountHeight; y++)
	{
		for (unsigned short x = 0; x < tileCountWidth; x++)
		{
			window.draw(tileSprites[y][x]);
		}
	}
	window.draw(*player);
	for (size_t i = 0; i < npcs.size(); i++)
	{
		window.draw(*npcs[i]);
	}
	gui.drawScreen(window, player);
	if (equipment)
	{
		gui.drawEquipment(window, player);
	}
	if (pause)
	{
		gui.drawPauseMenu(window);
	}
	window.display();
}

void Engine::startEngine(RenderWindow &window)
{
	bool quit = false;
	bool pause = false;
	bool equipment = false;
	
	updateMap();
	window.setView(view);
	draw(window, pause, equipment);
	while (!quit)
	{
		Event event;
		sf::Vector2f mouse(Mouse::getPosition(window));
		sf::Vector2f worldPos = window.mapPixelToCoords((Vector2i)mouse);

		if (!pause && !equipment)
		{
			while (window.pollEvent(event))
			{
				if ((event.type == Event::KeyReleased) && (event.key.code == Keyboard::Escape))
				{
					pause = true;
				}
				if ((event.type == Event::KeyReleased) && (event.key.code == Keyboard::I))
				{
					equipment = true;
				}
				if ((event.type == Event::MouseButtonPressed) && (event.mouseButton.button == Mouse::Right))
				{
					player->walk();
				}
				else if (event.type == Event::MouseButtonReleased)
				{
					if (event.mouseButton.button == Mouse::Right) player->stop();
				}
			}

			player->update(worldPos, &level);
			for (size_t i = 0; i < npcs.size(); ++i)
			{
				Enemy* enemy;
				if (enemy = dynamic_cast<Enemy*>(npcs[i]))
				{
					enemy->update(&level);
				}
				
			}
			if (player->getStatus() == Player::Status::WALK)
			{
				view.setCenter(player->getPosition());
				updateMap();
				window.setView(view);
			}
			if (player->getExp() >= player->getExpForNextLevel()) player->levelUp();
		}
		if (pause)
		{
			while (window.pollEvent(event))
			{
				if ((event.type == Event::KeyReleased) && (event.key.code == Keyboard::Escape))
				{
					pause = false;
				}
				if ((gui.getQuitButton().getGlobalBounds().contains(worldPos)) && (event.type == Event::MouseButtonReleased) && (event.key.code == Mouse::Left))
				{
					view.setCenter(1280 / 2, 720 / 2);
					window.setView(view);
					quit = true;
					pause = false;
				}
				if ((gui.getResumeButton().getGlobalBounds().contains(worldPos)) && (event.type == Event::MouseButtonReleased) && (event.key.code == Mouse::Left))
				{
					pause = false;
				}
			}
			if (gui.getResumeButton().getGlobalBounds().contains(worldPos)) gui.setResumeHighlight(1);
			else gui.setResumeHighlight(0);
			if (gui.getLoadButton().getGlobalBounds().contains(worldPos)) gui.setLoadHighlight(1);
			else gui.setLoadHighlight(0);
			if (gui.getQuitButton().getGlobalBounds().contains(worldPos)) gui.setQuitHighlight(1);
			else gui.setQuitHighlight(0);
		}
		if (equipment)
		{
			while (window.pollEvent(event))
			{
				if ((event.type == Event::KeyReleased) && ((event.key.code == Keyboard::I) || (event.key.code == Keyboard::Escape)))
				{
					equipment = false;
				}
			}
		}
		draw(window, pause, equipment);
	}
}
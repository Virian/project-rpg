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
			tileSprites[y][x].setTexture(tileTextures[level.getMap()[h][v].type]);
			v++;
		}
		h++;
	}
}

void Engine::setMap(RenderWindow &window, string filePath)
{
	if (!level.load(filePath))
	{
		MessageBox(NULL, "Level file not found!", "ERROR", NULL);
		return;
	}
	player->setPosition(level.getSpawnCoordX(), level.getSpawnCoordY());
	view.setCenter(player->getPosition());
	updateMap();
	window.setView(view);
}

Engine::Engine(RenderWindow &_window)
{
	view.setSize(1280, 720);
	view.setCenter(1280 / 2, 720 / 2);
	for (unsigned short i = 0; i < Level::COUNT; i++) /*zalozenie ze wszystkie kafle sa w jednej linii*/
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
	/*enemy = new Enemy();*/ /*Enemy comment*/
	setMap(_window, "test.level"); /*Reminder - do zmiany sciezka*/
	startEngine(_window);	
}

Engine::~Engine()
{
	delete player;
	/*delete enemy;*/ /*Enemy comment*/
}

void Engine::draw(RenderWindow &window)
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
	/*window.draw(*enemy);*/ /*Enemy comment*/
	gui.drawScreen(window, player->getHp(), player->getMaxHp());
	window.display();
}

void Engine::startEngine(RenderWindow &window)
{
	bool menu = false;
	/*float rot;
	int walkTime;
	int idleTime = rand() % 5000 + 10000;*/ /*Enemy comment*/
	updateMap();
	window.setView(view);
	draw(window);
	while (!menu)
	{
		Event event;
		sf::Vector2f mouse(Mouse::getPosition(window));
		sf::Vector2f worldPos = window.mapPixelToCoords((Vector2i)mouse);

		while (window.pollEvent(event))
		{
			if ((event.type == Event::KeyReleased) && (event.key.code == Keyboard::Escape))
			{
				view.setCenter(1280 / 2, 720 / 2);
				window.setView(view);
				menu = true;
			}
			/*if (event.type == Event::KeyPressed && event.key.code == Keyboard::W)
			{
				player.walk();
			}

			else if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::W)
					player.stop();
			}*/
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
		/*if (enemy->getStatus() == Enemy::Status::STOP)
		{
			rot = rand() % 360;
			walkTime = rand() % 500 + 1000;
		}
		else idleTime = rand() % 5000 + 7000;
		enemy->update(&level, rot, idleTime, walkTime);*/ /*Enemy comment*/
		if (player->getStatus() == Player::Status::WALK)
		{
			view.setCenter(player->getPosition());
			updateMap();
			window.setView(view);
		}		
		draw(window);
	}
}
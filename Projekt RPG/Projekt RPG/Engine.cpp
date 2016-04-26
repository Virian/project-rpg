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
	player = new Soldier(); /*Reminder - np. tu mozna zmieniac na Soldiera, Juggernauta, Sentinela*/
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

void Engine::fight(unsigned enemyIndex, Engine::Attacker attacker)
{
	unsigned hitChance, dodgeChance;
	Enemy* enemy;
	unsigned damage;
	Gui::TextDamage* damageInfo = new Gui::TextDamage();

	enemy = dynamic_cast<Enemy*>(npcs[enemyIndex]);

	switch (attacker)
	{
	case PLAYER:
		if (player->getEquipment().getActiveWeapon()->isRanged())
		{
			if (player->getAttackInterval().getElapsedTime().asSeconds() < 0.5) return;
			hitChance = rand() % 20 + 1 + player->getAgi() + 3;
		}
		else
		{
			if (player->getAttackInterval().getElapsedTime().asSeconds() < 0.7) return;
			hitChance = rand() % 20 + 1 + player->getStr() + 3;
		}

		dodgeChance = 10 + enemy->getAgi() + enemy->getArmorValue();

		if (hitChance > dodgeChance)
		{
			if (player->getEquipment().getActiveWeapon()->isRanged())
				damage = player->getEquipment().getActiveWeapon()->getAttackValue();
			else
				damage = player->getEquipment().getActiveWeapon()->getAttackValue() + player->getStr() / 15;

			enemy->takeDamage(damage);
			damageInfo->text.setString(std::to_string(damage));
			damageInfo->text.setPosition(npcs[enemyIndex]->getPosition() - Vector2f(0.0, npcs[enemyIndex]->getBoundingBox().height / 2 + 20.0));
			gui.pushDamageInfo(damageInfo);
		}
		else
		{
			damageInfo->text.setString("MISS");
			damageInfo->text.setPosition(npcs[enemyIndex]->getPosition() - Vector2f(0.0, npcs[enemyIndex]->getBoundingBox().height / 2 + 20.0));
			gui.pushDamageInfo(damageInfo);
		}
		player->restartAttackInterval();
		break;
	case NPC:
		if (enemy->isRanged())
		{
			if (enemy->getAttackInterval().getElapsedTime().asSeconds() < 0.5) return;
			hitChance = rand() % 20 + 1 + enemy->getAgi() + 3;
		}
		else
		{
			if (enemy->getAttackInterval().getElapsedTime().asSeconds() < 0.7) return;
			hitChance = rand() % 20 + 1 + enemy->getStr() + 3;
		}

		dodgeChance = 10 + player->getAgi() + player->getEquipment().getActiveArmor()->getArmorValue();

		if (hitChance > dodgeChance)
		{
			unsigned damage;

			if (enemy->isRanged())
				damage = enemy->getAttackValue();
			else
				damage = enemy->getAttackValue() + enemy->getStr() / 15;

			player->takeDamage(damage);
		}
		enemy->restartAttackInterval();
		break;
	}
	
}

void Engine::draw(RenderWindow &window, bool pause, bool equipment, short position)
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
		gui.drawEquipment(window, player, position);
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
	bool attacked = false;
	short position = -1;

	updateMap();
	window.setView(view);
	draw(window, pause, equipment, position);
	while (!quit)
	{
		Event event;
		Vector2f mouse(Mouse::getPosition(window));
		Vector2f worldPos = window.mapPixelToCoords((Vector2i)mouse);

		if (!pause && !equipment)
		{
			while (window.pollEvent(event))
			{
				bool attacked = false;
				if ((event.type == Event::KeyReleased) && (event.key.code == Keyboard::Escape))
				{
					pause = true;
				}
				if ((event.type == Event::KeyReleased) && (event.key.code == Keyboard::I))
				{
					equipment = true;
				}
				for (size_t i = 0; i < npcs.size(); ++i)
				{
					if ((player->getStatus() == Player::STOP) && (npcs[i]->getBoundingBox().contains(worldPos)) && (Mouse::isButtonPressed(Mouse::Right)))
					{						
						Vertex line[2];
						float distance;
						float sinus;
						float cosinus;
						line[0].position = player->getPosition();
						line[1].position = npcs[i]->getPosition();
						attacked = true;
						player->attack();
						do
						{
							if (level.getMap()[line[0].position.y / 64][line[0].position.x / 64]->isWall())
							{
								attacked = false;
								player->stop();
								break;
							}
							distance = sqrt(pow(line[0].position.x - line[1].position.x, 2) + pow(line[0].position.y - line[1].position.y, 2));
							sinus = (line[0].position.x - line[1].position.x) / distance;
							cosinus = (line[0].position.y - line[1].position.y) / distance;
							distance -= 1.0f;
							line[0].position.x = sinus * distance + line[1].position.x;
							line[0].position.y = cosinus * distance + line[1].position.y;
						} while (distance > 1);
						
					}
				}
				if ((!attacked) && (event.type == Event::MouseButtonPressed) && (event.mouseButton.button == Mouse::Right))
				{
					player->walk();
				}
				else if ((!attacked) && (event.type == Event::MouseButtonReleased))
				{
					if (event.mouseButton.button == Mouse::Right) player->stop();
				}
				if ((event.type == Event::KeyReleased) && (event.key.code == Keyboard::Space))
				{
					player->usePotion();
				}
			}

			player->update(worldPos, &level);
			for (size_t i = 0; i < npcs.size(); ++i)
			{
				Enemy* enemy;
				if ((player->getStatus() == Player::ATTACK) && (npcs[i]->getBoundingBox().contains(worldPos)) && (Mouse::isButtonPressed(Mouse::Right)))				
				{
					fight(i, PLAYER);
				}
				if (enemy = dynamic_cast<Enemy*>(npcs[i]))
				{
					if (enemy->isAlive())
						enemy->update(&level);
					else
					{
						player->increaseExperience(enemy->getExperienceGiven());
						delete npcs[i];
						npcs.erase(npcs.begin() + i);
						--i;
					}
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
					position = -1;
				}
				for (short i = 0; i < 2; ++i)
				{
					for (short j = 0; j < 5; ++j)
					{
						Vector2f slotPosition = window.mapPixelToCoords(Vector2i(140 + j * 128, 418 + i * 128));
						if ((FloatRect(slotPosition, Vector2f(128, 128)).contains(worldPos)) && (event.type == Event::MouseButtonReleased) && (event.key.code == Mouse::Left))
						{
							position = 5 * i + j;
						}
						if ((FloatRect(slotPosition, Vector2f(128, 128)).contains(worldPos)) && (Keyboard::isKeyPressed(Keyboard::LShift)) && (event.type == Event::MouseButtonReleased) && (event.key.code == Mouse::Left))
						{
							player->deleteItem(5 * i + j);
							position = -1;
						}
						if ((FloatRect(slotPosition, Vector2f(128, 128)).contains(worldPos)) && (Keyboard::isKeyPressed(Keyboard::LControl)) && (event.type == Event::MouseButtonReleased) && (event.key.code == Mouse::Left))
						{
							player->swapActiveItem(5 * i + j);
							position = -1;
						}
					}
				}
				if ((FloatRect(946, 340, 128, 128).contains(mouse)) && (event.type == Event::MouseButtonReleased) && (event.key.code == Mouse::Left))
				{
					position = -2;
				}
				if ((FloatRect(946, 520, 128, 128).contains(mouse)) && (event.type == Event::MouseButtonReleased) && (event.key.code == Mouse::Left))
				{
					position = -3;
				}
				if ((FloatRect(946, 340, 128, 128).contains(mouse)) && (Keyboard::isKeyPressed(Keyboard::LShift)) && (event.type == Event::MouseButtonReleased) && (event.key.code == Mouse::Left))
				{
					player->deleteItem(-1);
					position = -1;
				}
				if ((FloatRect(946, 520, 128, 128).contains(mouse)) && (Keyboard::isKeyPressed(Keyboard::LShift)) && (event.type == Event::MouseButtonReleased) && (event.key.code == Mouse::Left))
				{
					player->deleteItem(-2);
					position = -1;
				}
				if ((FloatRect(946, 340, 128, 128).contains(mouse)) && (Keyboard::isKeyPressed(Keyboard::LControl)) && (event.type == Event::MouseButtonReleased) && (event.key.code == Mouse::Left))
				{
					player->swapActiveItem(-1);
					position = -1;
				}
				if ((FloatRect(946, 520, 128, 128).contains(mouse)) && (Keyboard::isKeyPressed(Keyboard::LControl)) && (event.type == Event::MouseButtonReleased) && (event.key.code == Mouse::Left))
				{
					player->swapActiveItem(-2);
					position = -1;
				}
			}			
		}
		draw(window, pause, equipment, position);
	}
}
#include "Engine.h"
#include <Windows.h>

void Engine::updateMap()
{
	/*rysowane maja byc tylko te kafle, ktore sa widoczne w granicach kamery*/
	/*wyliczamy pozycjê minimalnych granic kamery*/
	sf::Vector2f min = sf::Vector2f(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2);

	/*ustawienie kamery w poziomie*/
	float leftBorder = min.x / 64;
	float rightBorder = leftBorder + tileCountWidth - 3;

	/*gdy jest za daleko na lewo*/
	if (min.x < 0)
	{
		float difference = abs(min.x); /*roznica pomiêdzy 0 a lewa krawedzia*/
		min.x += difference;
		view.move(difference, 0);

		leftBorder = min.x / 64;
	}
	else if (leftBorder > 0 && rightBorder - 1 < level.getWidth() - 1)
	{
		min.x -= 64;

		leftBorder = min.x / 64;
	}

	else if (rightBorder - 1 >= level.getWidth() - 1)
	{
		float difference = view.getCenter().x + view.getSize().x / 2 - (level.getWidth() - 1) * 64;

		difference = -difference - 64;
		min.x += difference;

		leftBorder = (min.x) / 64;

		view.setCenter((leftBorder + (tileCountWidth) / 2) * 64 + 64, view.getCenter().y);
	}
	else if (leftBorder == 0)
		view.move(-64 / 2, 0);



	/*ustawienie kamery w pionie*/
	float upBorder = min.y / 64;
	float bottomBorder = upBorder + tileCountHeight - 3;

	/*analogicznie, gdy jest za bardzo wysunieta do gory*/
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
		
		upBorder = min.y / 64;
	}
	else if (bottomBorder - 1 + 1.0 / 4.0 >= level.getHeight() - 1)
	{
		float difference = level.getHeight() * 64 - bottomBorder * 64;
		min.y += difference;
		view.move(0, difference - 64/4);
		min.y -= 64;
		upBorder = min.y / 64;
	}
	else if (upBorder == 0)
		view.move(0, -64 / 2);

	/*ustawienie kafli ktore maja zostac narysowane*/
	for (int y = 0, h = static_cast<int>(upBorder); y < tileCountHeight && h < level.getHeight(); y++)
	{
		for (int x = 0, v = static_cast<int>(leftBorder); x < tileCountWidth && v < level.getWidth(); x++)
		{
			tileSprites[y][x].setPosition(v * 64.f, h * 64.f);
			tileSprites[y][x].setTexture(tileTextures[level.getMap()[h][v]->getType()]);
			v++;
		}
		h++;
	}
}

void Engine::setMap(sf::RenderWindow &window, std::string filePath, unsigned short _id)
{
	/*wyczyszcznie mapy i wszystkich kontenerow z nia zwiaznych*/
	level.clearMap();
	for (size_t i = 0; i < npcs.size(); ++i)
	{
		delete npcs[i];
	}
	npcs.clear();
	for (size_t i = 0; i < gui.getHpInfoSize(); ++i)
	{
		gui.eraseHpInfo(i);
		--i;
	}
	gui.clearHpInfo();
	level.load(filePath); /*wczytanie poziomu*/
	/*ustawienie gracza w zaelznosci czy wczytujemy gre czy nie*/
	if (_id == 0) player->setPosition(level.getPlayerSpawnCoords());
	else player->setPosition(level.getSaveCoords(_id));
	view.setCenter(player->getPosition()); /*ustawienie kamery na gracza*/
	/*wczytanie wszystkich npc*/
	for (size_t i = 0; i < level.getNpcCoordsAndTypes().size(); ++i)
	{
		Npc* tmp;
		if (level.getNpcCoordsAndTypes()[i].enemyType == "[GUNNER]") tmp = new Gunner(level.getNpcCoordsAndTypes()[i].npcCoords);
		else if (level.getNpcCoordsAndTypes()[i].enemyType == "[ALIEN]") tmp = new Alien(level.getNpcCoordsAndTypes()[i].npcCoords);
		else if (level.getNpcCoordsAndTypes()[i].enemyType == "[NEUTRAL]") tmp = new Neutral(level.getNpcCoordsAndTypes()[i].npcCoords);
		else if (level.getNpcCoordsAndTypes()[i].enemyType == "[CANNON]") tmp = new Cannon(level.getNpcCoordsAndTypes()[i].npcCoords);
		/*else if inne typy przeciwnikow*/
		npcs.push_back(tmp);
		Enemy* temp;
		/*jesli nowy npc jest przeciwnikiem, dodany tez bedzie skojarzony z nim pasek hp*/
		if (temp = dynamic_cast<Enemy*>(tmp))
		{
			Gui::HpBar* hpInfo = new Gui::HpBar();
			hpInfo->characterPosition = temp->getPosition();
			hpInfo->currentHp.setSize(sf::Vector2f((temp->getHp() / temp->getMaxHp()) * 64.f,6));
			hpInfo->missingHp.setSize(sf::Vector2f(64.f - (temp->getHp() / temp->getMaxHp()) * 64.f,6));
			gui.pushHpInfo(hpInfo);
		}
	}
	/*wczytanie nowej muzyki*/
	audio.stopBackgroundMusic();
	if (filePath == "levels/level1.level") audio.setBackgroundMusic("music/background1.ogg");
	else if (filePath == "levels/level2.level") audio.setBackgroundMusic("music/background2.ogg");
	/*else if inne levele*/
	audio.playBackgroundMusic();
	updateMap();
	window.setView(view);
}

Engine::Engine(sf::RenderWindow &_window, sf::Sprite& cursor, std::string characterName, int classCode)
{
	/*ustawienie widoku*/
	view.setSize(1280, 720);
	view.setCenter(1280 / 2, 720 / 2);
	for (unsigned short i = 0; i < Tile::COUNT; i++) /*zalozenie ze wszystkie kafle sa w jednej linii*/
	{
		tileTextures[i].loadFromFile("images/tilesheet.png", sf::IntRect(i * 64, 512, 64, 64)); /*wczytanie wszystkich kafli do tablicy*/
	}
	tileCountHeight = (_window.getSize().y / 64) + 3; /*ilosc rysowanych kafli w pionie*/
	tileCountWidth = (_window.getSize().x / 64) + 3; /*ilosc rysowanych kafli w poziomie*/
	sf::Sprite standard(tileTextures[0]); /*sprite kafla domyslnego*/
	/*ustawienie rozmiaru kontenera kafli do rysowania i wypelnienie go kaflem domyslnym*/
	tileSprites.resize(tileCountHeight);
	for (unsigned short y = 0; y < tileCountHeight; y++)
	{
		tileSprites[y].resize(tileCountWidth, standard);
	}
	/*utworzenie gracza odpowiedniej klasy*/
	switch (classCode)
	{
	case 1:
		player = new Soldier(characterName);
		break;
	case 2:
		player = new Sentinel(characterName);
		break;
	case 3:
		player = new Juggernaut(characterName);
		break;
	}
	setMap(_window, "levels/level1.level", 0); /*ustawienie poziomu startowego*/
	gui.setSkillPictures(player->getClassName()); /*ustawienie odpowiednich obrazkow umiejetnosci*/
	startEngine(_window, cursor); /*uruchomienie silnika*/
}

Engine::Engine(sf::RenderWindow &_window, sf::Sprite& cursor, std::fstream &file)
{
	/*ustawienie widoku*/
	view.setSize(1280, 720);
	view.setCenter(1280 / 2, 720 / 2);
	for (unsigned short i = 0; i < Tile::COUNT; i++) /*zalozenie ze wszystkie kafle sa w jednej linii*/
	{
		tileTextures[i].loadFromFile("images/tilesheet.png", sf::IntRect(i * 64, 512, 64, 64)); /*wczytanie wszystkich kafli do tablicy*/
	}
	tileCountHeight = (_window.getSize().y / 64) + 3; /*ilosc rysowanych kafli w pionie*/
	tileCountWidth = (_window.getSize().x / 64) + 3;/*ilosc rysowanych kafli w poziomie*/
	sf::Sprite standard(tileTextures[0]); /*sprite kafla domyslnego*/
	/*ustawienie rozmiaru kontenera kafli do rysowania i wypelnienie go kaflem domyslnym*/
	tileSprites.resize(tileCountHeight);
	for (unsigned short y = 0; y < tileCountHeight; y++)
	{
		tileSprites[y].resize(tileCountWidth, standard);
	}
	/*wczytanie wszystkiego z pliku*/
	std::string characterName;
	std::string className;
	std::string levelPath;
	unsigned short saveId;
	file >> className;
	getline(file, characterName);
	characterName.erase(0, 1);
	file >> levelPath;
	file >> saveId;
	/*utworzenie gracza odpowiedniej klasy*/
	if (className == "Soldier") player = new Soldier(characterName, file);
	else if (className == "Sentinel") player = new Sentinel(characterName, file);
	else player = new Juggernaut(characterName, file);
	file.close(); /*zamkniecie pliku po wczytaniu wszystkiego*/
	setMap(_window, levelPath, saveId); /*ustawienie mapy*/
	gui.setSkillPictures(player->getClassName()); /*ustawienie odpowiednich obrazkow umiejetnosci*/
	startEngine(_window, cursor); /*uruchomienie silnika*/
}

Engine::~Engine()
{
	/*pozbycie sie dynamicznie zaalokowanej pamieci*/
	delete player;
	for (size_t i = 0; i < npcs.size(); ++i)
	{
		delete npcs[i];
	}
	npcs.clear();
}

void Engine::fight(size_t enemyIndex, Engine::Attacker attacker)
{
	unsigned hitChance, dodgeChance;
	Enemy* enemy;
	unsigned damage;
	Weapon* activeWeapon = player->getEquipment()->getActiveWeapon();
	Armor* activeArmor = player->getEquipment()->getActiveArmor();
	Gui::TextDamage* damageInfo; /*nowa informacje o obrazeniach*/

	enemy = dynamic_cast<Enemy*>(npcs[enemyIndex]);

	switch (attacker)
	{
	case PLAYER: /*przypadek gdy gracz atakuje npc*/
		if (activeWeapon && activeWeapon->isRanged()) /*atak z broni dystansowej*/
		{
			double interval;
			if (player->isActiveSkill1() && player->getClassName() == "Soldier") interval = 0.3; /*Soldier moze wtedy atakowac szybciej*/
			else interval = 0.5;
			if (player->getAttackInterval().getElapsedTime().asSeconds() < interval) return;
			hitChance = rand() % 20 + 1 + player->getAgi() + 3;
		}
		else /*atak z broni melee*/
		{
			if (player->getAttackInterval().getElapsedTime().asSeconds() < 0.7) return;
			hitChance = rand() % 20 + 1 + player->getStr() + 3;
		}
		if (player->isActiveSkill3() && player->getClassName() == "Sentinel") hitChance = static_cast<unsigned>(hitChance * 2.5); /*umiejetnosc zwiekszajaca szanse na trafienie*/

		dodgeChance = 10 + enemy->getAgi() + enemy->getArmorValue();

		if (hitChance > dodgeChance) /*jesli trafienie sie powiodlo nastepuje liczenie obrazen*/
		{
			if (activeWeapon && activeWeapon->isRanged())
				damage = activeWeapon->getAttackValue();
			else
			{
				if (!activeWeapon) damage = player->getStr() / 15 + 1;
				else damage = activeWeapon->getAttackValue() + player->getStr() / 15;
				if (player->isActiveSkill2() && player->getClassName() == "Juggernaut") /*umiejetnosc zwiekszajaca obrazenia*/
				{
					damage += damage / 2;
					player->clearEffectSkill2();
				}
			}

			enemy->takeDamage(damage); /*zadanie obrazen*/
			/*dorzucenie informacji o obrazeniach do wyswietlenia*/
			damageInfo = new Gui::TextDamage();
			damageInfo->text.setString(std::to_string(damage));
			damageInfo->text.setColor(sf::Color::Red);
			damageInfo->text.setPosition(npcs[enemyIndex]->getPosition() - sf::Vector2f(0.0, npcs[enemyIndex]->getBoundingBox().height / 2 + 20.0f));
			gui.pushDamageInfo(damageInfo);
		}
		else
		{
			/*jesli nie trafiono - wyswietlenie o tym informacji*/
			damageInfo = new Gui::TextDamage();
			damageInfo->text.setString("MISS");
			damageInfo->text.setColor(sf::Color::Red);
			damageInfo->text.setPosition(npcs[enemyIndex]->getPosition() - sf::Vector2f(0.0, npcs[enemyIndex]->getBoundingBox().height / 2 + 20.0f));
			gui.pushDamageInfo(damageInfo);
		}
		player->restartAttackInterval(); /*reset zegara liczacego czas od ostatniego ataku*/
		/*odtworzenie odpowiedniego dzwieku*/
		if (activeWeapon && activeWeapon->isRanged()) audio.playGunSound();
		else audio.playMeleeSound();
		break;
	case NPC: /*przypadek gdy npc atakuje gracza*/
		if (enemy->isRanged()) /*atak dystansowy*/
		{
			if (enemy->getAttackInterval().getElapsedTime().asSeconds() < 0.5) return;
			hitChance = rand() % 20 + 1 + enemy->getAgi() + 3;
		}
		else /*atak melee*/
		{
			if (enemy->getAttackInterval().getElapsedTime().asSeconds() < 0.7) return;
			hitChance = rand() % 20 + 1 + enemy->getStr() + 3;
		}

		if (!activeArmor) dodgeChance = 10 + player->getAgi();
		else dodgeChance = 10 + player->getAgi() + activeArmor->getArmorValue();
		if (player->isActiveSkill1() && player->getClassName() == "Juggernaut") dodgeChance += 100000; /*zapewnienie nietykalnosci*/

		if (hitChance > dodgeChance) /*trafiony*/
		{
			if (enemy->isRanged())
				damage = enemy->getAttackValue();
			else
				damage = enemy->getAttackValue() + enemy->getStr() / 15;

			player->takeDamage(damage); /*zadanie obrazen*/
			/*nie dodajemy informacji o obrazeniach do kontenera, zmiana hp gracza jest obslugiwana w innym miejscu*/
		}
		else /*nietrafiony*/
		{
			damageInfo = new Gui::TextDamage();
			damageInfo->text.setString("MISS");
			damageInfo->text.setColor(sf::Color::Red);
			damageInfo->text.setPosition(player->getPosition() - sf::Vector2f(0.0, player->getBoundingBox().height / 2 + 20.0f));
			gui.pushDamageInfo(damageInfo);
		}
		enemy->restartAttackInterval(); /*reset zegara liczacego czas od ostatniego ataku*/
		/*odtworzenie odpowiedniego dzwieku*/
		if (enemy->isRanged()) audio.playGunSound();
		else audio.playMeleeSound();
		break;
	}
	
}

void Engine::draw(sf::RenderWindow &window, sf::Sprite& cursor, bool pause, bool equipment, bool dead, bool levelMenu, short position)
{
	window.clear();
	gui.updateSkillCooldowns(window, player->getRatioSkill1(), player->getRatioSkill2(), player->getRatioSkill3()); /*aktualizacja obrazkow umiejetnosci*/
	/*narysowanie mapy*/
	for (unsigned short y = 0; y < tileCountHeight; y++)
	{
		for (unsigned short x = 0; x < tileCountWidth; x++)
		{
			window.draw(tileSprites[y][x]);
		}
	}	
	/*narysowanie wszystkich npc*/
	for (size_t i = 0; i < npcs.size(); i++)
	{
		window.draw(*npcs[i]);
	}
	window.draw(*player); /*narysowanie gracza*/
	gui.drawScreen(window, player); /*narysowanie HUDa*/
	if (equipment)
	{
		gui.drawEquipment(window, player, position); /*rysowanie ekwipunku*/
	}
	else if (pause)
	{
		gui.drawPauseMenu(window); /*rysowanie menu pauzy*/
	}
	else if (dead)
	{
		gui.drawDeathScreen(window); /*rysowanie ekranu smierci*/
	}
	else if (levelMenu)
	{
		gui.drawLevelMenu(window); /*rysowanie menu wyboru poziomu*/
	}
	/*sprawdzenie czy kursor jest ponad ktoryms z przeciwnikow*/
	if (checkCursor()) cursor.setTextureRect(sf::IntRect(26, 0, 26, 32));
	else cursor.setTextureRect(sf::IntRect(0, 0, 26, 32));
	window.draw(cursor); /*rysowanie kursora*/
	window.display();
}

void Engine::saveGame(unsigned short id)
{
	std::fstream file;

	file.open("save/SavedGame.sav", std::fstream::in | std::fstream::out | std::fstream::trunc); /*otworzenie pliku*/
	file << player->getClassName() << " " << player->getName() << std::endl; /*wypisanie klasy oraz imienia postaci*/
	file << level.getLevelPath() << std::endl; /*wypisanie sciezki poziomu na ktorym sie znajduje*/
	file << id << std::endl; /*wypisanie id kafla zapisu na ktorym stoi gracz*/
	file << player->getLvl() << " " << player->getExp() << " " << player->getExpForNextLevel() << std::endl; /*wypisanie poziomu, doswiadczenia, doswiadczenia potrzebnego na nastepny poziom*/
	file << player->getHp() << " " << player->getMaxHp() << std::endl; /*wypisanie obecnego i maksymalnego hp*/
	file << player->getStr() << " " << player->getInt() << " " << player->getAgi() << " " << player->getPointsToSpend() << std::endl; /*wypisanie statystyk i punktow do wydania*/
	file << player->getEquipment()->getPotionCount() << std::endl; /*wypisanie ilosci mikstur*/
	/*wypisanie informacji o aktywnej broni*/
	file << "[ACTIVEWEAPON] ";
	if (player->getEquipment()->getActiveWeapon() == NULL) file << "[NULL]" << std::endl;
	else
	{
		if (player->getEquipment()->getActiveWeapon()->isRanged()) file << "[RANGED] ";
		else file << "[MELEE] ";
		file << player->getEquipment()->getActiveWeapon()->getAttackValue() << " " << player->getEquipment()->getActiveWeapon()->getTextureRect().left / 128 << " " << player->getEquipment()->getActiveWeapon()->getName() << std::endl;
	}
	/*wypisanie informacji o aktywnej zbroi*/
	file << "[ACTIVEARMOR] ";
	if (player->getEquipment()->getActiveArmor() == NULL) file << "[NULL]";
	else
	{
		file << player->getEquipment()->getActiveArmor()->getArmorValue() << " " << player->getEquipment()->getActiveArmor()->getTextureRect().left / 128 << " " << player->getEquipment()->getActiveArmor()->getName();
	}
	/*wypisanie informacji o reszcie przedmiotow w ekwipunku*/
	for (size_t i = 0; i < player->getEquipment()->getBackpack().size(); ++i)
	{
		Armor* tempArmor;
		Weapon* tempWeapon;

		if (tempArmor = dynamic_cast<Armor*>(player->getEquipment()->getBackpack()[i]))
		{
			file << std::endl << "[ARMOR] " << tempArmor->getArmorValue() << " " << tempArmor->getTextureRect().left / 128 << " " << tempArmor->getName();
		}
		else if (tempWeapon = dynamic_cast<Weapon*>(player->getEquipment()->getBackpack()[i]))
		{
			if (tempWeapon->isRanged()) file << std::endl << "[WEAPON] [RANGED] " << tempWeapon->getAttackValue() << " " << tempWeapon->getTextureRect().left / 128 << " " << tempWeapon->getName();
			else file << std::endl << "[WEAPON] [MELEE] " << tempWeapon->getAttackValue() << " " << tempWeapon->getTextureRect().left / 128 << " " << tempWeapon->getName();
		}
	}
	file.close(); /*zamkniecie pliku*/
}

bool Engine::checkCursor()
{
	Enemy* enemy;
	for (size_t i = 0; i < npcs.size(); ++i)
	{
		if (enemy = dynamic_cast<Enemy*>(npcs[i]))
		{
			if (enemy->hasCursor()) return true; /*wystarczy ze kursor jest ponad ktorym kolwiek z przeciwnikow*/
		}
	}
	return false;
}

void Engine::startEngine(sf::RenderWindow &window, sf::Sprite& cursor)
{
	bool quit = false;
	bool pause = false;
	bool equipment = false;
	bool dead = false;
	bool levelMenu = false;
	bool attacked = false;
	short position = -1;

	updateMap();
	window.setView(view);
	draw(window, cursor, pause, equipment, dead, levelMenu, position); /*rysowanie poczatkowe*/
	while (!quit) /*petla gry*/
	{
		sf::Event event;
		sf::Vector2f mouse(sf::Mouse::getPosition(window));
		sf::Vector2f worldPos = window.mapPixelToCoords((sf::Vector2i)mouse);

		cursor.setPosition(worldPos); /*ustawienie kursora*/

		if (!pause && !equipment && !dead && !levelMenu)
		{
			short tempHp = player->getHp(); /*pobranie obecnego hp gracza przed wszystkimi zdarzeniami*/
			if (tempHp > 0) /*jesli gracz jest zywy*/
			{
				while (window.pollEvent(event)) /*petla zbierania eventow*/
				{
					bool attacked = false;
					if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::L)) /*wcisniecie L, proba otworzenia menu zmiany poziomu*/
					{
						Save* temp;
						if (temp = dynamic_cast<Save*>(level.getMap()[static_cast<unsigned __int64>(player->getPosition().y / 64)][static_cast<unsigned __int64>(player->getPosition().x / 64)])) /*jesli gracz stoi na kaflu zapisu*/
						{
							levelMenu = true; /*otwarcie menu zapisu*/
							player->pauseTimers(); /*zatrzymanie timerow gracza*/
						}
						else MessageBox(NULL, "You can only change your level while standing on save tile!", "UNABLE TO CHANGE LEVEL", NULL); /*wyswietlenie bledu*/					
					}
					if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Escape)) /*wcisniecie ESC, otworzenie menu pauzy*/
					{
						pause = true; /*otwarcie menu pauzy*/
						player->pauseTimers(); /*zatrzymanie timerow gracza*/
					}
					if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::I)) /*wcisniecie I, proba otwarcia ekwipunku*/
					{
						equipment = true; /*otwarcie ekwipunku*/
						player->pauseTimers(); /*zatrzymanie timerow gracza*/
					}
					if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Num1)) /*wcisniecie 1, uzycie pierwszej umiejetnosci*/
					{
						player->useSkill1();
					}
					if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Num2)) /*wcisniecie 2, uzycie drugiej umiejetnosci*/
					{
						player->useSkill2();
					}
					if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Num3)) /*wcisniecie 3, uzycie trzeciej umiejetnosci*/
					{
						player->useSkill3();
					}
					for (size_t i = 0; i < npcs.size(); ++i) /*sprawdzenie calego kontenera npcow*/
					{
						Enemy* enemy;
						if ((enemy = dynamic_cast<Enemy*>(npcs[i])) && (player->getStatus() == Player::STOP)
							&& (npcs[i]->getBoundingBox().contains(worldPos))
							&& (sf::Mouse::isButtonPressed(sf::Mouse::Right)))
							/*gracz moze zaatakowac jesli stoi w miejscu, ma wcisniety PPM i ma kursor nad przeciwnikiem*/
						{
							sf::Vertex line[2];
							float distance;
							float sinus;
							float cosinus;
							Weapon* activeWeapon = player->getEquipment()->getActiveWeapon();
							/*wyznaczenie lini od gracza do przeciwnika*/
							line[0].position = player->getPosition();
							line[1].position = npcs[i]->getPosition();
							/*proba zaatakowania*/
							attacked = true;
							player->attack();
							/*petla sprawdzajaca czy pomiedzy graczem a przeciwnikiem jest sciana*/
							do
							{
								/*sprawdzenie czy na obecnie rozpatrywanej pozycji jest sciana*/
								if (level.getMap()[static_cast<unsigned __int64>(line[0].position.y / 64)][static_cast<unsigned __int64>(line[0].position.x / 64)]->isWall())
								{
									attacked = false;
									player->stop();
									break;
								}
								/*wyliczenie obecnej dlugosci linii (na poczatku jest ona odlegloscia pomiedzy graczem a przeciwnikiem)*/
								distance = sqrt(pow(line[0].position.x - line[1].position.x, 2) + pow(line[0].position.y - line[1].position.y, 2));
								/*jesli gracz nie posiada broni dystansowej, a odleglosc pomiedzy nim a przeciwnikiem jest zbyt duza, nie wykona on ataku*/
								if ((!activeWeapon || !activeWeapon->isRanged()) && (distance > 70))
								{
									attacked = false;
									player->stop();
									break;
								}
								/*skrocenie linii poprzez przesuniecie jednego konca blizej drugiego*/
								sinus = (line[0].position.x - line[1].position.x) / distance;
								cosinus = (line[0].position.y - line[1].position.y) / distance;
								distance -= 2.0f;
								line[0].position.x = sinus * distance + line[1].position.x;
								line[0].position.y = cosinus * distance + line[1].position.y;
							} while (distance > 2);
						}
					}
					if ((!attacked) && (event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Right)) /*gdy gracz nie zaatakowal i trzyma PPM - chodzi*/
					{
						player->walk();
					}
					else if ((!attacked) && (event.type == sf::Event::MouseButtonReleased)) /*jesli nie zaatakowal i puscil PPM - zatrzymuje sie*/
					{
						if (event.mouseButton.button == sf::Mouse::Right) player->stop();
					}
					if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Space)) /*wcisniecie spacji, uzycie mikstury zycia*/
					{
						player->usePotion();
					}
				}

				if (player->update(worldPos, &level) == 1) updateMap(); /*wykoanie update'u gracza oraz update'u mapy i kamery gdy gracz mial kolizje ze skrzynka*/
				for (size_t i = 0; i < npcs.size(); ++i) /*sprawdzenie calego kontenera npcow*/
				{
					Enemy* enemy;
					if (enemy = dynamic_cast<Enemy*>(npcs[i])) /*jesli mamy do czynienia z przeciwnikiem*/
					{
						sf::Vertex line[2];
						float distance, distanceTemp;
						float sinus;
						float cosinus;

						if (enemy->getBoundingBox().contains(worldPos))	enemy->acquireCursor(); /*jesli jest nad nim kursor*/
						else enemy->loseCursor(); /*jesli nie ma nad nim kursora*/
						/*wyliczenie odleglosci miedzy graczem a przeciwnikiem*/
						line[0].position = player->getPosition();
						line[1].position = npcs[i]->getPosition();
						distance = sqrt(pow(line[0].position.x - line[1].position.x, 2) + pow(line[0].position.y - line[1].position.y, 2));
						distanceTemp = distance;
						if (distance > 500) /*gdy gracz jest za daleko*/
						{
							if ((enemy->getStatus() != Enemy::STOP) && (enemy->getStatus() != Enemy::WALK) && (enemy->getStatus() != Enemy::ENGAGED)) enemy->stop(false);
						}
						else /*jesli nie jest za daleko, przeciwnik podejmuje probe ataku*/
						{
							if (enemy->getStatus() != Enemy::ATTACK)
							{
								if (!player->isActiveSkill3() || player->getClassName() != "Soldier") enemy->engage(); /*gdy Soldier jest niewidzialny, przeciwnik nie moze go atakowac*/
							}
							do
							{
								/*jesli na drodze pomiedzy graczem a przeciwnikiem jest sciana, przeciwnik sie zatrzymuje*/
								if (level.getMap()[static_cast<unsigned __int64>(line[0].position.y / 64)][static_cast<unsigned __int64>(line[0].position.x / 64)]->isWall())
								{
									if (enemy->getStatus() != Enemy::STOP) enemy->stop(false);
									break;
								}
								distanceTemp = sqrt(pow(line[0].position.x - line[1].position.x, 2) + pow(line[0].position.y - line[1].position.y, 2));
								sinus = (line[0].position.x - line[1].position.x) / distanceTemp;
								cosinus = (line[0].position.y - line[1].position.y) / distanceTemp;
								distanceTemp -= 2.0f;
								line[0].position.x = sinus * distanceTemp + line[1].position.x;
								line[0].position.y = cosinus * distanceTemp + line[1].position.y;
							} while (distanceTemp > 2);
						}
						/*proba zaatakowania przeciwnika przez gracza*/
						if ((player->getStatus() == Player::ATTACK) && (npcs[i]->getBoundingBox().contains(worldPos)) && (sf::Mouse::isButtonPressed(sf::Mouse::Right)))
						{
							fight(i, PLAYER);
							if (enemy->getStatus() != Enemy::ATTACK) enemy->engage(); /*automatyczne zdenerwowanie przeciwnika*/
							if (player->isActiveSkill3() && player->getClassName() == "Soldier") player->clearEffectSkill3(); /*automatyczne przerwanie niewidzialnosci*/
						}
						if (enemy->isAlive()) /*jesli przeciwnik zyje*/
						{
							enemy->update(&level, player->getPosition()); /*aktualizacja przeciwnika*/
							gui.updateHpInfo(i, enemy->getPosition(), enemy->getHp(), enemy->getMaxHp()); /*aktualizacja paska hp przeciwnika*/
							if ((enemy->isEngaged()) || (enemy->isAttacking())) /*proba ataku*/
							{
								if ((enemy->isRanged()) || ((!enemy->isRanged()) && (distance < 70)))
								{
									enemy->attack();
									fight(i, NPC);
								}
								else if (!player->isActiveSkill3() || player->getClassName() != "Soldier") enemy->engage();
							}
						}
						else /*przeciwnik umarl*/
						{
							player->increaseExperience(enemy->getExperienceGiven()); /*dodanie doswiadczenia graczowi*/
							short lootChance = rand() % 101; /*losowanie czy przeciwnik da skrzynie*/
							if (lootChance > 59)
							{
								level.spawnLootChest(npcs[i]->getPosition());
								updateMap();
							}
							/*usuniecie przeciwnika i jego paska hp*/
							gui.eraseHpInfo(i);
							delete npcs[i];
							npcs.erase(npcs.begin() + i);
							--i;
						}
					}

				}
				if (player->getStatus() == Player::Status::WALK) /*jesli gracz chodzi, nalezy aktualizowac kamere i mape*/
				{
					view.setCenter(player->getPosition());
					updateMap();
					window.setView(view);
				}
				if (player->getExp() >= player->getExpForNextLevel()) player->levelUp(); /*awans*/
				if (player->getHp() != tempHp) /*jesli po obsluzeniu wszystkich zdarzen zmienilo sie hp gracza*/
				{
					Gui::TextDamage* hpInfo = new Gui::TextDamage(); /*stworzenie nowej informacji o zmianie hp*/

					hpInfo->text.setString(std::to_string(abs(player->getHp() - tempHp))); /*wyliczenie zmiany hp*/
					/*jesli hp wzroslo tekst jest zielony, jesli zmalalo tekst jest czerwony*/
					if (player->getHp() > tempHp) hpInfo->text.setColor(sf::Color::Green);
					else hpInfo->text.setColor(sf::Color::Red);
					hpInfo->text.setPosition(player->getPosition() - sf::Vector2f(0.0, player->getBoundingBox().height / 2 + 20.0f));
					gui.pushDamageInfo(hpInfo);
				}
			}
			else /*gracz umarl*/
			{
				dead = true;
			}
		}
		if (pause) /*wyswietlenie menu pauzy*/
		{
			while (window.pollEvent(event))
			{
				/*wcisniecie ESC, powrot do gry*/
				if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Escape))
				{
					pause = false;
					player->unpauseTimers(); /*odpauzowanie timerow gracza*/
				}
				/*wcisniecie Quit, powrot do menu*/
				if ((gui.getQuitButton().getGlobalBounds().contains(worldPos)) && (event.type == sf::Event::MouseButtonReleased) && (event.key.code == sf::Mouse::Left))
				{
					view.setCenter(1280 / 2, 720 / 2);
					window.setView(view);
					quit = true;
					pause = false;
				}
				/*wcisniecie Resume, powrot do gry*/
				if ((gui.getResumeButton().getGlobalBounds().contains(worldPos)) && (event.type == sf::Event::MouseButtonReleased) && (event.key.code == sf::Mouse::Left))
				{
					pause = false;
					player->unpauseTimers(); /*odpauzowanie timerow gracza*/
				}
				/*wcisniecie Save*/
				if ((gui.getSaveButton().getGlobalBounds().contains(worldPos)) && (event.type == sf::Event::MouseButtonReleased) && (event.key.code == sf::Mouse::Left))
				{
					Save* temp;
					/*moze sie wykonac tylko gdy gracz stoi na kaflu zapisu*/
					if (temp = dynamic_cast<Save*>(level.getMap()[static_cast<unsigned __int64>(player->getPosition().y / 64)][static_cast<unsigned __int64>(player->getPosition().x / 64)]))
					{
						saveGame(temp->getId());
						MessageBox(NULL, "Successfully saved game!", "SUCCESS", NULL);
					}
					else MessageBox(NULL, "You can only save your game while standing on save tile!", "UNABLE TO SAVE", NULL); /*wyswietlenie bledu*/
				}
			}
			/*podswietlenie przycisku jesli jest nad nim kursor*/
			if (gui.getResumeButton().getGlobalBounds().contains(worldPos)) gui.setResumeHighlight(1);
			else gui.setResumeHighlight(0);
			if (gui.getSaveButton().getGlobalBounds().contains(worldPos)) gui.setSaveHighlight(1);
			else gui.setSaveHighlight(0);
			if (gui.getQuitButton().getGlobalBounds().contains(worldPos)) gui.setQuitHighlight(1);
			else gui.setQuitHighlight(0);
		}
		if (equipment) /*wyswietlenie ekwipunku*/
		{
			while (window.pollEvent(event))
			{
				if ((event.type == sf::Event::KeyReleased) && ((event.key.code == sf::Keyboard::I) || (event.key.code == sf::Keyboard::Escape)))
				{
					equipment = false;
					position = -1;
					player->unpauseTimers(); /*odpauzowanie timerow gracza*/
				}
				for (short i = 0; i < 3; ++i)
				{
					sf::Vector2f plusPosition = window.mapPixelToCoords(sf::Vector2i(340, 235 + i * 30));
					/*sprawdzenie czy uzytkownik probuje dodac punkty do statystyk oraz czy ma jakies dostepne*/
					if ((sf::FloatRect(plusPosition, sf::Vector2f(20, 20)).contains(worldPos)) && (event.type == sf::Event::MouseButtonReleased) && (event.key.code == sf::Mouse::Left) && (player->getPointsToSpend() > 0))
					{
						/*jesli tak, nastepuje inkrementacja odpowiedniej statystyki*/
						switch (i)
						{
						case 0:
							player->increaseStr();
							break;
						case 1:
							player->increaseInt();
							break;
						case 2:
							player->increaseAgi();
							break;
						}
					}
				}
				/*sprawdzenie wszystkich pozycji plecaka*/
				for (short i = 0; i < 2; ++i)
				{
					for (short j = 0; j < 5; ++j)
					{
						sf::Vector2f slotPosition = window.mapPixelToCoords(sf::Vector2i(140 + j * 128, 418 + i * 128));
						/*klikniecie LPM na dana pozycje*/
						if ((sf::FloatRect(slotPosition, sf::Vector2f(128, 128)).contains(worldPos)) && (event.type == sf::Event::MouseButtonReleased) && (event.key.code == sf::Mouse::Left))
						{
							position = 5 * i + j;
						}
						/*lewy shift + LPM na danej pozycji, powoduje wyrzucenie przedmiotu*/
						if ((sf::FloatRect(slotPosition, sf::Vector2f(128, 128)).contains(worldPos)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) && (event.type == sf::Event::MouseButtonReleased) && (event.key.code == sf::Mouse::Left))
						{
							player->deleteItem(5 * i + j);
							position = -1;
						}
						/*lewy ctrl + LPM na danej pozycji, powoduje zamiane przedmiotu z aktywnym przedmiotem*/
						if ((sf::FloatRect(slotPosition, sf::Vector2f(128, 128)).contains(worldPos)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) && (event.type == sf::Event::MouseButtonReleased) && (event.key.code == sf::Mouse::Left))
						{
							player->swapActiveItem(5 * i + j);
							position = -1;
						}
					}
				}
				/*klikniecie LPM na aktywna bron*/
				if ((sf::FloatRect(946, 340, 128, 128).contains(mouse)) && (event.type == sf::Event::MouseButtonReleased) && (event.key.code == sf::Mouse::Left))
				{
					position = -2;
				}
				/*klikniecie LPM na aktywna zbroje*/
				if ((sf::FloatRect(946, 520, 128, 128).contains(mouse)) && (event.type == sf::Event::MouseButtonReleased) && (event.key.code == sf::Mouse::Left))
				{
					position = -3;
				}
				/*lewy shift + LPM na aktywnej broni, powoduje wyrzucenie przedmiotu*/
				if ((sf::FloatRect(946, 340, 128, 128).contains(mouse)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) && (event.type == sf::Event::MouseButtonReleased) && (event.key.code == sf::Mouse::Left))
				{
					player->deleteItem(-1);
					position = -1;
				}
				/*lewy shift + LPM na aktywnej zbroi, powoduje wyrzucenie przedmiotu*/
				if ((sf::FloatRect(946, 520, 128, 128).contains(mouse)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) && (event.type == sf::Event::MouseButtonReleased) && (event.key.code == sf::Mouse::Left))
				{
					player->deleteItem(-2);
					position = -1;
				}
				/*lewy ctrl + LPM na aktywnej broni, powoduje wrzucenie jej do plecaka*/
				if ((sf::FloatRect(946, 340, 128, 128).contains(mouse)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) && (event.type == sf::Event::MouseButtonReleased) && (event.key.code == sf::Mouse::Left))
				{
					player->swapActiveItem(-1);
					position = -1;
				}
				/*lewy ctrl + LPM na aktywnej zbroi, powoduje wrzucenie jej do plecaka*/
				if ((sf::FloatRect(946, 520, 128, 128).contains(mouse)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) && (event.type == sf::Event::MouseButtonReleased) && (event.key.code == sf::Mouse::Left))
				{
					player->swapActiveItem(-2);
					position = -1;
				}
			}			
		}
		if (dead) /*ekran smierci*/
		{
			while (window.pollEvent(event))
			{
				/*wcisniecie ENTER, powoduje powrot do menu glownego*/
				if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Return))
				{
					view.setCenter(1280 / 2, 720 / 2);
					window.setView(view);
					dead = false;
					quit = true;
				}
			}
		}
		if (levelMenu) /*menu zmiany poziomu*/
		{
			while (window.pollEvent(event))
			{
				/*wcisniecie ESC, powoduje powrot do gry*/
				if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Escape))
				{
					levelMenu = false;
					player->unpauseTimers(); /*odpauzowanie timerow gracza*/
				}
				/*wcisniecie 1, wybor poziomu 1*/
				if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Num1))
				{
					player->resetTimers(); /*reset timerow gracza*/
					levelMenu = false;
					setMap(window, "levels/level1.level", 0); /*ustawienie poziomu*/				
				}
				/*wcisniecie 2, wybor poziomu 2*/
				if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Num2))
				{
					player->resetTimers(); /*reset timerow gracza*/
					levelMenu = false;
					setMap(window, "levels/level2.level", 0); /*ustawienie poziomu*/
				}
				/*wcisniecie 3, wybor poziomu 3*/
				if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Num3))
				{
					MessageBox(NULL, "This level is yet to be designed!", "ERROR", NULL); /*komunikat dla jeszcze nieistniejacego poziomu*/
				}
				/*wcisniecie 4, wybor poziomu 4*/
				if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Num4))
				{
					MessageBox(NULL, "This level is yet to be designed!", "ERROR", NULL); /*komunikat dla jeszcze nieistniejacego poziomu*/
				}
				/*wcisniecie 5, wybor poziomu 5*/
				if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Num5))
				{
					MessageBox(NULL, "This level is yet to be designed!", "ERROR", NULL); /*komunikat dla jeszcze nieistniejacego poziomu*/
				}
			}
		}
		draw(window, cursor, pause, equipment, dead, levelMenu, position); /*wyswietlenie wszystkiego na ekranie*/
	}
}
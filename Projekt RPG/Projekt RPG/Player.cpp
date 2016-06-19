#define _USE_MATH_DEFINES
#include "Player.h"
#include <Windows.h>
#include <cmath>

Player::Player(std::string _name) : name(_name)
{
	/*ustawienie sprite'a*/
	texture.loadFromFile("images/tilesheet.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 640, 64, 64));
	sprite.setOrigin(32, 32);

	speed = 5.5f; /*ustawienie predkosci*/
	walkFrame = 0;	/*ustawienie obecnej klatki chodzenia*/
	walkFrameCount = 7;
	attackFrame = 0; /*ustawienie obecnej klatki ataku*/
	attackFrameCount = 0;
	/*rozpoczecie clockow*/
	walkAnimationClock.restart();
	attackAnimationClock.restart();
	attackInterval.restart();
	/*na poczatku umiejetnosci sa niekatywne*/
	activeSkill1 = false;
	activeSkill2 = false;
	activeSkill3 = false;
	/*statystyki poczatkowe*/
	parLvl = 1;
	parPointsToSpend = 0;
	parExp = 0;	
	parExpForNextLevel = 83;	
}

Player::Player(std::string _name, std::fstream &file) : name(_name)
{
	/*ustawienie sprite'a*/
	texture.loadFromFile("images/tilesheet.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 640, 64, 64));
	sprite.setOrigin(32, 32);

	speed = 5.5f; /*ustawienie predkosci*/
	walkFrame = 0; /*ustawienie obecnej klatki chodzenia*/
	attackFrame = 0; /*ustawienie obecnej klatki ataku*/
	walkFrameCount = 7;
	attackFrameCount = 0;
	/*rozpoczecie clockow*/
	walkAnimationClock.restart();
	attackAnimationClock.restart();
	attackInterval.restart();
	/*na poczatku umiejetnosci sa niekatywne*/
	activeSkill1 = false;
	activeSkill2 = false;
	activeSkill3 = false;

	std::string text, name;
	short value, which;
	/*wczytanie statystyk z pliku*/
	file >> parLvl >> parExp >> parExpForNextLevel;
	file >> parHp >> parMaxHp;
	file >> parStr >> parInt >> parAgi >> parPointsToSpend;
	file >> value;
	/*ustawienie ilosci mikstur*/
	equipment.setPotionCount(value);
	/*wczytanie aktywnej broni*/
	file >> text;
	if (text == "[ACTIVEWEAPON]")
	{
		file >> text;
		if (text != "[NULL]") /*jesli ta bron faktycznie jest*/
		{
			Item* tmp;
			file >> value; /*wczytanie wartosci ataku*/
			file >> which; /*wczytanie ktory obrazek w pliku tilesheet.png jej odpowiada*/
			getline(file, name); /*wczytanie nazwy przedmiotu*/
			name.erase(0, 1); /*usuniecie spacji z poczatku*/
			if (text == "[RANGED]") tmp = new Weapon(name, value, true, which); /*stworzenie broni dystansowej*/
			else tmp = new Weapon(name, value, false, which); /*stworzenie broni melee*/
			equipment.addItem(tmp); /*dodanie jej do ekwipunku*/
			equipment.swapActiveItem(0); /*ustawienie jako aktywnej*/
			equipment.deleteItem(0); /*usuniecie domyslnie tworzonej losowej broni*/
		}
		else equipment.deleteItem(-1); /*usuniecie domyslnie tworzonej losowej broni*/
	}
	/*wczytanie aktywnej zbroi*/
	file >> text;
	if (text == "[ACTIVEARMOR]")
	{
		file >> text;
		if (text != "[NULL]") /*jesli ta zbroja faktycznie jest*/
		{
			Item* tmp;
			/*jesli text nie byl [NULL] to do zmiennej text zostala wczytana wartosc defensywna zbroi*/
			file >> which; /*wczytanie ktory obrazek w pliku tilesheet.png jej odpowiada*/
			getline(file, name); /*wczytanie nazwy przedmiotu*/
			name.erase(0, 1); /*usuniecie spacji z poczatku*/
			tmp = new Armor(name, stoi(text), which); /*stworzenie zbroi*/
			equipment.addItem(tmp); /*dodanie jej do ekwipunku*/
			equipment.swapActiveItem(0); /*ustawienie jako aktywnej*/
			equipment.deleteItem(0); /*usuniecie domyslnie tworzonej losowej zbroi*/
		}
		else equipment.deleteItem(-2); /*usuniecie domyslnie tworzonej losowej zbroi*/
	}
	while (!file.eof()) /*wczytywanie reszty przedmiotow*/
	{
		file >> text;
		if (text == "[ARMOR]") /*zbroja*/
		{
			Item* tmp;
			file >> value; /*wczytanie wartosci obrony*/
			file >> which; /*wczytanie ktory obrazek w pliku tilesheet.png jej odpowiada*/
			getline(file, name); /*wczytanie nazwy przedmiotu*/
			name.erase(0, 1); /*usuniecie spacji z poczatku*/
			tmp = new Armor(name, value, which); /*stworzenie zbroi*/
			equipment.addItem(tmp); /*dodanie jej do ekwipunku*/
		}
		else if (text == "[WEAPON]") /*bron*/
		{
			Item* tmp;
			file >> text; /*wczytanie czy bedzie to bron dystansowa czy melee*/
			file >> value; /*wczytanie wartosci ataku*/
			file >> which; /*wczytanie ktory obrazek w pliku tilesheet.png jej odpowiada*/
			getline(file, name); /*wczytanie nazwy przedmiotu*/
			name.erase(0, 1); /*usuniecie spacji z poczatku*/
			if (text == "[RANGED]") tmp = new Weapon(name, value, true, which); /*stworzenie broni dystansowej*/
			else tmp = new Weapon(name, value, false, which); /*stworzenie broni melee*/
			equipment.addItem(tmp); /*dodanie jej do ekwipunku*/
		}
	}	
}

Player::~Player()
{
	equipment.clearBackpack(); /*wyczyszczenie ekwipunku*/
}

short Player::update(sf::Vector2f mouse, Level *level)
{
	short result = 0;
	TrapFountain* temp1;
	LootChest* temp2;
	sf::Vector2f norm = mouse - sprite.getPosition(); /*wektor miedzy kursorem a graczem*/
	/*obliczenie rotacji tak, aby gracz byl zawsze zwrocony w kierunku kursora*/
	float rot = atan2(norm.y, norm.x); /*zalozenie ze przod sprite'a jest na gorze*/
	rot = rot * 180.f / static_cast<float>(M_PI);
	rot += 90;
	sprite.setRotation(rot);

	if (!activeSkill3 || getClassName() != "Juggernaut") parMaxHp = 100 + parStr; /*maksymalne zdrowie zalezy od wartosci bazowej oraz wartosci sily, chyba ze jest aktywna umiejetnosc trzecia Juggernauta (czasowe zwiekszenie maksymalnego hp)*/

	if (temp1 = dynamic_cast<TrapFountain*>(level->getMap()[static_cast<int>(getPosition().y / 64)][static_cast<int>(getPosition().x / 64)])) parHp += temp1->getHpChange(); /*jesli gracz stoi na pulapce lub fontannie*/
	if (parHp > parMaxHp) parHp = parMaxHp; /*gdyby hp mialo przekroczyc maksymalna mozliwa wartosc*/
	/*gdyby skonczyl sie czas trwania efektu umiejetnosci oraz byl on wciaz aktywny, nalezy usunac ten efekt*/
	if (effectSkill1.isExpired() && activeSkill1) clearEffectSkill1();
	if (effectSkill2.isExpired() && activeSkill2) clearEffectSkill2();
	if (effectSkill3.isExpired() && activeSkill3) clearEffectSkill3();
	/*gdy gracz sie porusza*/
	if (status == WALK)
	{
		/*gracz moze sie poruszyc jedynie co okreslona ilosc czasu*/
		if (walkAnimationClock.getElapsedTime() > sf::seconds(0.04f))
		{
			if (walkFrame < walkFrameCount) /*liczba klatek animacji - 1*/
				walkFrame++;
			else
				walkFrame = 0; /*animacja sie zapetla*/
			sprite.setTextureRect(sf::IntRect(walkFrame * 64, 640, 64, 64)); /*ustawienie odpowiedniej klatki*/
			sprite.move(getMove()); /*przesuniecie postaci*/
			/*wszystkie +15 i -15 sa tolerancja boundingboxa w przypadku kolizji*/
			/*jesli gracz mialby wejsc na sciane/wyjsc poza granice poziomu, ruch zostaje cofniety, a postac sie zatrzymuje*/
			if (sprite.getGlobalBounds().left + 15 < 0) /*lewa krawedz poziomu*/
			{
				sprite.move(-getMove());
				stop();
			}
			if (sprite.getGlobalBounds().top + 15 < 0) /*gorna krawedz poziomu*/
			{
				sprite.move(-getMove());
				stop();
			}
			if (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width - 15 > level->getWidth() * 64) /*prawa krawedz poziomu*/
			{
				sprite.move(-getMove());
				stop();
			}
			if (sprite.getGlobalBounds().top + sprite.getGlobalBounds().height - 15 > level->getHeight() * 64) /*dolna krawedz poziomu*/
			{
				sprite.move(-getMove());
				stop();
			}
			/*w przypadku kolizji z kaflami zostaje sprawdzone czy nie jest to kolizja ze skrzynia zawierajaca przedmioty - jesli tak to skrzynka znika a przedmiot zostaje dodany do ekwipunku*/
			if (level->getMap()[static_cast<int>(getPosition().y / 64)][static_cast<int>((sprite.getGlobalBounds().left + 15) / 64)]->isWall()) /*kolizja z kaflem po lewej*/
			{
				if (temp2 = dynamic_cast<LootChest*>(level->getMap()[static_cast<int>(getPosition().y / 64)][static_cast<int>((sprite.getGlobalBounds().left + 15) / 64)]))
				{
					if ((temp2->containsPotion()) || (equipment.getBackpack().size() < Equipment::backpackSize)) /*miksture mozna dodac zawsze, przedmiot tylko jesli jest na niego miejsce w plecaku*/
					{
						if (temp2->containsPotion()) equipment.addPotion(); /*dodanie mikstury*/
						else /*dodanie przedmiotu*/
						{
							Item* item;
							/*losowanie czy bron czy zbroja*/
							if (rand() % 2 == 0) item = new Armor(parLvl);
							else
							{
								/*jesli bron, losowanie czy dystansowa czy melee*/
								if (rand() % 2 == 0) item = new Weapon(false, parLvl);
								else item = new Weapon(true, parLvl);
							}
							equipment.addItem(item); /*dodanie do ekwipunku*/
						}
						level->deleteLootChest(sf::Vector2f(sprite.getGlobalBounds().left + 15, getPosition().y)); /*usuniecie skrzynki i zastapienie jej kaflem ktory byl tam wczesniej*/
						result = 1;
					}
				}
				sprite.move(-getMove());
				stop();
			}
			if (level->getMap()[static_cast<int>(getPosition().y / 64)][static_cast<int>((sprite.getGlobalBounds().left + sprite.getGlobalBounds().width - 15) / 64)]->isWall()) /*kolizja z kaflem po prawej*/
			{
				if (temp2 = dynamic_cast<LootChest*>(level->getMap()[static_cast<int>(getPosition().y / 64)][static_cast<int>((sprite.getGlobalBounds().left + sprite.getGlobalBounds().width - 15) / 64)]))
				{
					if ((temp2->containsPotion()) || (equipment.getBackpack().size() < Equipment::backpackSize))
					{
						if (temp2->containsPotion()) equipment.addPotion();
						else
						{
							Item* item;
							if (rand() % 2 == 0) item = new Armor(parLvl);
							else
							{
								if (rand() % 2 == 0) item = new Weapon(false, parLvl);
								else item = new Weapon(true, parLvl);
							}
							equipment.addItem(item);
						}
						level->deleteLootChest(sf::Vector2f(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width - 15, getPosition().y));
						result = 1;
					}
				}
				sprite.move(-getMove());
				stop();
			}
			if (level->getMap()[static_cast<int>((sprite.getGlobalBounds().top + 15) / 64)][static_cast<int>(getPosition().x / 64)]->isWall()) /*kolizja z kaflem z gory*/
			{
				if (temp2 = dynamic_cast<LootChest*>(level->getMap()[static_cast<int>((sprite.getGlobalBounds().top + 15) / 64)][static_cast<int>(getPosition().x / 64)]))
				{
					if ((temp2->containsPotion()) || (equipment.getBackpack().size() < Equipment::backpackSize))
					{
						if (temp2->containsPotion()) equipment.addPotion();
						else
						{
							Item* item;
							if (rand() % 2 == 0) item = new Armor(parLvl);
							else
							{
								if (rand() % 2 == 0) item = new Weapon(false, parLvl);
								else item = new Weapon(true, parLvl);
							}
							equipment.addItem(item);
						}
						level->deleteLootChest(sf::Vector2f(getPosition().x, sprite.getGlobalBounds().top + 15));
						result = 1;
					}
				}
				sprite.move(-getMove());
				stop();
			}
			if (level->getMap()[static_cast<int>((sprite.getGlobalBounds().top + sprite.getGlobalBounds().height - 15) / 64)][static_cast<int>(getPosition().x / 64)]->isWall()) /*kolizja z kaflem z dolu*/
			{
				if (temp2 = dynamic_cast<LootChest*>(level->getMap()[static_cast<int>((sprite.getGlobalBounds().top + sprite.getGlobalBounds().height - 15) / 64)][static_cast<int>(getPosition().x / 64)]))
				{
					if ((temp2->containsPotion()) || (equipment.getBackpack().size() < Equipment::backpackSize))
					{
						if (temp2->containsPotion()) equipment.addPotion();
						else
						{
							Item* item;
							if (rand() % 2 == 0) item = new Armor(parLvl);
							else
							{
								if (rand() % 2 == 0) item = new Weapon(false, parLvl);
								else item = new Weapon(true, parLvl);
							}
							equipment.addItem(item);
						}
						level->deleteLootChest(sf::Vector2f(getPosition().x, sprite.getGlobalBounds().top + sprite.getGlobalBounds().height - 15));
						result = 1;
					}
				}
				sprite.move(-getMove());
				stop();
			}
			walkAnimationClock.restart(); /*reset clocka animacji*/
		}
	}
	/*gdy gracz atakuje*/
	else if (status == ATTACK)
	{
		/*animacja wystepuje tylko jesli sa dostepne jakies klatki animacji oraz zmiana klatki moze nastapic tylko co okreslony okres czasu*/
		if ((attackFrameCount > 0) && (attackAnimationClock.getElapsedTime() > sf::seconds(.1f)))
		{
			sf::IntRect tmpRect;
			if (attackFrame < attackFrameCount) /*liczba klatek animacji - 1*/
				++attackFrame;
			else
				attackFrame = 0; /*animacja sie zapetla*/
			/*ustawianie kolejnych klatek animacji ataku*/
			tmpRect = sprite.getTextureRect();
			tmpRect.left = (attackFrame + walkFrameCount + 1) * 64;
			sprite.setTextureRect(tmpRect);			
			attackAnimationClock.restart(); /*reset clocka animacji*/
		}
	}
	return result;
}

void Player::walk()
{
	status = WALK;
}

void Player::stop()
{
	status = STOP;
	/*gdy gracz sie zatrzymuje zostaje ustawiona pierwsza klatka animacji chodzenia*/
	walkFrame = 0;
	attackFrame = 0;
	sprite.setTextureRect(sf::IntRect(walkFrame * 64, 640, 64, 64));
	walkAnimationClock.restart();
}

void Player::attack()
{
	status = ATTACK;
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite);
}

Player::Status Player::getStatus()
{
	return status;
}

sf::FloatRect Player::getBoundingBox()
{
	sf::FloatRect box(sprite.getGlobalBounds());
	return box;
}

sf::Vector2f Player::getMove()
{
	float rotation = sprite.getRotation();
	float vx = sin((rotation * static_cast<float>(M_PI)) / 180.0f); /*wyliczenie przemieszczenia na osi x*/
	float vy = -cos((rotation * static_cast<float>(M_PI)) / 180.0f); /*wyliczenie przemieszczenia na osi y*/

	return sf::Vector2f(vx * speed, vy * speed);
}

sf::Vector2f Player::getPosition()
{
	return sprite.getPosition();
}

void Player::setPosition(Tile::Coord coord)
{
	sprite.setPosition(coord.x * 64.f + 32.f, coord.y * 64.f + 32.f); /*ustawienie pozycji jako koordynaty * szerokosc kafla + polowa szerokosci kafla - zeby ustawic idealnie na srodku*/
}

std::string Player::getName()
{
	return name;
}

Equipment* Player::getEquipment()
{
	return &equipment;
}

short Player::getHp()
{
	return parHp;
}

short Player::getMaxHp()
{
	return parMaxHp;
}

unsigned short Player::getPointsToSpend()
{
	return parPointsToSpend;
}

unsigned Player::getExp()
{
	return parExp;
}

unsigned Player::getExpForNextLevel()
{
	return parExpForNextLevel;
}

unsigned short Player::getLvl()
{
	return parLvl;
}

unsigned short Player::getStr()
{
	return parStr;
}

unsigned short Player::getAgi()
{
	return parAgi;
}

unsigned short Player::getInt()
{
	return parInt;
}

void Player::increaseStr()
{
	++parStr;
	--parPointsToSpend;
}

void Player::increaseAgi()
{
	++parAgi;
	--parPointsToSpend;
}

void Player::increaseInt()
{
	++parInt;
	--parPointsToSpend;
}

void Player::levelUp()
{
	double sum = 0.0;

	parExp -= parExpForNextLevel;
	++parLvl;
	/*wyliczenie doswiadczenia na podstawie formuly z Runescape*/
	for (double i = 1.0; i < parLvl + 1; ++i)
	{
		sum += floor(i + 300.0 * pow(2.0, i/7.0));
	}
	parExpForNextLevel = static_cast<int>(floor(sum/4.0));
	parPointsToSpend += 5;
}

void Player::deleteItem(short position)
{
	equipment.deleteItem(position);
}

void Player::addItem(Item* newItem)
{
	equipment.addItem(newItem);
}

void Player::swapActiveItem(short position)
{
	equipment.swapActiveItem(position);
}

void Player::usePotion()
{
	if (equipment.usePotion() == 0) parHp += static_cast<short>(0.6 * parMaxHp); /*gracz jest leczony o 60% maksymalnego hp jesli ma dostepne mikstury*/
}

void Player::increaseExperience(unsigned experience)
{
	parExp += experience;
}

void Player::takeDamage(unsigned damage)
{
	parHp -= damage;
}

sf::Clock Player::getAttackInterval()
{
	return attackInterval;
}

void Player::restartAttackInterval()
{
	attackInterval.restart();
}

void Player::pauseTimers()
{
	/*zatrzymanie wszystkich timerow*/
	cooldownSkill1.stop();
	cooldownSkill2.stop();
	cooldownSkill3.stop();
	effectSkill1.stop();
	effectSkill2.stop();
	effectSkill3.stop();
}

void Player::unpauseTimers()
{
	/*wznowienie dzialania wszystkich timerow*/
	cooldownSkill1.start();
	cooldownSkill2.start();
	cooldownSkill3.start();
	effectSkill1.start();
	effectSkill2.start();
	effectSkill3.start();
}

void Player::resetTimers()
{
	/*zresetowanie timerow, przechodza w stan expired niemal od razu*/
	cooldownSkill1.restart(sf::microseconds(1));
	cooldownSkill2.restart(sf::microseconds(1));
	cooldownSkill3.restart(sf::microseconds(1));
	effectSkill1.restart(sf::microseconds(1));
	effectSkill2.restart(sf::microseconds(1));
	effectSkill3.restart(sf::microseconds(1));
}

bool Player::isActiveSkill1()
{
	return activeSkill1;
}

bool Player::isActiveSkill2()
{
	return activeSkill2;
}

bool Player::isActiveSkill3()
{
	return activeSkill3;
}

Juggernaut::Juggernaut(std::string _name) : Player(_name)
{
	sprite.setColor(sf::Color(255, 140, 140)); /*kolor czerwony*/
	/*statystyki nastawione na sile*/
	parStr = 18;
	parAgi = 6;
	parInt = 6;
	parHp = parMaxHp = 100 + parStr;
}

Juggernaut::Juggernaut(std::string _name, std::fstream &file) : Player(_name, file)
{
	sprite.setColor(sf::Color(255, 140, 140));
}

Juggernaut::~Juggernaut()
{

}

std::string Juggernaut::getClassName()
{
	return "Juggernaut";
}

void Juggernaut::useSkill1() /*nietykalnosc*/
{
	if (cooldownSkill1.isExpired())
	{
		cooldownSkill1.restart(sf::seconds(120.f));
		effectSkill1.restart(sf::seconds(1.7f + parInt / 100.f)); /*+0.1s za kazde 10 int*/
		activeSkill1 = true;
	}
}

void Juggernaut::useSkill2() /*mocniejszy atak o 50%*/
{
	if (cooldownSkill2.isExpired())
	{
		cooldownSkill2.restart(sf::seconds(10.f - parInt / 50.f)); /*-0.1s za kazde 5 int*/
		effectSkill2.restart(sf::seconds(3.f));
		activeSkill2 = true;
	}
}

void Juggernaut::useSkill3()
{
	/*czasowo wiecej max hp o 20%*/
	if (cooldownSkill3.isExpired())
	{
		parMaxHp += static_cast<short>(0.2 * parMaxHp);
		cooldownSkill3.restart(sf::seconds(35.f));
		effectSkill3.restart(sf::seconds(5.f + parInt / 50.f)); /*+0.1s za kazde 5 int*/
		activeSkill3 = true;
	}
}

void Juggernaut::clearEffectSkill1()
{
	activeSkill1 = false;
}

void Juggernaut::clearEffectSkill2()
{
	activeSkill2 = false;
}

void Juggernaut::clearEffectSkill3()
{
	parMaxHp = static_cast<short>(parMaxHp / 1.2);
	activeSkill3 = false;
}

float Juggernaut::getRatioSkill1()
{
	return cooldownSkill1.getRemainingTime().asSeconds() / 120.f;
}

float Juggernaut::getRatioSkill2()
{
	return cooldownSkill2.getRemainingTime().asSeconds() / (10.f - parInt / 50.f);
}

float Juggernaut::getRatioSkill3()
{
	return cooldownSkill3.getRemainingTime().asSeconds() / 35.f;
}

Soldier::Soldier(std::string _name) : Player(_name)
{
	sprite.setColor(sf::Color::Yellow);
	/*statystyki nastawione na zrecznosc*/
	parAgi = 16;
	parStr = 6;
	parInt = 8;
	parHp = parMaxHp = 100 + parStr;
}

Soldier::Soldier(std::string _name, std::fstream &file) : Player(_name, file)
{
	sprite.setColor(sf::Color::Yellow);
}

Soldier::~Soldier()
{

}

std::string Soldier::getClassName()
{
	return "Soldier";
}

void Soldier::useSkill1() /*szybsze strzelanie*/
{
	if (cooldownSkill1.isExpired())
	{
		cooldownSkill1.restart(sf::seconds(40.f));
		effectSkill1.restart(sf::seconds(1.f + parInt / 100.f));
		activeSkill1 = true;
	}
}

void Soldier::useSkill2() /*przyspieszenie*/
{
	if (cooldownSkill2.isExpired())
	{
		/*przyspiesza o stala wartosc + 0.1 za kazde 10 int*/
		speed += 3.f + parInt / 100.f;
		cooldownSkill2.restart(sf::seconds(24.f));
		effectSkill2.restart(sf::seconds(3.5f));
		activeSkill2 = true;
	}
}

void Soldier::useSkill3()
{
	if (cooldownSkill3.isExpired())
	{
		/*niewidzialnosc*/
		sf::Color color = sprite.getColor();
		color.a -= 130; /*zmniejszenie alfy, daje efekt lekkiej przezroczystosci*/
		sprite.setColor(color);
		cooldownSkill3.restart(sf::seconds(60.f));
		effectSkill3.restart(sf::seconds(4.f));
		activeSkill3 = true;
	}
}

void Soldier::clearEffectSkill1()
{
	activeSkill1 = false;
}

void Soldier::clearEffectSkill2()
{
	speed -= 3.f + parInt / 100.f;
	activeSkill2 = false;
}

void Soldier::clearEffectSkill3()
{
	sf::Color color = sprite.getColor();
	color.a += 130;
	sprite.setColor(color);
	activeSkill3 = false;
}

float Soldier::getRatioSkill1()
{
	return cooldownSkill1.getRemainingTime().asSeconds() / 40.f;
}

float Soldier::getRatioSkill2()
{
	return cooldownSkill2.getRemainingTime().asSeconds() / 24.f;
}

float Soldier::getRatioSkill3()
{
	return cooldownSkill3.getRemainingTime().asSeconds() / 60.f;
}

Sentinel::Sentinel(std::string _name) : Player(_name)
{
	sprite.setColor(sf::Color(140, 140, 255)); /*kolor niebieski*/
	/*statystyki nastawione na inteligencje*/
	parInt = 19;
	parStr = 5;
	parAgi = 6;
	parHp = parMaxHp = 100 + parStr;
}

Sentinel::Sentinel(std::string _name, std::fstream &file) : Player(_name, file)
{
	sprite.setColor(sf::Color(140, 140, 255));
}

Sentinel::~Sentinel()
{

}

std::string Sentinel::getClassName()
{
	return "Sentinel";
}

void Sentinel::useSkill1() /*heal*/
{
	/*leczy 30% hp + 1% za kazde 10 int*/
	if (cooldownSkill1.isExpired())
	{
		parHp += static_cast<short>(((30.0 + parInt / 10.0) / 100.0) * parMaxHp);
		cooldownSkill1.restart(sf::seconds(40.f));
	}
}

void Sentinel::useSkill2() /*zwiekszenie szansy na dodge oraz trafienie z broni dystansowej*/
{
	if (cooldownSkill2.isExpired())
	{
		parAgi += static_cast<unsigned short>((0.33f + parInt / 100.f) * parAgi); /*zwieksza zrecznosc o 33% + 1% za kazdy 1 int*/
		cooldownSkill2.restart(sf::seconds(35.f));
		effectSkill2.restart(sf::seconds(7.f));
		activeSkill2 = true;
	}
}

void Sentinel::useSkill3()
{
	/*zwiekszenie celnosci*/
	if (cooldownSkill3.isExpired())
	{
		cooldownSkill3.restart(sf::seconds(25.f));
		effectSkill3.restart(sf::seconds(1.f + parInt / 100.f));
		activeSkill3 = true;
	}
}

void Sentinel::clearEffectSkill1()
{

}

void Sentinel::clearEffectSkill2()
{
	parAgi = static_cast<unsigned short>(100.f * parAgi / (133.f + parInt / 10.f));
	activeSkill2 = false;
}

void Sentinel::clearEffectSkill3()
{
	activeSkill3 = false;
}

float Sentinel::getRatioSkill1()
{
	return cooldownSkill1.getRemainingTime().asSeconds() / 40.f;
}

float Sentinel::getRatioSkill2()
{
	return cooldownSkill2.getRemainingTime().asSeconds() / 35.f;
}

float Sentinel::getRatioSkill3()
{
	return cooldownSkill3.getRemainingTime().asSeconds() / 25.f;
}
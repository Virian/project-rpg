#define _USE_MATH_DEFINES
#include "Player.h"
#include <Windows.h>
#include <cmath>

Player::Player(string _name) : name(_name)
{
	if (!texture.loadFromFile("images/tilesheet.png")) /*Reminder - do zmiany sciezka*/
	{
		MessageBox(NULL, "Textures not found!", "ERROR", NULL);
		return; /*Remider - powinien w ogole jakos te gre wywalic, co najmniej do menu*/
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 640, 64, 64));
	sprite.setOrigin(32, 32);

	speed = 5.5f;
	frame = 0;
	anim_clock.restart();
	activeSkill1 = false;
	activeSkill2 = false;
	activeSkill3 = false;
	parLvl = 1;
	parPointsToSpend = 0;
	parExp = 0;	
	parExpForNextLevel = 83;
	parMaxHp = parHp = 100;
	attackInterval.restart();
}

Player::Player(string _name, fstream &file) : name(_name)
{
	if (!texture.loadFromFile("images/tilesheet.png")) /*Reminder - do zmiany sciezka*/
	{
		MessageBox(NULL, "Textures not found!", "ERROR", NULL);
		return; /*Remider - powinien w ogole jakos te gre wywalic, co najmniej do menu*/
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 640, 64, 64));
	sprite.setOrigin(32, 32);

	speed = 5.5f;
	frame = 0;
	anim_clock.restart();
	activeSkill1 = false;
	activeSkill2 = false;
	activeSkill3 = false;

	string text, name;
	short value;
	file >> parLvl >> parExp >> parExpForNextLevel;
	file >> parHp >> parMaxHp;
	file >> parStr >> parInt >> parAgi >> parPointsToSpend;
	file >> value;
	equipment.setPotionCount(value);
	file >> text;
	if (text == "[ACTIVEWEAPON]")
	{
		file >> text;
		if (text != "[NULL]")
		{
			Item* tmp;
			file >> value;
			getline(file, name);
			name.erase(0, 1);
			if (text == "[RANGED]") tmp = new Weapon(name, value, true);
			else tmp = new Weapon(false);
			equipment.addItem(tmp);
			equipment.swapActiveItem(0);
			equipment.deleteItem(0);
		}
	}
	file >> text;
	if (text == "[ACTIVEARMOR]")
	{
		file >> text;
		if (text != "[NULL]")
		{
			Item* tmp;
			getline(file, name);
			name.erase(0, 1);
			tmp = new Armor(name, stoi(text));
			equipment.addItem(tmp);
			equipment.swapActiveItem(0);
			equipment.deleteItem(0);
		}
	}
	while (!file.eof())
	{
		file >> text;
		if (text == "[ARMOR]")
		{
			Item* tmp;
			file >> value;
			getline(file, name);
			name.erase(0, 1);
			tmp = new Armor(name, value);
			equipment.addItem(tmp);
		}
		else if (text == "[WEAPON]")
		{
			Item* tmp;
			file >> text;
			file >> value;
			getline(file, name);
			name.erase(0, 1);
			if (text == "[RANGED]") tmp = new Weapon(name, value, true);
			else tmp = new Weapon(name, value, false);
			equipment.addItem(tmp);
		}
	}

	attackInterval.restart();
}

Player::~Player()
{
	equipment.clearBackpack();
}

short Player::update(Vector2f mouse, Level *level) 
{
	short result = 0;
	TrapFountain* temp1;
	LootChest* temp2;
	Vector2f norm = mouse - sprite.getPosition();
	float rot = atan2(norm.y, norm.x); /*gdy przod playera jest na gorze tekstury, gdyby byl na dole to zamienic x z y*/
	rot = rot * 180.f / static_cast<float>(M_PI);
	rot += 90;
	sprite.setRotation(rot);

	if (temp1 = dynamic_cast<TrapFountain*>(level->getMap()[static_cast<int>(getPosition().y / 64)][static_cast<int>(getPosition().x / 64)])) parHp += temp1->getHpChange();
	if (parHp > parMaxHp) parHp = parMaxHp;

	if (effectSkill1.isExpired() && activeSkill1) clearEffectSkill1();
	if (effectSkill2.isExpired() && activeSkill2) clearEffectSkill2();
	if (effectSkill3.isExpired() && activeSkill3) clearEffectSkill3();
	
	if (anim_clock.getElapsedTime() > seconds(0.04f))
	{
		if (status != WALK) return result;
		if (frame < 7) /*liczba klatek animacji - 1*/
			frame++;
		else
			frame = 0; /*animacja sie zapetla*/
		sprite.setTextureRect(IntRect(frame * 64, 640, 64, 64));
		sprite.move(getMove());
		/*wszystkie +15 i -15 sa tolerancja boundingboxa w przypadku kolizji*/
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
		if (level->getMap()[static_cast<int>(getPosition().y / 64)][static_cast<int>((sprite.getGlobalBounds().left + 15) / 64)]->isWall()) /*kolizja z kaflem po lewej*/
		{
			if (temp2 = dynamic_cast<LootChest*>(level->getMap()[static_cast<int>(getPosition().y / 64)][static_cast<int>((sprite.getGlobalBounds().left + 15) / 64)]))
			{
				if ((temp2->containsPotion()) || (equipment.getBackpack().size() < Equipment::backpackSize))
				{
					if (temp2->containsPotion()) equipment.addPotion();
					else
					{
						Item* item;
						if (rand() % 2 == 0) item = new Armor();
						else
						{
							if (rand() % 2 == 0) item = new Weapon(false);
							else item = new Weapon(true);
						}
						equipment.addItem(item);
					}
					level->deleteLootChest(Vector2f(sprite.getGlobalBounds().left + 15, getPosition().y));
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
						if (rand() % 2 == 0) item = new Armor();
						else
						{
							if (rand() % 2 == 0) item = new Weapon(false);
							else item = new Weapon(true);
						}
						equipment.addItem(item);
					}
					level->deleteLootChest(Vector2f(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width - 15, getPosition().y));
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
						if (rand() % 2 == 0) item = new Armor();
						else
						{
							if (rand() % 2 == 0) item = new Weapon(false);
							else item = new Weapon(true);
						}
						equipment.addItem(item);
					}
					level->deleteLootChest(Vector2f(getPosition().x, sprite.getGlobalBounds().top + 15));
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
						if (rand() % 2 == 0) item = new Armor();
						else
						{
							if (rand() % 2 == 0) item = new Weapon(false);
							else item = new Weapon(true);
						}
						equipment.addItem(item);
					}
					level->deleteLootChest(Vector2f(getPosition().x, sprite.getGlobalBounds().top + sprite.getGlobalBounds().height - 15));
					result = 1;
				}
			}
			sprite.move(-getMove());
			stop();
		}
		anim_clock.restart();		
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
	frame = 0;
	sprite.setTextureRect(IntRect(frame * 64, 640, 64, 64));
	anim_clock.restart();
}

void Player::attack()
{
	status = ATTACK;
}

void Player::draw(RenderTarget &target, RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite);
}

Player::Status Player::getStatus()
{
	return status;
}

FloatRect Player::getBoundingBox()
{
	FloatRect box(sprite.getGlobalBounds());
	return box;
}

Vector2f Player::getMove()
{
	float rotation = sprite.getRotation();
	float vx = sin((rotation * static_cast<float>(M_PI)) / 180.0f);
	float vy = -cos((rotation * static_cast<float>(M_PI)) / 180.0f);

	return Vector2f(vx * speed, vy * speed);
}

Vector2f Player::getPosition()
{
	return sprite.getPosition();
}

void Player::setPosition(Tile::Coord coord)
{
	sprite.setPosition(coord.x * 64.f + 32.f, coord.y * 64.f + 32.f);
}

std::string Player::getName()
{
	return name;
}

Equipment Player::getEquipment()
{
	return equipment;
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
	if (equipment.usePotion() == 0) parHp += static_cast<short>(0.6 * parMaxHp);
}

void Player::increaseExperience(unsigned experience)
{
	parExp += experience;
}

void Player::takeDamage(unsigned damage)
{
	parHp -= damage;
}

Clock Player::getAttackInterval()
{
	return attackInterval;
}

void Player::restartAttackInterval()
{
	attackInterval.restart();
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

Juggernaut::Juggernaut(string _name) : Player(_name)
{
	sprite.setColor(Color(255, 140, 140));
	parStr = 18;
	parAgi = 6;
	parInt = 6;
}

Juggernaut::Juggernaut(string _name, fstream &file) : Player(_name, file)
{
	sprite.setColor(Color(255, 140, 140));
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
		parAgi += 20000;
		cooldownSkill1.restart(seconds(120.f));
		effectSkill1.restart(seconds(1.7f + parInt / 100.f)); /*+0.1s za kazde 10 int*/
		activeSkill1 = true;
	}
}

void Juggernaut::useSkill2() /*mocniejszy atak o 50%*/
{
	if (cooldownSkill2.isExpired())
	{
		cooldownSkill2.restart(seconds(10.f - parInt / 50.f)); /*-0.1s za kazde 5 int*/
		effectSkill2.restart(seconds(3.f));
		activeSkill2 = true;
	}
}

void Juggernaut::useSkill3()
{

}

void Juggernaut::clearEffectSkill1()
{
	parAgi -= 20000;
	activeSkill1 = false;
}

void Juggernaut::clearEffectSkill2()
{
	activeSkill2 = false;
}

void Juggernaut::clearEffectSkill3()
{

}

Soldier::Soldier(string _name) : Player(_name)
{
	sprite.setColor(Color::Yellow);
	parAgi = 16;
	parStr = 6;
	parInt = 8;

}

Soldier::Soldier(string _name, fstream &file) : Player(_name, file)
{
	sprite.setColor(Color::Yellow);
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
		cooldownSkill1.restart(seconds(40.f));
		effectSkill1.restart(seconds(1.f + parInt / 100.f));
		activeSkill1 = true;
	}
}

void Soldier::useSkill2() /*przyspieszenie*/
{
	if (cooldownSkill2.isExpired())
	{
		/*przyspiesza o stala wartosc + 0.1 za kazde 10 int*/
		speed += 3.f + parInt / 100.f;
		cooldownSkill2.restart(seconds(24.f));
		effectSkill2.restart(seconds(3.5f));
		activeSkill2 = true;
	}
}

void Soldier::useSkill3()
{
	if (cooldownSkill3.isExpired())
	{
		/*niewidzialnosc*/
		Color color = sprite.getColor();
		color.a -= 130;
		sprite.setColor(color);
		cooldownSkill3.restart(seconds(60.f));
		effectSkill3.restart(seconds(20.f)); /*Reminder - do zmiany, tylko dla testow*/
		activeSkill3 = true;
	}
}

void Soldier::clearEffectSkill1()
{
	activeSkill1 = false;
}

void Soldier::clearEffectSkill2()
{
	speed -= 3.3f;
	activeSkill2 = false;
}

void Soldier::clearEffectSkill3()
{
	Color color = sprite.getColor();
	color.a += 130;
	sprite.setColor(color);
	activeSkill3 = false;
}

Sentinel::Sentinel(string _name) : Player(_name)
{
	sprite.setColor(Color(140, 140, 255));
	parInt = 19;
	parStr = 5;
	parAgi = 6;
}

Sentinel::Sentinel(string _name, fstream &file) : Player(_name, file)
{
	sprite.setColor(Color(140, 140, 255));
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
		cooldownSkill1.restart(seconds(40.f));
	}
}

void Sentinel::useSkill2() /*zwiekszenie szansy na dodge*/
{
	if (cooldownSkill2.isExpired())
	{
		parAgi += static_cast<unsigned short>((0.33f + parInt / 100.f) * parAgi);
		cooldownSkill2.restart(seconds(35.f));
		effectSkill2.restart(seconds(7.f));
		activeSkill2 = true;
	}
}

void Sentinel::useSkill3()
{
	
}

void Sentinel::clearEffectSkill1()
{

}

void Sentinel::clearEffectSkill2()
{
	parAgi = static_cast<unsigned short>(100.f * parAgi / (133.f + parInt / 10.f)); /*Reminder - na razie dziala, ale nie wiem czy dla wszystkich wartosci bedzie poprawnie wracac*/
	activeSkill2 = false;
}

void Sentinel::clearEffectSkill3()
{

}
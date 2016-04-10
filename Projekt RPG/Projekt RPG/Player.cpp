#define _USE_MATH_DEFINES
#include "Player.h"
#include <Windows.h>
#include <cmath>

Player::Player()
{
	if (!texture.loadFromFile("placeholder.png")) /*Reminder - do zmiany sciezka*/
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
	name = "noname";
	parExp = 5;
	parLvl = 1;
	parExpForNextLevel = 83;
	parMaxHp = parHp = 100;
	parHp = 81;
	parStr = parAgi = parInt = 10; /*Reminder - pewnie tez do zmiany*/
}

Player::~Player()
{
	equipment.clearBackpack();
}

void Player::update(Vector2f mouse, Level *level) 
{
	TrapFountain* temp;
	Vector2f norm = mouse - sprite.getPosition();
	float rot = atan2(norm.y, norm.x); /*gdy przod playera jest na gorze tekstury, gdyby byl na dole to zamienic x z y*/
	rot = rot * 180.f / M_PI;
	rot += 90;
	sprite.setRotation(rot);

	if (temp = dynamic_cast<TrapFountain*>(level->getMap()[static_cast<int>(getPosition().y / 64)][static_cast<int>(getPosition().x / 64)])) parHp += temp->getHpChange();
	if (parHp > parMaxHp) parHp = parMaxHp;
	
	if (anim_clock.getElapsedTime() > seconds(0.04f))
	{
		if (status == STOP) return;
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
			sprite.move(-getMove());
			stop();
		}
		if (level->getMap()[static_cast<int>(getPosition().y / 64)][static_cast<int>((sprite.getGlobalBounds().left + sprite.getGlobalBounds().width - 15) / 64)]->isWall()) /*kolizja z kaflem po prawej*/
		{
			sprite.move(-getMove());
			stop();
		}
		if (level->getMap()[static_cast<int>((sprite.getGlobalBounds().top + 15) / 64)][static_cast<int>(getPosition().x / 64)]->isWall()) /*kolizja z kaflem z gory*/
		{
			sprite.move(-getMove());
			stop();
		}
		if (level->getMap()[static_cast<int>((sprite.getGlobalBounds().top + sprite.getGlobalBounds().height - 15) / 64)][static_cast<int>(getPosition().x / 64)]->isWall()) /*kolizja z kaflem z dolu*/
		{
			sprite.move(-getMove());
			stop();
		}
		anim_clock.restart();		
	}
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
	float vx = sin((rotation * M_PI) / 180.0f);
	float vy = -cos((rotation * M_PI) / 180.0f);

	return Vector2f(vx * speed, vy * speed);
}

Vector2f Player::getPosition()
{
	return sprite.getPosition();
}

void Player::setPosition(Tile::Coord coord)
{
	sprite.setPosition(coord.x * 64 + 32, coord.y * 64 + 32);
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

void Player::levelUp()
{
	double sum = 0.0;

	parExp -= parExpForNextLevel;
	++parLvl;
	for (double i = 1.0; i < parLvl + 1; ++i)
	{
		sum += floor(i + 300.0 * pow(2.0, i/7.0)); /*nie dziala, bo chyba pow cos zle zwraca*/
	}
	parExpForNextLevel = static_cast<int>(floor(sum/4.0));
}

Juggernaut::Juggernaut()
{

}

Juggernaut::~Juggernaut()
{

}

Soldier::Soldier()
{

}

Soldier::~Soldier()
{

}

Sentinel::Sentinel()
{

}

Sentinel::~Sentinel()
{

}
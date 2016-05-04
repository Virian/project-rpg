#define _USE_MATH_DEFINES
#include "Npc.h"
#include <Windows.h>
#include <cstdlib>
#include <cmath>

Npc::Npc(Tile::Coord spawnCoord) : spawnCoord(spawnCoord)
{
	if (!texture.loadFromFile("placeholder.png")) /*Reminder - do zmiany sciezka*/
	{
		MessageBox(NULL, "Textures not found!", "ERROR", NULL);
		return; /*powinien w ogole jakos te gre wywalic, co najmniej do menu*/
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 640, 64, 64)); /*Reminder - do zmiany, obecnie jest to tekstura playera*/
	sprite.setOrigin(32, 32);
	sprite.setPosition(64 * spawnCoord.x + 32, 64 * spawnCoord.y + 32);
}

Npc::~Npc()
{

}

void Npc::draw(RenderTarget &target, RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite);
}

FloatRect Npc::getBoundingBox()
{
	FloatRect box(sprite.getGlobalBounds());
	return box;
}

Vector2f Npc::getPosition()
{
	return sprite.getPosition();
}

void Npc::setPosition(Tile::Coord coord)
{
	sprite.setPosition(coord.x * 64 + 32, coord.y * 64 + 32);
}

Neutral::Neutral(Tile::Coord spawnCoord) : Npc(spawnCoord)
{

}

Neutral::~Neutral()
{

}

Enemy::Enemy(Tile::Coord spawnCoord) : Npc(spawnCoord)
{
	speed = 4.0f;
	frame = 0;
	anim_clock.restart();
	time.restart();
	attackInterval.restart();
	status = STOP;
	rot = rand() % 360;
	sprite.setRotation(rot);
	walkT = rand() % 500 + 1000;
	idleT = rand() % 5000 + 7000;

	parHp = parStr = parAgi = parInt = 10;
	experienceGiven = 20; /*Reminder - do zmiany*/
	alive = true;
	attackValue = rand() % 4 + 4;
	armorValue = rand() % 4 + 4;
	short random; /*bedzie w konstruktorze*/
	random = rand() % 2;
	if (random == 0) ranged = false;
	else ranged = true;
}

Enemy::~Enemy()
{

}

Enemy::Status Enemy::getStatus()
{
	return status;
}

void Enemy::update(Level* level, Vector2f playerPosition)
{	
	bool collision = false;
	/*ma przestawac atakowac, moze podazac*/
	if (status == ENGAGED)
	{
		rot = atan2f(playerPosition.y - sprite.getPosition().y, playerPosition.x - sprite.getPosition().x);
		rot = rot * 180.f / M_PI;
		rot += 90;
		sprite.setRotation(rot);
		collision = false;
		if (anim_clock.getElapsedTime() > seconds(0.04f))
		{
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
				collision = true;
				stop(collision);
			}
			if (sprite.getGlobalBounds().top + 15 < 0) /*gorna krawedz poziomu*/
			{
				sprite.move(-getMove());
				collision = true;
				stop(collision);
			}
			if (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width - 15 > level->getWidth() * 64) /*prawa krawedz poziomu*/
			{
				sprite.move(-getMove());
				collision = true;
				stop(collision);
			}
			if (sprite.getGlobalBounds().top + sprite.getGlobalBounds().height - 15 > level->getHeight() * 64) /*dolna krawedz poziomu*/
			{
				sprite.move(-getMove());
				collision = true;
				stop(collision);
			}
			if (level->getMap()[static_cast<int>(getPosition().y / 64)][static_cast<int>((sprite.getGlobalBounds().left + 15) / 64)]->isWall()) /*kolizja z kaflem po lewej*/
			{
				sprite.move(-getMove());
				collision = true;
				stop(collision);
			}
			if (level->getMap()[static_cast<int>(getPosition().y / 64)][static_cast<int>((sprite.getGlobalBounds().left + sprite.getGlobalBounds().width - 15) / 64)]->isWall()) /*kolizja z kaflem po prawej*/
			{
				sprite.move(-getMove());
				collision = true;
				stop(collision);
			}
			if (level->getMap()[static_cast<int>((sprite.getGlobalBounds().top + 15) / 64)][static_cast<int>(getPosition().x / 64)]->isWall()) /*kolizja z kaflem z gory*/
			{
				sprite.move(-getMove());
				collision = true;
				stop(collision);
			}
			if (level->getMap()[static_cast<int>((sprite.getGlobalBounds().top + sprite.getGlobalBounds().height - 15) / 64)][static_cast<int>(getPosition().x / 64)]->isWall()) /*kolizja z kaflem z dolu*/
			{
				sprite.move(-getMove());
				collision = true;
				stop(collision);
			}
			anim_clock.restart();
		}
	}
	else if (status == ATTACK)
	{
		rot = atan2f(playerPosition.y - sprite.getPosition().y, playerPosition.x - sprite.getPosition().x);
		rot = rot * 180.f / M_PI;
		rot += 90;
		sprite.setRotation(rot);
	}
	else if (time.getElapsedTime() > milliseconds(idleT))
	{		
		sprite.setRotation(rot);
		if (time.getElapsedTime() < milliseconds(idleT) + milliseconds(walkT))
		{
			status = WALK;
			collision = false;
			if (anim_clock.getElapsedTime() > seconds(0.04f))
			{
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
					collision = true;
					stop(collision);
				}
				if (sprite.getGlobalBounds().top + 15 < 0) /*gorna krawedz poziomu*/
				{
					sprite.move(-getMove());
					collision = true;
					stop(collision);
				}
				if (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width - 15 > level->getWidth() * 64) /*prawa krawedz poziomu*/
				{
					sprite.move(-getMove());
					collision = true;
					stop(collision);
				}
				if (sprite.getGlobalBounds().top + sprite.getGlobalBounds().height - 15 > level->getHeight() * 64) /*dolna krawedz poziomu*/
				{
					sprite.move(-getMove());
					collision = true;
					stop(collision);
				}
				if (level->getMap()[static_cast<int>(getPosition().y / 64)][static_cast<int>((sprite.getGlobalBounds().left + 15) / 64)]->isWall()) /*kolizja z kaflem po lewej*/
				{
					sprite.move(-getMove());
					collision = true;
					stop(collision);
				}
				if (level->getMap()[static_cast<int>(getPosition().y / 64)][static_cast<int>((sprite.getGlobalBounds().left + sprite.getGlobalBounds().width - 15) / 64)]->isWall()) /*kolizja z kaflem po prawej*/
				{
					sprite.move(-getMove());
					collision = true;
					stop(collision);
				}
				if (level->getMap()[static_cast<int>((sprite.getGlobalBounds().top + 15) / 64)][static_cast<int>(getPosition().x / 64)]->isWall()) /*kolizja z kaflem z gory*/
				{
					sprite.move(-getMove());
					collision = true;
					stop(collision);
				}
				if (level->getMap()[static_cast<int>((sprite.getGlobalBounds().top + sprite.getGlobalBounds().height - 15) / 64)][static_cast<int>(getPosition().x / 64)]->isWall()) /*kolizja z kaflem z dolu*/
				{
					sprite.move(-getMove());
					collision = true;
					stop(collision);
				}
				anim_clock.restart();
			}			
		}
		else
		{
			stop(collision);
		}
	}
}

Vector2f Enemy::getMove()
{
	float rotation = sprite.getRotation();
	float vx = sin((rotation * M_PI) / 180.0f);
	float vy = -cos((rotation * M_PI) / 180.0f);

	return Vector2f(vx * speed, vy * speed);
}

//void Enemy::walk()
//{
//	status = WALK;
//}

void Enemy::stop(bool collision)
{
	status = STOP;
	frame = 0;
	sprite.setTextureRect(IntRect(frame * 64, 640, 64, 64)); /*Reminder - ustawic odpowiednia teksture*/
	anim_clock.restart();
	time.restart();
	if (collision) rot = rot + 180; /*Reminder - mo¿na zmienic na widelki ale ryzyko zablokowania*/
	else rot = rand() % 360;
	walkT = rand() % 500 + 1000;
	idleT = rand() % 5000 + 7000;
}

void Enemy::engage()
{
	status = ENGAGED;
}

void Enemy::attack()
{
	status = ATTACK;
}

void Enemy::takeDamage(unsigned damage)
{
	parHp -= damage;
	if (parHp <= 0) alive = false;
}

unsigned short Enemy::getStr()
{
	return parStr;
}

unsigned short Enemy::getAgi()
{
	return parAgi;
}

unsigned short Enemy::getAttackValue()
{
	return attackValue;
}

unsigned short Enemy::getArmorValue()
{
	return armorValue;
}

bool Enemy::isRanged()
{
	return ranged;
}

bool Enemy::isAlive()
{
	return alive;
}

bool Enemy::isEngaged()
{
	if (status == ENGAGED) return true;
	else return false;
}

bool Enemy::isAttacking()
{
	if (status == ATTACK) return true;
	else return false;
}

Clock Enemy::getAttackInterval()
{
	return attackInterval;
}

void Enemy::restartAttackInterval()
{
	attackInterval.restart();
}

unsigned Enemy::getExperienceGiven()
{
	return experienceGiven;
}

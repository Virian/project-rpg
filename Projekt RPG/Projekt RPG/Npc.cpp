#define _USE_MATH_DEFINES
#include "Npc.h"
#include <Windows.h>
#include <cstdlib>
#include <cmath>

Npc::Npc(Tile::Coord spawnCoord) : spawnCoord(spawnCoord)
{
	texture.loadFromFile("images/tilesheet.png");
	sprite.setTexture(texture);	
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
	sprite.setPosition(coord.x * 64.f + 32.f, coord.y * 64.f + 32.f);
}

Neutral::Neutral(Tile::Coord spawnCoord) : Npc(spawnCoord)
{
	/*Reminder - dodac jakiegos npc...*/
}

Neutral::~Neutral()
{

}

Enemy::Enemy(Tile::Coord spawnCoord) : Npc(spawnCoord)
{
	walkFrame = 0;
	attackFrame = 0;
	walkAnimationClock.restart();
	attackAnimationClock.restart();
	time.restart();
	attackInterval.restart();
	status = STOP;
	rot = static_cast<float>(rand() % 360);
	sprite.setRotation(rot);
	walkT = rand() % 500 + 1000;
	idleT = rand() % 5000 + 7000;

	alive = true;
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
	IntRect tmpRect;
	/*ma przestawac atakowac, moze podazac*/
	if (status == ENGAGED)
	{
		rot = atan2f(playerPosition.y - sprite.getPosition().y, playerPosition.x - sprite.getPosition().x);
		rot = rot * 180.f / static_cast<float>(M_PI);
		rot += 90;
		sprite.setRotation(rot);
		collision = false;
		if (walkAnimationClock.getElapsedTime() > seconds(0.04f))
		{
			if (walkFrame < walkFrameCount) /*liczba klatek animacji - 1*/
				walkFrame++;
			else
				walkFrame = 0; /*animacja sie zapetla*/
			tmpRect = sprite.getTextureRect();
			tmpRect.left = walkFrame * 64;
			sprite.setTextureRect(tmpRect);
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
			walkAnimationClock.restart();
		}
	}
	else if (status == ATTACK)
	{
		rot = atan2f(playerPosition.y - sprite.getPosition().y, playerPosition.x - sprite.getPosition().x);
		rot = rot * 180.f / static_cast<float>(M_PI);
		rot += 90;
		sprite.setRotation(rot);
		if (((attackFrameCount > 0)) && (attackAnimationClock.getElapsedTime() > seconds(0.1f)))
		{
			if (attackFrame < attackFrameCount) /*liczba klatek animacji - 1*/
				++attackFrame;
			else
				attackFrame = 0; /*animacja sie zapetla*/
			tmpRect = sprite.getTextureRect();
			tmpRect.left = (attackFrame + walkFrameCount + 1) * 64;
			sprite.setTextureRect(tmpRect);
			attackAnimationClock.restart();
		}
	}
	else if (time.getElapsedTime() > milliseconds(idleT))
	{		
		sprite.setRotation(rot);
		if (time.getElapsedTime() < milliseconds(idleT) + milliseconds(walkT))
		{
			status = WALK;
			collision = false;
			if (walkAnimationClock.getElapsedTime() > seconds(0.04f))
			{
				if (walkFrame < walkFrameCount) /*liczba klatek animacji - 1*/
					walkFrame++;
				else
					walkFrame = 0; /*animacja sie zapetla*/
				tmpRect = sprite.getTextureRect();
				tmpRect.left = walkFrame * 64;
				sprite.setTextureRect(tmpRect);
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
				walkAnimationClock.restart();
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
	float vx = sin((rotation * static_cast<float>(M_PI)) / 180.0f);
	float vy = -cos((rotation * static_cast<float>(M_PI)) / 180.0f);

	return Vector2f(vx * speed, vy * speed);
}

void Enemy::stop(bool collision)
{
	IntRect tmpRect;
	
	status = STOP;
	walkFrame = 0;
	attackFrame = 0;
	tmpRect = sprite.getTextureRect();
	tmpRect.left = walkFrame * 64;
	sprite.setTextureRect(tmpRect);
	walkAnimationClock.restart();
	time.restart();
	if (collision) rot = rot + 180;
	else rot = static_cast<float>(rand() % 360);
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

short Enemy::getHp()
{
	return parHp;
}

short Enemy::getMaxHp()
{
	return parMaxHp;
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

Gunner::Gunner(Tile::Coord spawnCoord) : Enemy(spawnCoord)
{
	sprite.setTextureRect(IntRect(0, 640, 64, 64));
	sprite.setOrigin(32, 32);
	sprite.setPosition(64.f * spawnCoord.x + 32.f, 64.f * spawnCoord.y + 32.f);
	walkFrameCount = 7;
	attackFrameCount = 0;
	speed = 3.2f;
	ranged = true;
	parHp = parMaxHp = 10;
	attackValue = rand() % 5 + 5;
	armorValue = rand() % 2 + 3;
	experienceGiven = 10;
	parStr = 8;
	parAgi = 10;
}

Gunner::~Gunner()
{

}

Alien::Alien(Tile::Coord spawnCoord) : Enemy(spawnCoord)
{
	sprite.setTextureRect(IntRect(0, 704, 64, 64));
	sprite.setOrigin(32, 32);
	sprite.setPosition(64.f * spawnCoord.x + 32.f, 64.f * spawnCoord.y + 32.f);
	walkFrameCount = 7;
	attackFrameCount = 4;
	speed = 4.0f;
	ranged = false;
	parHp = parMaxHp = 18;
	attackValue = rand() % 3 + 2;
	armorValue = rand() % 3 + 4;
	experienceGiven = 8;
	parAgi = 6;
	parStr = 14;
}

Alien::~Alien()
{

}

Cannon::Cannon(Tile::Coord spawnCoord) : Enemy(spawnCoord)
{
	sprite.setTextureRect(IntRect(0, 576, 64, 64));
	sprite.setOrigin(32, 52);
	sprite.setPosition(64.f * spawnCoord.x + 32.f, 64.f * spawnCoord.y + 32.f);
	walkFrameCount = 0;
	attackFrameCount = 3;
	speed = .0f;
	ranged = true;
	parHp = parMaxHp = 28;
	attackValue = rand() % 7 + 8;
	armorValue = rand() % 5 + 6;
	experienceGiven = 24;
	parAgi = 8;
	parStr = 12;
}

Cannon::~Cannon()
{

}
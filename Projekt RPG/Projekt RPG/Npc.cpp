#define _USE_MATH_DEFINES
#include "Npc.h"
#include <Windows.h>
#include <cstdlib>

Npc::Npc(unsigned short spawnCoordX, unsigned short spawnCoordY) : spawnCoordX(spawnCoordX), spawnCoordY(spawnCoordY)
{
	if (!texture.loadFromFile("placeholder.png")) /*Reminder - do zmiany sciezka*/
	{
		MessageBox(NULL, "Textures not found!", "ERROR", NULL);
		return; /*powinien w ogole jakos te gre wywalic, co najmniej do menu*/
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 640, 64, 64)); /*Reminder - do zmiany, obecnie jest to tekstura playera*/
	sprite.setOrigin(32, 32);
	sprite.setPosition(64 * spawnCoordX + 32, 64 * spawnCoordY + 32);
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

void Npc::setPosition(unsigned short x, unsigned short y)
{
	sprite.setPosition(x * 64 + 32, y * 64 + 32);
}

Neutral::Neutral(unsigned short spawnCoordX, unsigned short spawnCoordY) : Npc(spawnCoordX, spawnCoordY)
{

}

Neutral::~Neutral()
{

}

Enemy::Enemy(unsigned short spawnCoordX, unsigned short spawnCoordY) : Npc(spawnCoordX, spawnCoordY)
{
	speed = 5.5f;
	frame = 0;
	anim_clock.restart();
	idleTime.restart();
	walkTime.restart();
	status = STOP;
	rot = rand() % 360;
	sprite.setRotation(rot);
	walkT = rand() % 500 + 1000;
	idleT = rand() % 5000 + 7000;

	par_hp = par_str = par_agi = par_int = 10;
}

Enemy::~Enemy()
{

}

Enemy::Status Enemy::getStatus()
{
	return status;
}

void Enemy::update(Level* level)
{	
	bool collision = false;
	
	if (idleTime.getElapsedTime() > milliseconds(idleT))
	{		
		sprite.setRotation(rot);
		if (walkTime.getElapsedTime() < milliseconds(idleT) + milliseconds(walkT))
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
	idleTime.restart();
	walkTime.restart();
	if (collision) rot = rot + 180; /*Reminder - mo¿na zmienic na widelki ale ryzyko zablokowania*/
	else rot = rand() % 360;
	walkT = rand() % 500 + 1000;
	idleT = rand() % 5000 + 7000;
}
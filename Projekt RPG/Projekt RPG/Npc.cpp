#define _USE_MATH_DEFINES
#include "Npc.h"
#include <Windows.h>
#include <cstdlib>
#include <cmath>

Npc::Npc(Tile::Coord spawnCoord) : spawnCoord(spawnCoord)
{
	/*wczytanie tekstury i zaladowanie jej do sprite'a*/
	texture.loadFromFile("images/tilesheet.png");
	sprite.setTexture(texture);	
}

Npc::~Npc()
{

}

void Npc::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite);
}

sf::FloatRect Npc::getBoundingBox()
{
	sf::FloatRect box(sprite.getGlobalBounds());
	return box;
}

sf::Vector2f Npc::getPosition()
{
	return sprite.getPosition();
}

void Npc::setPosition(Tile::Coord coord)
{
	sprite.setPosition(coord.x * 64.f + 32.f, coord.y * 64.f + 32.f); /*ustawienie pozycji jako koordynaty * szerokosc kafla + polowa szerokosci kafla - zeby ustawic idealnie na srodku*/
}

Neutral::Neutral(Tile::Coord spawnCoord) : Npc(spawnCoord)
{
	short npcLook = rand() % 2; /*losowy wyglad npc, obecnie dostepne sa 2*/
	short rot = rand() % 360; /*losowa rotacja*/
	sprite.setTextureRect(sf::IntRect(0 + npcLook * 64, 1344, 64, 64)); /*ustawienie tekstury*/
	sprite.setOrigin(32, 32);
	sprite.setPosition(64.f * spawnCoord.x + 32.f, 64.f * spawnCoord.y + 32.f); /*ustawienie na odpowiedniej pozycji*/
	sprite.setRotation(static_cast<float>(rot));
}

Neutral::~Neutral()
{

}

Enemy::Enemy(Tile::Coord spawnCoord) : Npc(spawnCoord)
{
	cursor = false; /*na poczatku przeciwnik na pewno nie zwiera kursora*/
	/*poczatki animacji*/
	walkFrame = 0;
	attackFrame = 0;
	/*wystartowanie zegarow*/
	walkAnimationClock.restart();
	attackAnimationClock.restart();
	time.restart();
	attackInterval.restart();
	/*na poczatku przeciwnik stoi*/
	status = STOP;
	/*ustawienie losowej rotacji*/
	rot = static_cast<float>(rand() % 360);
	sprite.setRotation(rot);
	/*wylosowanie czasu przez jaki przeciwnik ma stac i chodzic*/
	walkT = rand() % 500 + 1000;
	idleT = rand() % 5000 + 4000;
	
	alive = true; /*na poczatku na pewno jest zywy*/
}

Enemy::~Enemy()
{

}

Enemy::Status Enemy::getStatus()
{
	return status;
}

void Enemy::update(Level* level, sf::Vector2f playerPosition)
{	
	bool collision = false;
	sf::IntRect tmpRect;
	/*podazanie za graczem w probie zaatakowania*/
	if (status == ENGAGED)
	{
		/*wyliczenie odpowiedniej rotacji na podstawie pozycji gracza*/
		rot = atan2f(playerPosition.y - sprite.getPosition().y, playerPosition.x - sprite.getPosition().x);
		rot = rot * 180.f / static_cast<float>(M_PI);
		rot += 90;
		sprite.setRotation(rot);
		collision = false;
		if (walkAnimationClock.getElapsedTime() > sf::seconds(0.04f))
		{
			if (walkFrame < walkFrameCount) /*liczba klatek animacji - 1*/
				walkFrame++;
			else
				walkFrame = 0; /*animacja sie zapetla*/
			/*ustawienie klatki animacji*/
			tmpRect = sprite.getTextureRect();
			tmpRect.left = walkFrame * 64;
			sprite.setTextureRect(tmpRect);
			sprite.move(getMove()); /*proba przemieszczenia sprite'a*/
			/*wszystkie +15 i -15 sa tolerancja boundingboxa w przypadku kolizji*/
			/*jesli po drodze zajdzie kolizja, metoda stop() wywolywana jest z argumentem true oraz cofane jest przemieszczenie przeciwnika*/
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
			walkAnimationClock.restart(); /*reset clocka animacji chodzenia*/
		}
	}
	/*atakowanie gracza*/
	else if (status == ATTACK)
	{
		/*obrot przeciwnika w kierunku postaci*/
		rot = atan2f(playerPosition.y - sprite.getPosition().y, playerPosition.x - sprite.getPosition().x);
		rot = rot * 180.f / static_cast<float>(M_PI);
		rot += 90;
		sprite.setRotation(rot);
		if (((attackFrameCount > 0)) && (attackAnimationClock.getElapsedTime() > sf::seconds(0.1f))) /*animacja wystepuje tylko jesli sa dostepne jakies klatki animacji oraz zmiana klatki moze nastapic tylko co okreslony okres czasu*/
		{
			if (attackFrame < attackFrameCount) /*liczba klatek animacji - 1*/
				++attackFrame;
			else
				attackFrame = 0; /*animacja sie zapetla*/
			/*ustawienie klatki animacji*/
			tmpRect = sprite.getTextureRect();
			tmpRect.left = (attackFrame + walkFrameCount + 1) * 64;
			sprite.setTextureRect(tmpRect);
			attackAnimationClock.restart(); /*reset clocka animacji ataku*/
		}
	}
	/*gdy przeciwnik nie ma stycznosci z graczem*/
	else if (time.getElapsedTime() > sf::milliseconds(idleT))
	{		
		sprite.setRotation(rot); /*ustawienie uprzednio wyliczonej rotacji*/
		if (time.getElapsedTime() < sf::milliseconds(idleT) + sf::milliseconds(walkT))
		{
			status = WALK;
			collision = false;
			if (walkAnimationClock.getElapsedTime() > sf::seconds(0.04f))
			{
				if (walkFrame < walkFrameCount) /*liczba klatek animacji - 1*/
					walkFrame++;
				else
					walkFrame = 0; /*animacja sie zapetla*/
				/*ustawienie odpowiedniej klatki animacji*/
				tmpRect = sprite.getTextureRect();
				tmpRect.left = walkFrame * 64;
				sprite.setTextureRect(tmpRect);
				sprite.move(getMove()); /*proba przesuniecia sprite'a*/
				/*wszystkie +15 i -15 sa tolerancja boundingboxa w przypadku kolizji*/
				/*jesli po drodze zajdzie kolizja, metoda stop() wywolywana jest z argumentem true oraz cofane jest przemieszczenie przeciwnika*/
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
				walkAnimationClock.restart(); /*reset clocka animacji chodzenia*/
			}			
		}
		else
		{
			stop(collision); /*gdy czas sekwencji stoj-chodz przekroczyl sume czasow chodzenia (walkT) i stania (idleT) zostaje wywolana metoda stop() z argumentem false (poniewaz nie doszlo do kolizji)*/
		}
	}
}

sf::Vector2f Enemy::getMove()
{
	float rotation = sprite.getRotation();
	float vx = sin((rotation * static_cast<float>(M_PI)) / 180.0f); /*wyliczenie przemieszczenia na osi x*/
	float vy = -cos((rotation * static_cast<float>(M_PI)) / 180.0f); /*wyliczenie przemieszczenia na osi y*/

	return sf::Vector2f(vx * speed, vy * speed);
}

void Enemy::stop(bool collision)
{
	sf::IntRect tmpRect;
	
	status = STOP; /*zatrzymanie przeciwnika*/
	/*ustawienie poczatkowej klatki animacji chodzenia*/
	walkFrame = 0;
	attackFrame = 0;
	tmpRect = sprite.getTextureRect();
	tmpRect.left = walkFrame * 64;
	sprite.setTextureRect(tmpRect);
	/*zresetowanie clockow*/
	walkAnimationClock.restart();
	time.restart();
	if (collision) rot = rot + 180; /*jesli doszlo do kolizji, przeciwnik obraza sie o 180 stopni, dzieki czemu nie pozostaje zaklinowany*/
	else rot = static_cast<float>(rand() % 360); /*jesli kolizji nie bylo, obraca sie o dowolny kat*/
	/*losowanie nowych czasow dla sekwencji stoj-idz*/
	walkT = rand() % 500 + 1000;
	idleT = rand() % 5000 + 4000;
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
	if (parHp <= 0) alive = false; /*jesli hp spadnie do 0 lub nizej, przeciwnik umiera*/
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

sf::Clock Enemy::getAttackInterval()
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

bool Enemy::hasCursor()
{
	return cursor;
}

void Enemy::acquireCursor()
{
	cursor = true;
}

void Enemy::loseCursor()
{
	cursor = false;
}

Gunner::Gunner(Tile::Coord spawnCoord) : Enemy(spawnCoord)
{
	/*ustawienie sprite'a*/
	sprite.setTextureRect(sf::IntRect(0, 640, 64, 64));
	sprite.setOrigin(32, 32);
	sprite.setPosition(64.f * spawnCoord.x + 32.f, 64.f * spawnCoord.y + 32.f);
	walkFrameCount = 7;
	attackFrameCount = 0;
	/*ustawienie statystyk*/
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
	/*ustawienie sprite'a*/
	sprite.setTextureRect(sf::IntRect(0, 704, 64, 64));
	sprite.setOrigin(32, 32);
	sprite.setPosition(64.f * spawnCoord.x + 32.f, 64.f * spawnCoord.y + 32.f);
	walkFrameCount = 7;
	attackFrameCount = 4;
	/*ustawienie statystyk*/
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
	/*ustawienie sprite'a*/
	sprite.setTextureRect(sf::IntRect(0, 576, 64, 64));
	sprite.setOrigin(32, 52);
	sprite.setPosition(64.f * spawnCoord.x + 32.f, 64.f * spawnCoord.y + 32.f);
	walkFrameCount = 0;
	attackFrameCount = 3;
	/*ustawienie statystyk*/
	speed = .0f; /*przeciwnik stacjonarny*/
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
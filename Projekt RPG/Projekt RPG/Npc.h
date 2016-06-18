#pragma once
#include <SFML/Graphics.hpp>
#include "Level.h"

class Npc : public sf::Drawable, public sf::Transformable
{
public:
	Npc(Tile::Coord);
	virtual ~Npc();
	sf::FloatRect getBoundingBox();
	sf::Vector2f getPosition();
	void setPosition(Tile::Coord);
protected:
	sf::Sprite sprite;
	sf::Texture texture;
	Tile::Coord spawnCoord;
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};

class Neutral : public Npc
{
public:
	Neutral(Tile::Coord);
	~Neutral();
};

class Enemy : public Npc
{
public:
	Enemy(Tile::Coord);
	~Enemy();
	enum Status { STOP, WALK, ENGAGED, ATTACK };
	Status getStatus();
	void update(Level*, sf::Vector2f);
	sf::Vector2f getMove();
	void stop(bool);
	void engage();
	void attack();
	void takeDamage(unsigned);
	short getHp();
	short getMaxHp();
	unsigned short getStr();
	unsigned short getAgi();
	unsigned short getAttackValue();
	unsigned short getArmorValue();
	bool isRanged();
	bool isAlive();
	bool isEngaged();
	bool isAttacking();
	sf::Clock getAttackInterval();
	void restartAttackInterval();
	unsigned getExperienceGiven();
	bool hasCursor();
	void acquireCursor();
	void loseCursor();
protected:
	bool cursor;
	float speed;
	unsigned walkFrame;
	unsigned walkFrameCount;
	unsigned attackFrame;
	unsigned attackFrameCount;
	sf::Clock walkAnimationClock;
	sf::Clock attackAnimationClock;
	sf::Clock time;
	float rot;
	int idleT;
	int walkT;
	Status status;
	/*statystyki*/
	short parHp;
	short parMaxHp;
	unsigned short parStr;
	unsigned short parAgi;
	unsigned experienceGiven;
	unsigned short attackValue;
	unsigned short armorValue;
	bool ranged;
	bool alive;
	sf::Clock attackInterval;
};

class Gunner : public Enemy
{
public:
	Gunner(Tile::Coord);
	~Gunner();
};

class Alien : public Enemy
{
public:
	Alien(Tile::Coord);
	~Alien();
};

class Cannon : public Enemy
{
public:
	Cannon(Tile::Coord);
	~Cannon();
};
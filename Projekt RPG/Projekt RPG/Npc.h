#pragma once
#include <SFML/Graphics.hpp>
#include "Level.h"

using namespace sf;

class Npc : public Drawable, public Transformable
{
public:
	/*Npc(unsigned short, unsigned short);*/
	Npc(Tile::Coord);
	virtual ~Npc();
	FloatRect getBoundingBox();
	Vector2f getPosition();
	void setPosition(Tile::Coord);
protected:
	Sprite sprite;
	Texture texture;
	/*unsigned short spawnCoordX;
	unsigned short spawnCoordY;*/
	Tile::Coord spawnCoord;
	virtual void draw(RenderTarget&, RenderStates) const;
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
	Enemy(Tile::Coord); /*Reminder - trzeba bedzie dodac np parametr speed, str, int itp.*/
	~Enemy();
	enum Status { STOP, WALK, ENGAGED, ATTACK };
	Status getStatus();
	void update(Level*, Vector2f);
	Vector2f getMove();
	//void walk();
	void stop(bool);
	void engage();
	void attack();
	void takeDamage(unsigned);
	unsigned short getStr();
	unsigned short getAgi();
	unsigned short getAttackValue();
	unsigned short getArmorValue();
	bool isRanged();
	bool isAlive();
	bool isEngaged();
	bool isAttacking();
	Clock getAttackInterval();
	void restartAttackInterval();
	unsigned getExperienceGiven();
private:
	float speed;
	unsigned frame;
	Clock anim_clock;
	Clock time;
	float rot;
	int idleT;
	int walkT;
	Status status;
	/*statystyki*/
	short parHp;
	unsigned short parStr;
	unsigned short parAgi;
	unsigned short parInt; /*moze okazac sie niepotrzebny*/
	unsigned experienceGiven;
	unsigned short attackValue;
	unsigned short armorValue;
	bool ranged;
	bool alive;
	Clock attackInterval;
};
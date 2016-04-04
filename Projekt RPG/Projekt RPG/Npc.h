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
	enum Status { STOP, WALK };
	Status getStatus();
	void update(Level*);
	Vector2f getMove();
	//void walk();
	void stop(bool);
private:
	float speed;
	unsigned frame;
	Clock anim_clock;
	Clock idleTime;
	Clock walkTime;
	float rot;
	int idleT;
	int walkT;
	Status status;
	/*statystyki*/
	short par_hp;
	unsigned short par_str;
	unsigned short par_agi;
	unsigned short par_int;
};
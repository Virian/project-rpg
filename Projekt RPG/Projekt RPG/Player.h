#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Level.h"

using namespace sf;

class Player : public Drawable, Transformable
{
public:
	Player();
	virtual ~Player();
	void update(Vector2f, Level*);
	void walk();
	void stop();
	enum Status { STOP, WALK };
	Status getStatus();
	FloatRect getBoundingBox();
	Vector2f getMove();
	Vector2f getPosition();
	void setPosition(unsigned short, unsigned short);
	short getHp();
	short getMaxHp();
protected: /*dodac co najmniej str, dex, int*/
	Sprite sprite;
	Texture texture;
	Status status;
	float speed;
	unsigned frame;
	Clock anim_clock;
	virtual void draw(RenderTarget&, RenderStates) const;
	//Statystyki
	std::string name;
	short par_hp;
	short par_max_hp;
	unsigned short par_str;
	unsigned short par_agi;
	unsigned short par_int;
	//co z setName ??
};

class Juggernaut : public Player
{
public:	
	Juggernaut();
};

class Soldier : public Player
{
public:	
	Soldier();
};

class Sentinel : public Player
{
public:	
	Sentinel();
};
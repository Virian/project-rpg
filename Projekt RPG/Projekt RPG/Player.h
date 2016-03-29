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
	unsigned getExp();
	unsigned getExpForNextLevel();
	unsigned short getLvl();
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
	short parHp;
	short parMaxHp;
	unsigned parExp;
	unsigned parExpForNextLevel;
	unsigned short parLvl;
	unsigned short parStr;
	unsigned short parAgi;
	unsigned short parInt;
	//co z setName ??
};

class Juggernaut : public Player
{
public:	
	Juggernaut();
	~Juggernaut();
};

class Soldier : public Player
{
public:	
	Soldier();
	~Soldier();
};

class Sentinel : public Player
{
public:	
	Sentinel();
	~Sentinel();
};
#pragma once
#include <SFML/Graphics.hpp>
#include "Level.h"

using namespace sf;

class Npc : public Drawable, public Transformable
{
public:
	Npc();
	virtual ~Npc();
	FloatRect getBoundingBox();
	Vector2f getPosition();
protected:
	Sprite sprite;
	Texture texture;
	virtual void draw(RenderTarget&, RenderStates) const;
};

class Neutral : public Npc
{
public:
	Neutral();
};

class Enemy : public Npc
{
public:
	Enemy(); /*trzeba bedzie dodac np parametr speed, str, int itp.*/
	enum Status { STOP, WALK };
	Status getStatus();
	void update(Level*, float, int, int);
	Vector2f getMove();
	void walk();
	void stop();
private:
	float speed;
	unsigned frame;
	Clock anim_clock;
	Clock idleTime;
	Clock walkTime;
	Status status;
	/*statystyki*/
	short par_hp;
	unsigned short par_str;
	unsigned short par_agi;
	unsigned short par_int;
};
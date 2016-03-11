#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

class Player : public Drawable, Transformable
{
public:
	Player();
	~Player();
	void update(Vector2f);
	void walk();
	void stop();
	enum Status { STOP, WALK };
	Status getStatus();
	FloatRect getBoundingBox();
	Vector2f getSpeed();
	Vector2f getPosition();
	void setPosition(unsigned short, unsigned short);
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
	unsigned short par_str;
	unsigned short par_agi;
	unsigned short par_int;
	//co z setName ??
};

/*class Juggernaut : public Player
{

};

class Soldier : public Player
{

};

class Sentinel : public Player
{

};*/
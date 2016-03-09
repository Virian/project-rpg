#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player : public Drawable, Transformable
{
protected: /*dodac co najmniej str, dex, int*/
	enum Status { STOP, WALK };
	Sprite sprite;
	Texture texture;
	Status status;
	float speed;
	unsigned frame;
	Clock anim_clock;
	virtual void draw(RenderTarget&, RenderStates) const;
public:
	Player();
	~Player();
	void update(Vector2f);
	void walk();
	void stop();
	Status getStatus();
	FloatRect getBoundingBox();
	Vector2f getSpeed();
	Vector2f getPosition();
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
#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player : public Drawable, Transformable
{
public:
	Player();
	~Player();
	void update(Vector2f);
	void walk();
	void stop();
	//Vector2f getPosition();
protected:
	enum Status {STOP, WALK};
	Sprite sprite;
	Texture texture;
	Status status;
	float speed;
	unsigned frame;
	Clock anim_clock;
	virtual void draw(RenderTarget&, RenderStates) const;
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
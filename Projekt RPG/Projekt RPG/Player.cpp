#define _USE_MATH_DEFINES
#include "Player.h"
#include <Windows.h>
#include <cmath>

Player::Player()
{
	if (!texture.loadFromFile("ship.png"))
	{
		MessageBox(NULL, "Textures not found!", "ERROR", NULL);
		return;
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, 32, 32));
	sprite.setOrigin(16, 16);
	sprite.setPosition(1280 / 2, 720 / 2);

	speed = 4.5f;
	frame = 0;
	anim_clock.restart();
}

Player::~Player()
{

}

void Player::update(Vector2f mouse)
{
	Vector2f norm = mouse - sprite.getPosition();
	float rot = atan2(norm.y, norm.x); /*gdy przod playera jest na gorze tekstury, gdyby byl na dole to zamienic x z y*/
	rot = rot * 180.f / M_PI;
	rot += 90;
	sprite.setRotation(rot);
	
	if (anim_clock.getElapsedTime() > seconds(0.04f))
	{
		if (status == STOP) return;
		if (frame < 0) /*liczba klatek animacji*/
			frame++;
		else
			frame = 0; /*animacja sie zapetla*/
		sprite.setTextureRect(IntRect(frame * 32, 0, 32, 32));
		sprite.move(getSpeed());
		anim_clock.restart();
	}	
}

void Player::walk()
{
	status = WALK;
}

void Player::stop()
{
	status = STOP;
	frame = 0;
}

void Player::draw(RenderTarget &target, RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite);
}

Player::Status Player::getStatus()
{
	return status;
}

FloatRect Player::getBoundingBox()
{
	FloatRect box(sprite.getGlobalBounds());
	return box;
}

Vector2f Player::getSpeed()
{
	float rotation = sprite.getRotation();
	float vx = sin((rotation * M_PI) / 180.0f);
	float vy = -cos((rotation * M_PI) / 180.0f);

	return Vector2f(vx * speed, vy * speed);
}

Vector2f Player::getPosition()
{
	return sprite.getPosition();
}
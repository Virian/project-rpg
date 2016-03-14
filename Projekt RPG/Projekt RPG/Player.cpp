#define _USE_MATH_DEFINES
#include "Player.h"
#include <Windows.h>
#include <cmath>

Player::Player()
{
	if (!texture.loadFromFile("placeholder.png")) /*Reminder - do zmiany sciezka*/
	{
		MessageBox(NULL, "Textures not found!", "ERROR", NULL);
		return; /*powinien w ogole jakos te gre wywalic, co najmniej do menu*/
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 640, 64, 64));
	sprite.setOrigin(32, 32);
	sprite.setPosition(1280 / 2, 720 / 2);

	speed = 5.5f;
	frame = 0;
	anim_clock.restart();
	name = "noname";
	par_hp = par_str = par_agi = par_int = 10;
}

Player::~Player()
{

}

void Player::update(Vector2f mouse, Level *level) 
{
	Vector2f norm = mouse - sprite.getPosition();
	float rot = atan2(norm.y, norm.x); /*gdy przod playera jest na gorze tekstury, gdyby byl na dole to zamienic x z y*/
	rot = rot * 180.f / M_PI;
	rot += 90;
	sprite.setRotation(rot);
	
	if (anim_clock.getElapsedTime() > seconds(0.04f))
	{
		if (status == STOP) return;
		if (frame < 7) /*liczba klatek animacji - 1*/
			frame++;
		else
			frame = 0; /*animacja sie zapetla*/
		sprite.setTextureRect(IntRect(frame * 64, 640, 64, 64));
		sprite.move(getMove());
		/*wszystkie +15 i -15 sa tolerancja boundingboxa w przypadku kolizji*/
		if (sprite.getGlobalBounds().left + 15 < 0) /*lewa krawedz poziomu*/
		{
			sprite.move(-getMove());
			stop();
		}
		if (sprite.getGlobalBounds().top + 15 < 0) /*gorna krawedz poziomu*/
		{
			sprite.move(-getMove());
			stop();
		}
		if (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width - 15 > level->getWidth() * 64) /*prawa krawedz poziomu*/
		{
			sprite.move(-getMove());
			stop();
		}
		if (sprite.getGlobalBounds().top + sprite.getGlobalBounds().height - 15 > level->getHeight() * 64) /*dolna krawedz poziomu*/
		{
			sprite.move(-getMove());
			stop();
		}
		if (level->getMap()[static_cast<int>(getPosition().y / 64)][static_cast<int>((sprite.getGlobalBounds().left + 15) / 64)].isWall) /*kolizja z kaflem po lewej*/
		{
			sprite.move(-getMove());
			stop();
		}
		if (level->getMap()[static_cast<int>(getPosition().y / 64)][static_cast<int>((sprite.getGlobalBounds().left + sprite.getGlobalBounds().width - 15) / 64)].isWall) /*kolizja z kaflem po prawej*/
		{
			sprite.move(-getMove());
			stop();
		}
		if (level->getMap()[static_cast<int>((sprite.getGlobalBounds().top + 15) / 64)][static_cast<int>(getPosition().x / 64)].isWall) /*kolizja z kaflem z gory*/
		{
			sprite.move(-getMove());
			stop();
		}
		if (level->getMap()[static_cast<int>((sprite.getGlobalBounds().top + sprite.getGlobalBounds().height - 15) / 64)][static_cast<int>(getPosition().x / 64)].isWall) /*kolizja z kaflem z dolu*/
		{
			sprite.move(-getMove());
			stop();
		}
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
	sprite.setTextureRect(IntRect(frame * 64, 640, 64, 64));
	anim_clock.restart();
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

Vector2f Player::getMove()
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

void Player::setPosition(unsigned short x, unsigned short y)
{
	sprite.setPosition(x * 64 + 32, y * 64 + 32);
}

Juggernaut::Juggernaut()
{

}

Soldier::Soldier()
{

}

Sentinel::Sentinel()
{

}
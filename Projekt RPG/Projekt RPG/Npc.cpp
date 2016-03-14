#include "Npc.h"
#include <Windows.h>
#include <cstdlib>

Npc::Npc()
{
	if (!texture.loadFromFile("placeholder.png")) /*Reminder - do zmiany sciezka*/
	{
		MessageBox(NULL, "Textures not found!", "ERROR", NULL);
		return; /*powinien w ogole jakos te gre wywalic, co najmniej do menu*/
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 640, 64, 64)); /*Reminder - do zmiany, obecnie jest to tekstura playera*/
	sprite.setOrigin(32, 32);
	sprite.setPosition(1280 / 2, 720 / 2);
}

Npc::~Npc()
{

}

void Npc::draw(RenderTarget &target, RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite);
}

FloatRect Npc::getBoundingBox()
{
	FloatRect box(sprite.getGlobalBounds());
	return box;
}

Vector2f Npc::getPosition()
{
	return sprite.getPosition();
}

Neutral::Neutral()
{

}

Enemy::Enemy()
{
	speed = 5.5f;
	frame = 0;
	anim_clock.restart();

	par_hp = par_str = par_agi = par_int = 10;
}

Enemy::Status Enemy::getStatus()
{
	return status;
}

void Enemy::update()
{
	float rot = rand() % 360;
	sprite.setRotation(rot);
}
#include "Item.h"

Item::Item()
{
	texture.loadFromFile("placeholder.png");
	sprite.setTexture(texture);
}

Item::~Item()
{

}

void Item::draw(RenderTarget &target, RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite);
}

void Item::setPosition(Vector2f position)
{
	sprite.setPosition(position);
}

std::string Item::getName()
{
	return name;
}

short Item::getId()
{
	return id;
}

Weapon::Weapon()
{
	sprite.setTextureRect(IntRect(0, 128, 128, 128));
	name = "weapon";
	attackValue = rand() % 4 + 4;
}

Weapon::~Weapon()
{

}

unsigned short Weapon::getAttackValue()
{
	return attackValue;
}

Armor::Armor()
{
	sprite.setTextureRect(IntRect(0, 256, 128, 128));
	name = "armor";
	armorValue = rand() % 4 + 4;
}

Armor::~Armor()
{

}

unsigned short Armor::getArmorValue()
{
	return armorValue;
}

/*Potion::Potion()
{

}

Potion::~Potion()
{

}*/
#include "Item.h"

Item::Item()
{

}

Item::~Item()
{

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

}

Armor::~Armor()
{

}

unsigned short Armor::getArmorValue()
{
	return armorValue;
}

Potion::Potion()
{

}

Potion::~Potion()
{

}
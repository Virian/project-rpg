#include "Item.h"

Item::Item()
{
	texture.loadFromFile("images/tilesheet.png");
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

IntRect Item::getTextureRect()
{
	return sprite.getTextureRect();
}

Weapon::Weapon(bool _ranged, unsigned short playerLvl) : ranged(_ranged)
{
	short which, nameRand;

	nameRand = rand() % 4;
	switch (nameRand)
	{
	case 0:
		name = "Super ";
		break;
	case 1:
		name = "Tested ";
		break;
	case 2:
		name = "Worn-out ";
		break;
	case 3:
		name = "Quick ";
		break;
	}
	nameRand = rand() % 4;
	switch (nameRand)
	{
	case 0:
		name += "Accurate ";
		break;
	case 1:
		name += "Powerful ";
		break;
	case 2:
		name += "Vengeful ";
		break;
	case 3:
		name += "Plasma ";
		break;
	}
	if (_ranged)
	{
		which = rand() % 6;
		sprite.setTextureRect(IntRect(0 + which * 128, 128, 128, 128));
		if (which < 2) name += "Rifle";
		else if (which < 4) name += "Shotgun";
		else name += "Pistol";
	}
	else
	{
		which = rand() % 4;
		sprite.setTextureRect(IntRect(0 + which * 128, 0, 128, 128));
		if (which < 3) name += "Sword";
		else name += "Axe";
	}
	attackValue = rand() % static_cast<int>(4 + playerLvl / 4.0) + 4 + playerLvl;;
}

Weapon::Weapon(std::string _name, unsigned short _attackValue, bool _ranged, short which) : attackValue(_attackValue), ranged(_ranged)
{
	if (_ranged) sprite.setTextureRect(IntRect(0 + which * 128, 128, 128, 128));
	else sprite.setTextureRect(IntRect(0 + which * 128, 0, 128, 128));
	name = _name;
}

Weapon::~Weapon()
{

}

unsigned short Weapon::getAttackValue()
{
	return attackValue;
}

bool Weapon::isRanged()
{
	return ranged;
}

Armor::Armor(unsigned short playerLvl)
{
	short which;

	which = rand() % 5;
	sprite.setTextureRect(IntRect(0 + which * 128, 256, 128, 128));
	armorValue = rand() % static_cast<int>(4 + playerLvl / 4.0) + 4 + playerLvl;
	short nameRand = rand() % 5;
	switch (nameRand)
	{
	case 0:
		name = "Glass ";
		break;
	case 1:
		name = "Ultra ";
		break;
	case 2:
		name = "Hyper-electric ";
		break;
	case 3:
		name = "Rusty ";
		break;
	case 4:
		name = "Metal ";
		break;
	}
	nameRand = rand() % 3;
	switch (nameRand)
	{
	case 0:
		name += "Tough ";
		break;
	case 1:
		name += "Light ";
		break;
	case 2:
		name += "Heavy ";
		break;
	}
	name += "Armor";
}

Armor::Armor(std::string _name, unsigned short _armorValue, short which) : armorValue(_armorValue)
{
	sprite.setTextureRect(IntRect(0 + which * 128, 256, 128, 128));
	name = _name;
}

Armor::~Armor()
{

}

unsigned short Armor::getArmorValue()
{
	return armorValue;
}
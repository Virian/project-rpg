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

Weapon::Weapon(bool ranged) : ranged(ranged)
{
	sprite.setTextureRect(IntRect(0, 128, 128, 128));
	name = "weapon";
	attackValue = rand() % 4 + 4;
	/*short range = rand() % 2;
	if (range == 0) ranged = false;
	else ranged = true;*/
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

Armor::Armor()
{
	sprite.setTextureRect(IntRect(0, 256, 128, 128));
	//name = "armor";
	armorValue = rand() % 4 + 4;
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
#include "Item.h"

Item::Item()
{
	/*wczytanie tekstury*/
	texture.loadFromFile("images/tilesheet.png");
	sprite.setTexture(texture);
}

Item::~Item()
{

}

void Item::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite);
}

void Item::setPosition(sf::Vector2f position)
{
	sprite.setPosition(position);
}

std::string Item::getName()
{
	return name;
}

sf::IntRect Item::getTextureRect()
{
	return sprite.getTextureRect();
}

Weapon::Weapon(bool _ranged, unsigned short playerLvl) : ranged(_ranged)
{
	short which, nameRand;
	/*generator losowej nazwy broni*/
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
		sprite.setTextureRect(sf::IntRect(0 + which * 128, 128, 128, 128)); /*ustawienie losowego obrazka broni*/
		/*ostatni czlon nazwy zalezy od wylosowanego obrazka*/
		if (which < 2) name += "Rifle";
		else if (which < 4) name += "Shotgun";
		else name += "Pistol";
	}
	else
	{
		which = rand() % 4;
		sprite.setTextureRect(sf::IntRect(0 + which * 128, 0, 128, 128)); /*ustawienie losowego obrazka broni*/
		/*ostatni czlon nazwy zalezy od wylosowanego obrazka*/
		if (which < 3) name += "Sword";
		else name += "Axe";
	}
	attackValue = rand() % static_cast<int>(4 + playerLvl / 4.0) + 4 + playerLvl; /*losowanie wartosci ataku, zaleznej rowniez od poziomu gracza*/
}

Weapon::Weapon(std::string _name, unsigned short _attackValue, bool _ranged, short which) : attackValue(_attackValue), ranged(_ranged)
{
	/*ustawienie wszystkich wartosci oraz sprite'a na podstawie wartosci wczytanych z pliku*/
	if (_ranged) sprite.setTextureRect(sf::IntRect(0 + which * 128, 128, 128, 128));
	else sprite.setTextureRect(sf::IntRect(0 + which * 128, 0, 128, 128));
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
	sprite.setTextureRect(sf::IntRect(0 + which * 128, 256, 128, 128)); /*ustawienie losowego obrazka zbroi*/
	armorValue = rand() % static_cast<int>(4 + playerLvl / 4.0) + 4 + playerLvl; /*losowanie wartosci obrony, zaleznej rowniez od poziomu gracza*/
	/*generator losowej nazwy*/
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
	/*ustawienie wszystkich wartosci oraz sprite'a na podstawie wartosci wczytanych z pliku*/
	sprite.setTextureRect(sf::IntRect(0 + which * 128, 256, 128, 128));
	name = _name;
}

Armor::~Armor()
{

}

unsigned short Armor::getArmorValue()
{
	return armorValue;
}
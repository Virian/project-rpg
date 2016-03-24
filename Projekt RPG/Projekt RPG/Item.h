#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Item
{
protected:
	Sprite sprite;
	Texture texture;
public:
	Item();
	virtual ~Item();
};

class Weapon : public Item
{
private:
	unsigned short attackValue;
public:
	Weapon();
	~Weapon();
	unsigned short getAttackValue();
};

class Armor : public Item
{
private:
	unsigned short armorValue;
public:
	Armor();
	~Armor();
	unsigned short getArmorValue();
};

class Potion : public Item
{
public:
	Potion();
	~Potion();
};
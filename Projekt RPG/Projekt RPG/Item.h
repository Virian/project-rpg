#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

class Item
{
protected:
	Sprite sprite;
	Texture texture;
	std::string name;
	short id;
public:
	Item();
	virtual ~Item();
	std::string getName();
	short getId();
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

/*Reminder - potki moga sie na dobra sprawe nie przydac*/
class Potion : public Item
{
public:
	Potion();
	~Potion();
};
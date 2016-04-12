#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

class Item : public Drawable, public Transformable
{
protected:
	Sprite sprite;
	Texture texture;
	std::string name;
	short id;
	virtual void draw(RenderTarget&, RenderStates) const;
public:
	Item();
	virtual ~Item();
	void setPosition(Vector2f);
	std::string getName();
	short getId();
};

class Weapon : public Item
{
private:
	unsigned short attackValue;
	bool ranged;
public:
	Weapon(bool);
	~Weapon();
	unsigned short getAttackValue();
	bool isRanged();
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
/*class Potion : public Item
{
public:
	Potion();
	~Potion();
};*/
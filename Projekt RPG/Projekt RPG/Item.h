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
	Weapon(std::string, unsigned short, bool);
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
	Armor(std::string, unsigned short);
	~Armor();
	unsigned short getArmorValue();
};
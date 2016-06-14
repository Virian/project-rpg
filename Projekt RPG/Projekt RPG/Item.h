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
	virtual void draw(RenderTarget&, RenderStates) const;
public:
	Item();
	virtual ~Item();
	void setPosition(Vector2f);
	std::string getName();
	IntRect getTextureRect();
};

class Weapon : public Item
{
private:
	unsigned short attackValue;
	bool ranged;
public:
	Weapon(bool, unsigned short);
	Weapon(std::string, unsigned short, bool, short);
	~Weapon();
	unsigned short getAttackValue();
	bool isRanged();
};

class Armor : public Item
{
private:
	unsigned short armorValue;
public:
	Armor(unsigned short);
	Armor(std::string, unsigned short, short);
	~Armor();
	unsigned short getArmorValue();
};
#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Item : public sf::Drawable, public sf::Transformable
{
protected:
	sf::Sprite sprite;
	sf::Texture texture;
	std::string name;
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
public:
	Item();
	virtual ~Item();
	void setPosition(sf::Vector2f);
	std::string getName();
	sf::IntRect getTextureRect();
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
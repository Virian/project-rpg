#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Item : public sf::Drawable, public sf::Transformable
{
/*klasa bazowa*/
protected:
	sf::Sprite sprite;
	sf::Texture texture;
	std::string name;									/*nazwa przedmiotu*/
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
public:
	Item();
	virtual ~Item();
	void setPosition(sf::Vector2f);						/*ustawia spirte'a na zadanej pozycji*/
	std::string getName();								/*zwraca nazwe przemiotu*/
	sf::IntRect getTextureRect();						/*zwraca prostokat w teksturze, z ktorego korzysta sprite*/
};

class Weapon : public Item
{
private:
	unsigned short attackValue;							/*wartosc ataku broni*/
	bool ranged;										/*przyjmuje true gdy bron jest dystansowa*/
public:
	Weapon(bool, unsigned short);						/*konstruktor nowej, losowej broni*/
	Weapon(std::string, unsigned short, bool, short);	/*konstruktor konkretnej broni w czasie wczytywania*/
	~Weapon();
	unsigned short getAttackValue();					/*zwraca wartosc ataku*/
	bool isRanged();									/*zwraca true jesli bron jest dystansowa*/
};

class Armor : public Item
{
private:
	unsigned short armorValue;							/*wartosc obrony*/
public:
	Armor(unsigned short);								/*konstruktor nowej, losowej zbroi*/
	Armor(std::string, unsigned short, short);			/*konstruktor konkretnej zbroi w czasie wczytywania*/
	~Armor();
	unsigned short getArmorValue();						/*zwraca wartosc obrony*/
};
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Level.h"
#include "Equipment.h"

using namespace sf;

class Player : public Drawable, Transformable
{
public:
	Player(string);
	virtual ~Player();
	short update(Vector2f, Level*);
	void walk();
	void stop();
	void attack();
	enum Status { STOP, WALK, ATTACK };
	Status getStatus();
	FloatRect getBoundingBox();
	Vector2f getMove();
	Vector2f getPosition();
	void setPosition(Tile::Coord);
	std::string getName();
	virtual std::string getClassName() = 0;
	Equipment getEquipment();
	short getHp();
	short getMaxHp();
	unsigned getExp();
	unsigned getExpForNextLevel();
	unsigned short getLvl();
	unsigned short getStr();
	unsigned short getAgi();
	unsigned short getInt();
	void levelUp();
	void deleteItem(short);
	void addItem(Item*);
	void swapActiveItem(short);
	void usePotion();
	void takeDamage(unsigned);
	Clock getAttackInterval();
	void restartAttackInterval();
	void increaseExperience(unsigned);
	/*skille*/
	virtual void useSkill1() = 0;
	virtual void useSkill2() = 0;
	virtual void useSkill3() = 0;
protected:
	Sprite sprite;
	Texture texture;
	Status status;
	float speed;
	unsigned frame;
	Clock anim_clock;
	virtual void draw(RenderTarget&, RenderStates) const;
	//Statystyki
	std::string name;
	Equipment equipment;
	short parHp;
	short parMaxHp;
	unsigned parExp;
	unsigned parExpForNextLevel;
	unsigned short parLvl;
	unsigned short parStr;
	unsigned short parAgi;
	unsigned short parInt;
	Clock attackInterval;
};

class Juggernaut : public Player
{
public:	
	Juggernaut(string);
	~Juggernaut();
	std::string getClassName();
	void useSkill1();
	void useSkill2();
	void useSkill3();
};

class Soldier : public Player
{
public:	
	Soldier(string);
	~Soldier();
	std::string getClassName();
	void useSkill1();
	void useSkill2();
	void useSkill3();
};

class Sentinel : public Player
{
public:	
	Sentinel(string);
	~Sentinel();
	std::string getClassName();
	void useSkill1();
	void useSkill2();
	void useSkill3();
};
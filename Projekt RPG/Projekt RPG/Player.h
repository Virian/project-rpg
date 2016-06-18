#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include "Level.h"
#include "Equipment.h"
#include "Time.h"

class Player : public sf::Drawable, sf::Transformable
{
public:
	Player(std::string);
	Player(std::string, std::fstream&);
	virtual ~Player();
	short update(sf::Vector2f, Level*);
	void walk();
	void stop();
	void attack();
	enum Status { STOP, WALK, ATTACK };
	Status getStatus();
	sf::FloatRect getBoundingBox();
	sf::Vector2f getMove();
	sf::Vector2f getPosition();
	void setPosition(Tile::Coord);
	std::string getName();
	virtual std::string getClassName() = 0;
	Equipment* getEquipment();
	short getHp();
	short getMaxHp();
	unsigned short getPointsToSpend();
	unsigned getExp();
	unsigned getExpForNextLevel();
	unsigned short getLvl();
	unsigned short getStr();
	unsigned short getAgi();
	unsigned short getInt();
	void increaseStr();
	void increaseAgi();
	void increaseInt();
	void levelUp();
	void deleteItem(short);
	void addItem(Item*);
	void swapActiveItem(short);
	void usePotion();
	void takeDamage(unsigned);
	sf::Clock getAttackInterval();
	void restartAttackInterval();
	void increaseExperience(unsigned);
	void pauseTimers();
	void unpauseTimers();
	void resetTimers();
	/*skille*/
	bool isActiveSkill1();
	bool isActiveSkill2();
	bool isActiveSkill3();
	virtual void useSkill1() = 0;
	virtual void useSkill2() = 0;
	virtual void useSkill3() = 0;
	virtual void clearEffectSkill1() = 0;
	virtual void clearEffectSkill2() = 0;
	virtual void clearEffectSkill3() = 0;
	virtual float getRatioSkill1() = 0;
	virtual float getRatioSkill2() = 0;
	virtual float getRatioSkill3() = 0;	
protected:
	sf::Sprite sprite;
	sf::Texture texture;
	Status status;
	float speed;
	unsigned walkFrame;
	unsigned attackFrame;
	unsigned walkFrameCount;
	unsigned attackFrameCount;
	sf::Clock walkAnimationClock;
	sf::Clock attackAnimationClock;
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
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
	unsigned short parPointsToSpend;
	sf::Clock attackInterval;
	bool activeSkill1;
	bool activeSkill2;
	bool activeSkill3;
	Timer cooldownSkill1;
	Timer cooldownSkill2;
	Timer cooldownSkill3;
	Timer effectSkill1;
	Timer effectSkill2;
	Timer effectSkill3;
};

class Juggernaut : public Player
{
public:	
	Juggernaut(std::string);
	Juggernaut(std::string, std::fstream&);
	~Juggernaut();
	std::string getClassName();
	void useSkill1();
	void useSkill2();
	void useSkill3();
	void clearEffectSkill1();
	void clearEffectSkill2();
	void clearEffectSkill3();
	float getRatioSkill1();
	float getRatioSkill2();
	float getRatioSkill3();
};

class Soldier : public Player
{
public:	
	Soldier(std::string);
	Soldier(std::string, std::fstream&);
	~Soldier();
	std::string getClassName();
	void useSkill1();
	void useSkill2();
	void useSkill3();
	void clearEffectSkill1();
	void clearEffectSkill2();
	void clearEffectSkill3();
	float getRatioSkill1();
	float getRatioSkill2();
	float getRatioSkill3();
};

class Sentinel : public Player
{
public:	
	Sentinel(std::string);
	Sentinel(std::string, std::fstream&);
	~Sentinel();
	std::string getClassName();
	void useSkill1();
	void useSkill2();
	void useSkill3();
	void clearEffectSkill1();
	void clearEffectSkill2();
	void clearEffectSkill3();
	float getRatioSkill1();
	float getRatioSkill2();
	float getRatioSkill3();
};
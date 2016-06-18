#pragma once
#include <SFML/Graphics.hpp>
#include "Level.h"

class Npc : public sf::Drawable, public sf::Transformable
/*klasa bazowa*/
{
public:
	Npc(Tile::Coord);
	virtual ~Npc();
	sf::FloatRect getBoundingBox();					/*zwraca bounding boxa npc*/
	sf::Vector2f getPosition();						/*zwraca pozycje npc*/
	void setPosition(Tile::Coord);
protected:
	sf::Sprite sprite;
	sf::Texture texture;
	Tile::Coord spawnCoord;							/*koordynaty na ktorych ma sie pojawic npc*/
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;	/*metoda pozwalajaca na rysowanie*/
};

class Neutral : public Npc
/*npc ktorzy jedynie stoja*/
/*wraz z rozwojem gry podejscie do nich mogloby pozwalac na interakcje z nimi*/
{
public:
	Neutral(Tile::Coord);
	~Neutral();
};

class Enemy : public Npc
/*przeciwnicy z ktorymi gracz walczy*/
{
public:
	Enemy(Tile::Coord);
	~Enemy();
	enum Status { STOP, WALK, ENGAGED, ATTACK };	/*stan przeciwnika*/
	Status getStatus();								/*zwraca stan przeciwnika*/
	void update(Level*, sf::Vector2f);				/*aktualizuje przeciwnika*/
	sf::Vector2f getMove();							/*zwraca pozycje przeciwnika po nastepnym ruchu*/
	void stop(bool);								/*zatrzymuje przeciwnika w zaleznosci od tego czy byla kolizja czy nie*/
	void engage();									/*staraj sie zaatakowac gracza, podazaj za nim*/
	void attack();									/*atakuj*/
	void takeDamage(unsigned);						/*zmniejsza hp*/
	short getHp();									/*zwraca obecna ilosc hp*/
	short getMaxHp();								/*zwraca maksymalna wartosc hp*/
	unsigned short getStr();						/*zwraca sile*/
	unsigned short getAgi();						/*zwraca zrecznosc*/
	unsigned short getAttackValue();				/*zwraca wartosc ataku*/
	unsigned short getArmorValue();					/*zwraca wartosc obrony*/
	bool isRanged();								/*zwraca true jesli przeciwnik jest dystansowy*/
	bool isAlive();									/*zwraca true jesli przeciwnik zyje*/
	bool isEngaged();								/*zwraca true jesli stan przeciwnika to ENGAGED*/
	bool isAttacking();								/*zwraca true jesli stan przeciwnika to ATTACK*/
	sf::Clock getAttackInterval();					/*zwraca czas od ostatniego ataku*/
	void restartAttackInterval();					/*resetuje clocka odpowiadajacego za czas od ostatniego ataku*/
	unsigned getExperienceGiven();					/*zwraca wartosc doswiadczenia jaka daje dany przeciwnik*/
	bool hasCursor();								/*zwraca true jesli kursor znajduje sie w bounding boxie przeciwnika*/
	void acquireCursor();							/*gdy kursor znajdzie sie w bounding boxie przeciwnika, ustawia pole cursor na true*/
	void loseCursor();								/*gdy kursor wyjdzie z bounding boxa przeciwnika, ustawia pole cursor na false*/
protected:
	bool cursor;									/*przyjmuje wartosc true gdy kursor znajduje sie nad przeciwnikiem*/
	float speed;									/*szybkosc*/
	unsigned walkFrame;								/*klatka animacji chodzenia*/
	unsigned walkFrameCount;						/*liczba klatek animacji chodzenia - 1*/
	unsigned attackFrame;							/*klatka animacji ataku*/
	unsigned attackFrameCount;						/*liczba klatek animacji ataku - 1*/
	sf::Clock walkAnimationClock;					/*zegar liczacy czas od ostatniej zmiany klatki animacji chodzenia*/
	sf::Clock attackAnimationClock;					/*zegar liczacy czas od ostatniej zmiany klatki animacji ataku*/
	sf::Clock time;									/*zegar liczacy czas sekwencji stoj-chodz*/
	float rot;										/*rotacja przeciwnika*/
	int idleT;										/*czas w milisekundach przez jaki przeciwik ma stac i nic nie robic*/
	int walkT;										/*czas w milisekundach przez jaki przeciwik ma chodzic*/
	Status status;									/*stan przeciwnika*/
	/*statystyki*/
	short parHp;									/*obecna ilosc hp*/
	short parMaxHp;									/*maksymalna ilosc hp*/
	unsigned short parStr;							/*sila*/
	unsigned short parAgi;							/*zrecznosc*/
	unsigned experienceGiven;						/*ilosc dawanego doswiadczenia*/
	unsigned short attackValue;						/*wartosc ataku*/
	unsigned short armorValue;						/*wartosc obrony*/
	bool ranged;									/*przyjmuje true gdy atakuje z dystansu*/
	bool alive;										/*przyjmuje true gdy obecna ilosc hp jest wieksza od 0*/
	sf::Clock attackInterval;						/*zegar liczacy czas od ostatniego ataku*/
};

/*pochodne klasy roznych typow przeciwnikow*/
class Gunner : public Enemy
{
public:
	Gunner(Tile::Coord);
	~Gunner();
};

class Alien : public Enemy
{
public:
	Alien(Tile::Coord);
	~Alien();
};

class Cannon : public Enemy
{
public:
	Cannon(Tile::Coord);
	~Cannon();
};
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include "Level.h"
#include "Equipment.h"
#include "Time.h"

class Player : public sf::Drawable, sf::Transformable
/*abstrakcyjna klasa bazowa*/
{
public:
	Player(std::string);						/*konstruktor gdy tworzymy nowa gre*/
	Player(std::string, std::fstream&);			/*konstruktor gdy wczytujemy gre*/
	virtual ~Player();
	short update(sf::Vector2f, Level*);			/*aktualizacja gracza*/
	void walk();								/*idz*/
	void stop();								/*zatrzymaj sie*/
	void attack();								/*atakuj*/
	enum Status { STOP, WALK, ATTACK };			/*mozliwe stany gracza*/
	Status getStatus();							/*zwraca status*/
	sf::FloatRect getBoundingBox();				/*zwraca bounding boxa gracza*/
	sf::Vector2f getMove();						/*zwraca miejsce w ktorym ma sie pojawic gracz w nastepnej klatce*/
	sf::Vector2f getPosition();					/*zwraca pozycje gracza*/
	void setPosition(Tile::Coord);				/*ustawia pozycje gracza na zadanych koordynatach*/
	std::string getName();						/*zwraca imie postaci*/
	virtual std::string getClassName() = 0;		/*zwraca nazwe klasy*/
	Equipment* getEquipment();					/*zwraca ekwipunek gracza*/
	short getHp();								/*zwraca obecne hp gracza*/
	short getMaxHp();							/*zwraca maksymalne hp gracza*/
	unsigned short getPointsToSpend();			/*zwraca ile punktow gracz moze wydac na statystyki*/
	unsigned getExp();							/*zwraca ilosc punktow doswiadczenia gracza*/
	unsigned getExpForNextLevel();				/*zwraca ilosc potrzebnych punktow doswiadczenia by awansowac na nastepny poziom*/
	unsigned short getLvl();					/*zwraca poziom gracza*/
	unsigned short getStr();					/*zwraca wartosc sily gracza*/
	unsigned short getAgi();					/*zwraca wartosc zrecznosci gracza*/
	unsigned short getInt();					/*zwraca wartosc inteligencji gracza*/
	void increaseStr();							/*zwieksza sile o 1, zmniejsza o 1 ilosc punktow do wydania*/
	void increaseAgi();							/*zwieksza zrecznosc o 1, zmniejsza o 1 ilosc punktow do wydania*/
	void increaseInt();							/*zwieksza inteligencje o 1, zmniejsza o 1 ilosc punktow do wydania*/
	void levelUp();								/*zwieksza poziom o 1, liczy ilosc punktow doswiadczenia potrzebnych na nastepny poziom i zwieksza ilosc punktow do wydania o 5*/
	void deleteItem(short);						/*usuwa z ekwipunku przedmiot na zadanej pozycji*/
	void addItem(Item*);						/*dodaje do ekwipunku przedmiot*/
	void swapActiveItem(short);					/*zamienia zadany przedmiot z aktywnym lub zdejmuje aktywny przedmiot do plecaka*/
	void usePotion();							/*leczy przy uzyciu mikstury zycia*/
	void takeDamage(unsigned);					/*odejmuje zadana ilosc punktow zycia*/
	sf::Clock getAttackInterval();				/*zwraca ile czasu mienlo od ostatniego ataku*/
	void restartAttackInterval();				/*resetuje clocka liczacego ile czasu minelo od ostatniego ataku*/
	void increaseExperience(unsigned);			/*zwieksza ilosc punktow doswiadczenia o zadana ilosc*/
	void pauseTimers();							/*pauzuje wszystkie timery jakie posiada gracz*/
	void unpauseTimers();						/*odpauzowuje wszystkie timery jakie posiada gracz*/
	void resetTimers();							/*zeruje wszystkie timery jakie posiada gracz*/
	/*skille*/
	bool isActiveSkill1();						/*zwraca true, jesli aktywny jest pierwsza umiejetnosc gracza*/
	bool isActiveSkill2();						/*zwraca true, jesli aktywna jest druga umiejetnosc gracza*/
	bool isActiveSkill3();						/*zwraca true, jesli aktywna jest trzecia umiejetnosc gracza*/
	virtual void useSkill1() = 0;				/*uzycie pierwszej umiejetnosc*/
	virtual void useSkill2() = 0;				/*uzycie drugiej umiejetnosci*/
	virtual void useSkill3() = 0;				/*uzycie trzeciej umiejetnosci*/
	virtual void clearEffectSkill1() = 0;		/*zakonczenie dzialania pierwszej umiejetnosci*/
	virtual void clearEffectSkill2() = 0;		/*zakonczenie dzialania drugiej umiejetnosci*/
	virtual void clearEffectSkill3() = 0;		/*zakonczenie dzialania trzeciej umiejetnosci*/
	virtual float getRatioSkill1() = 0;			/*zwraca stosunek czasu brakujacego do zaladowania pierwszej umiejetnosci do czasu calkowitego ladowania pierwszej umiejetnosci*/
	virtual float getRatioSkill2() = 0;			/*zwraca stosunek czasu brakujacego do zaladowania drugiej umiejetnosci do czasu calkowitego ladowania drugiej umiejetnosci*/
	virtual float getRatioSkill3() = 0;			/*zwraca stosunek czasu brakujacego do zaladowania trzeciej umiejetnosci do czasu calkowitego ladowania trzeciej umiejetnosci*/
protected:
	sf::Sprite sprite;
	sf::Texture texture;
	Status status;								/*stan w jakim obecnie jest postac*/
	float speed;								/*szybkosc postaci*/
	unsigned walkFrame;							/*obecna klatka animacji chodzenia*/
	unsigned attackFrame;						/*obecna klatka animacji ataku*/
	unsigned walkFrameCount;					/*ilosc klatek ruchu - 1*/
	unsigned attackFrameCount;					/*ilosc klatek ataku - 1*/
	sf::Clock walkAnimationClock;				/*czas jaki uplynal od ostatniej klatki chodzenia*/
	sf::Clock attackAnimationClock;				/*czas jaki uplynal od ostatniej klatki ataku*/
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;	/*metoda pozwalajaca na rysowanie sprite'a*/
	/*statystyki*/
	std::string name;							/*imie postaci*/
	Equipment equipment;						/*ekwipunek*/
	short parHp;								/*obecna ilosc hp*/
	short parMaxHp;								/*maksymalna wartosc hp*/
	unsigned parExp;							/*ilosc posiadanych punktow doswiadczenia*/
	unsigned parExpForNextLevel;				/*ilosc punktow doswiadczenia potrzebnych do awansowania*/
	unsigned short parLvl;						/*poziom postaci*/
	unsigned short parStr;						/*sila*/
	unsigned short parAgi;						/*zrecznosc*/
	unsigned short parInt;						/*inteligencja*/
	unsigned short parPointsToSpend;			/*punkty do wydania na statystyki*/
	sf::Clock attackInterval;					/*czas jaki uplynal od ostatniego ataku*/
	bool activeSkill1;							/*czy jest aktywna pierwsza umiejetnosc*/
	bool activeSkill2;							/*czy jest aktywna druga umiejetnosc*/
	bool activeSkill3;							/*czy jest aktywna trzecia umiejetnosc*/
	Timer cooldownSkill1;						/*timer odliczajacy ladowanie sie pierwszej umiejetnosci*/
	Timer cooldownSkill2;						/*timer odliczajacy ladowanie sie drugiej umiejetnosci*/
	Timer cooldownSkill3;						/*timer odliczajacy ladowanie sie trzeciej umiejetnosci*/
	Timer effectSkill1;							/*timer odliczajacy czas dzialania pierwszej umiejetnosci*/
	Timer effectSkill2;							/*timer odliczajacy czas dzialania drugiej umiejetnosci*/
	Timer effectSkill3;							/*timer odliczajacy czas dzialania trzeciej umiejetnosci*/
};

class Juggernaut : public Player
{
public:	
	Juggernaut(std::string);					/*konstruktor gdy tworzymy nowa gre*/
	Juggernaut(std::string, std::fstream&);		/*konstruktor gdy wczytujemy gre*/
	~Juggernaut();
	/*przeslanianie metod*/
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
	Soldier(std::string);						/*konstruktor gdy tworzymy nowa gre*/
	Soldier(std::string, std::fstream&);		/*konstruktor gdy wczytujemy gre*/
	~Soldier();
	/*przeslanianie metod*/
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
	Sentinel(std::string);						/*konstruktor gdy tworzymy nowa gre*/
	Sentinel(std::string, std::fstream&);		/*konstruktor gdy wczytujemy gre*/
	~Sentinel();
	/*przeslanianie metod*/
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
#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Gui : public sf::Drawable, sf::Transformable
{
public:
	struct TextDamage {													/*struktura wyswietlanych zadanych/wyleczonych obrazen*/
		sf::Text text;
		sf::Clock lifeTime;												/*czas od powstania*/
		sf::Clock tick;													/*czas od ostatniej aktualizacji*/
	};
	struct HpBar {														/*struktura sluzaca do wyswietlania paska hp ponad przeciwnikami*/
		sf::Vector2f characterPosition;									/*pozycja przeciwnika do ktorego nalezy dany pasek*/
		sf::RectangleShape currentHp;									/*pasek obecnego hp*/
		sf::RectangleShape missingHp;									/*pasek brakujacego hp*/
		HpBar();														/*konstruktor*/
	};
	Gui();
	~Gui();
	void setSkillPictures(std::string);									/*ustawia obrazki umiejetnosci w zaleznosci od klasy postaci*/
	void drawScreen(sf::RenderWindow&, Player*);						/*rysuje "stala" czesc HUDa - umiejetnosci, doswiadczenie, hp, zadawane obrazenia, paski hp, licznik mikstur*/
	void drawPauseMenu(sf::RenderWindow&);								/*rysuje menu pauzy*/
	void drawEquipment(sf::RenderWindow&, Player*, short);				/*rysuje ekwipunek*/
	void drawDeathScreen(sf::RenderWindow&);							/*rysuje ekran smierci*/
	void drawLevelMenu(sf::RenderWindow&);								/*rysuje menu do zmiany poziomu*/
	sf::RectangleShape getResumeButton();								/*zwraca przycisk do kontynuacji gry z menu pauzy*/
	sf::RectangleShape getSaveButton();									/*zwraca przycisk do zapisu gry z menu pauzy*/
	sf::RectangleShape getQuitButton();									/*zwraca przycisk do wyjscia z gry z menu pauzy*/
	void setResumeHighlight(short);										/*ustawia podswietlenie przycisku w zaleznosci od podanego argumentu*/
	void setSaveHighlight(short);										/*ustawia podswietlenie przycisku w zaleznosci od podanego argumentu*/
	void setQuitHighlight(short);										/*ustawia podswietlenie przycisku w zaleznosci od podanego argumentu*/
	void pushDamageInfo(TextDamage*);									/*dodaje do kontenera tekst do wyswietlenia o zadanych/wyleczonych obrazeniach*/
	void pushHpInfo(HpBar*);											/*dodaje do kontenera pasek zycia przeciwnika*/
	void updateHpInfo(size_t, sf::Vector2f, short, short);				/*aktualizuje pasek zycia przeciwnika*/
	void eraseHpInfo(size_t);											/*usuwa z kontenera pasek zycia przeciwnika*/
	size_t getHpInfoSize();												/*zwraca rozmiar kontenera z paskami zycia*/
	void clearHpInfo();													/*czysci kontener paskow zycia*/
	void updateSkillCooldowns(sf::RenderWindow&, float, float, float);	/*aktualizuje obrazki umiejetnosci*/
private:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	sf::Texture texture;
	sf::Font font;														/*czcionka dla calego GUI*/
	/*hud*/
	sf::Sprite hpGauge;													/*obrazek ilustrujacy obecne hp gracza*/
	sf::Sprite expGauge;												/*obrazek ilustrujacy obecne punkty doswiadczenia gracza*/
	sf::Text currHp, maximHp;											/*wyswietlany tekst z obecnym i maksymalnym hp gracza*/
	sf::Text experience;												/*wyswietlany tekst z procentowym stosunkiem obecnych punktow doswiadczenia do potrzebnych do awansu*/
	sf::Text potions;													/*wyswietlany tekst z iloscia mikstur zycia*/
	sf::RectangleShape skill1, fadedSkill1;								/*obrazek umiejetnosci pierwszej - zaladowanej i niezaladowanej*/
	sf::RectangleShape skill2, fadedSkill2;								/*obrazek umiejetnosci drugiej - zaladowanej i niezaladowanej*/
	sf::RectangleShape skill3, fadedSkill3;								/*obrazek umiejetnosci trzeciej - zaladowanej i niezaladowanej*/
	sf::Clock flash;													/*zegar odpowiadajacy za miganie obrazka hp gdy jest na niskim poziomie*/
	std::vector<TextDamage*> damageInfo;								/*kontener zawierajacy wszystkie zmiany hp do wyswietlenia*/
	std::vector<HpBar*> hpInfo;											/*kontener paskow hp przeciwnikow*/
	/*pauza*/
	sf::RectangleShape pauseMenu;										/*tlo menu pauzy*/
	sf::RectangleShape resumeButton;									/*przycisk kontynuacji gry*/
	sf::RectangleShape saveButton;										/*przycisk zapisu gry*/
	sf::RectangleShape quitButton;										/*przycisk wyjscia z gry*/
	sf::Text resume, save, quit;										/*teksty na przyciski*/
	/*ekwipunek*/
	sf::RectangleShape backpackBackground;								/*tlo plecaka*/
	sf::RectangleShape activeEquipment;									/*tlo aktywnych czesci ekwipunku*/
	sf::RectangleShape characterInfo;									/*tlo informacji o postaci*/
	sf::RectangleShape itemInfo;										/*tlo informacji o przedmiocie*/
	sf::RectangleShape plus;											/*obrazek plusa*/
	sf::Sprite backpackSlot;											/*obrazek nieaktywnego miejsca w ekwipunku*/
	sf::Sprite activeBackpackSlot;										/*obrazek aktywnego miejsca w ekwipunku*/
	sf::Text characterInfoHeader, activeEquipmentHeader, itemInfoHeader; /*naglowki sekcji informacji o postaci, aktywnego ekwipunku, badanego przedmiotu*/
	sf::Text playerStats;												/*tekst z informacjami o postaci*/
	sf::Text itemStats;													/*tekst z informacjami o przemdiocie*/
	sf::Text activeEquipmentInfo;										/*tekst z czesciami aktywnego ekwipunku*/
	/*zmiana poziomu*/
	sf::RectangleShape levelMenu;										/*tlo menu zmiany poziomu*/
	std::vector<sf::Text> levelOptions;									/*kontener opcji w menu zmiany poziomu*/
};
#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Gui : public sf::Drawable, sf::Transformable
{
public:
	struct TextDamage {
		sf::Text text;
		sf::Clock lifeTime;
		sf::Clock tick;
	};
	struct HpBar {
		sf::Vector2f characterPosition;
		sf::RectangleShape currentHp;
		sf::RectangleShape missingHp;
		HpBar();
	};
	Gui();
	~Gui();
	void setSkillPictures(std::string);
	void drawScreen(sf::RenderWindow&, Player*);
	void drawPauseMenu(sf::RenderWindow&);
	void drawEquipment(sf::RenderWindow&, Player*, short);
	void drawDeathScreen(sf::RenderWindow&);
	void drawLevelMenu(sf::RenderWindow&);
	sf::RectangleShape getResumeButton();
	sf::RectangleShape getSaveButton();
	sf::RectangleShape getQuitButton();
	void setResumeHighlight(short);
	void setSaveHighlight(short);
	void setQuitHighlight(short);
	void pushDamageInfo(TextDamage*);
	void pushHpInfo(HpBar*);
	void updateHpInfo(size_t, sf::Vector2f, short, short);
	void eraseHpInfo(size_t);
	size_t getHpInfoSize();
	void clearHpInfo();
	void updateSkillCooldowns(sf::RenderWindow&, float, float, float);
private:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	sf::Texture texture;
	sf::Font font;
	/*hud*/
	sf::Sprite hpGauge;
	sf::Sprite expGauge;
	sf::Text currHp, maximHp;
	sf::Text experience;
	sf::Text potions;
	sf::RectangleShape skill1, fadedSkill1;
	sf::RectangleShape skill2, fadedSkill2;
	sf::RectangleShape skill3, fadedSkill3;
	sf::Clock flash; /*miganie hp gdy jest niskie*/
	std::vector<TextDamage*> damageInfo;
	std::vector<HpBar*> hpInfo;
	/*pauza*/
	sf::RectangleShape pauseMenu;
	sf::RectangleShape resumeButton;
	sf::RectangleShape saveButton;
	sf::RectangleShape quitButton;
	sf::Text resume, save, quit;
	/*ekwipunek*/
	sf::RectangleShape backpackBackground;
	sf::RectangleShape activeEquipment;
	sf::RectangleShape characterInfo;
	sf::RectangleShape itemInfo;
	sf::RectangleShape plus;
	sf::Sprite backpackSlot;
	sf::Sprite activeBackpackSlot;
	sf::Text characterInfoHeader, activeEquipmentHeader, itemInfoHeader;
	sf::Text playerStats;
	sf::Text itemStats;
	sf::Text activeEquipmentInfo;
	/*zmiana poziomu*/
	sf::RectangleShape levelMenu;
	std::vector<sf::Text> levelOptions;
};
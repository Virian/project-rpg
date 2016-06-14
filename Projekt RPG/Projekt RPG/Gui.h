#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace sf;

class Gui : public Drawable, Transformable
{
public:
	struct TextDamage {
		Text text;
		Clock lifeTime;
		Clock tick;
	};
	struct HpBar {
		Vector2f characterPosition;
		RectangleShape currentHp;
		RectangleShape missingHp;
		HpBar();
	};
	Gui();
	~Gui();
	void setSkillPictures(string);
	void drawScreen(RenderWindow&, Player*);
	void drawPauseMenu(RenderWindow&);
	void drawEquipment(RenderWindow&, Player*, short);
	void drawDeathScreen(RenderWindow&);
	void drawLevelMenu(RenderWindow&);
	RectangleShape getResumeButton();
	RectangleShape getLoadButton();
	RectangleShape getQuitButton();
	void setResumeHighlight(short);
	void setLoadHighlight(short);
	void setQuitHighlight(short);
	void pushDamageInfo(TextDamage*);
	void pushHpInfo(HpBar*);
	void updateHpInfo(size_t, Vector2f, short, short);
	void eraseHpInfo(size_t);
	size_t getHpInfoSize();
	void clearHpInfo();
	void updateSkillCooldowns(RenderWindow&, float, float, float);
private:
	virtual void draw(RenderTarget&, RenderStates) const;
	Texture texture;
	Font font;
	/*hud*/
	Sprite hpGauge;
	Sprite expGauge;
	Text currHp, maximHp;
	Text experience;
	Text potions;
	RectangleShape skill1, fadedSkill1;
	RectangleShape skill2, fadedSkill2;
	RectangleShape skill3, fadedSkill3;
	Clock flash; /*miganie hp gdy jest niskie*/
	vector<TextDamage*> damageInfo;
	vector<HpBar*> hpInfo;
	/*pauza*/
	RectangleShape pauseMenu;
	RectangleShape resumeButton;
	RectangleShape loadButton;
	RectangleShape quitButton;
	/*ekwipunek*/
	RectangleShape backpackBackground;
	RectangleShape activeEquipment;
	RectangleShape characterInfo;
	RectangleShape itemInfo;
	RectangleShape plus; /*Reminder - do zamiany na obrazek plusa*/
	Sprite backpackSlot;
	Sprite activeBackpackSlot;
	Text characterInfoHeader, activeEquipmentHeader, itemInfoHeader;
	Text playerStats;
	Text itemStats;
	Text activeEquipmentInfo;
	/*zmiana poziomu*/
	RectangleShape levelMenu;
	vector<Text> levelOptions;
};
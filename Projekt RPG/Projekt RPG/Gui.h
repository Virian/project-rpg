#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Gui : public Drawable, Transformable
{
public:
	Gui();
	~Gui();
	void drawScreen(RenderWindow&, short, short);
	void drawPauseMenu(RenderWindow&);
	void drawEquipment(RenderWindow&);
	RectangleShape getResumeButton();
	RectangleShape getLoadButton();
	RectangleShape getQuitButton();
	void setResumeHighlight(short);
	void setLoadHighlight(short);
	void setQuitHighlight(short);
private:
	//RectangleShape hpBar;
	Sprite hpGauge;
	Texture texture;
	RectangleShape experienceBar;
	RectangleShape skill1;
	RectangleShape skill2;
	RectangleShape skill3;
	RectangleShape pauseMenu;
	RectangleShape resumeButton;
	RectangleShape loadButton;
	RectangleShape quitButton;
	Font font;
	Text currHp, maximHp;
	virtual void draw(RenderTarget&, RenderStates) const;
};
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
private:
	//RectangleShape hpBar;
	Sprite hpGauge;
	Texture texture;
	RectangleShape experienceBar;
	RectangleShape skill1;
	RectangleShape skill2;
	RectangleShape skill3;
	Font font;
	Text currHp, maximHp;
	virtual void draw(RenderTarget&, RenderStates) const;
};
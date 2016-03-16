#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Gui : public Drawable, Transformable
{
public:
	Gui();
	~Gui();
	void drawScreen(RenderWindow&);
	void drawPauseMenu(RenderWindow&);
	void drawEquipment(RenderWindow&);
private:
	RectangleShape hpBar;
	RectangleShape experienceBar;
	RectangleShape skill1;
	RectangleShape skill2;
	RectangleShape skill3;
	virtual void draw(RenderTarget&, RenderStates) const;
};
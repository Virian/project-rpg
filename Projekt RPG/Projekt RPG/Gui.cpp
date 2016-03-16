#include "Gui.h"

Gui::Gui()
{
	hpBar.setSize(Vector2f(250,50));
	experienceBar.setSize(Vector2f(250, 50));
	skill1.setSize(Vector2f(100, 100));
	skill2.setSize(Vector2f(100, 100));
	skill3.setSize(Vector2f(100, 100));

	hpBar.setFillColor(Color::Green);
	experienceBar.setFillColor(Color::Green);
	skill1.setFillColor(Color::Green);
	skill2.setFillColor(Color::Green);
	skill3.setFillColor(Color::Green);	
}

Gui::~Gui()
{

}

void Gui::drawScreen(RenderWindow &window)
{
	hpBar.setPosition(window.mapPixelToCoords(Vector2i(50, 650)));
	experienceBar.setPosition(window.mapPixelToCoords(Vector2i(980, 650)));
	skill1.setPosition(window.mapPixelToCoords(Vector2i(395, 600)));
	skill2.setPosition(window.mapPixelToCoords(Vector2i(590, 600)));
	skill3.setPosition(window.mapPixelToCoords(Vector2i(785, 600)));

	window.draw(hpBar);
	window.draw(experienceBar);
	window.draw(skill1);
	window.draw(skill2);
	window.draw(skill3);
}

void Gui::drawPauseMenu(RenderWindow &window)
{

}

void Gui::drawEquipment(RenderWindow &window)
{

}

void Gui::draw(RenderTarget &target, RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(hpBar);
	target.draw(experienceBar);
	target.draw(skill1);
	target.draw(skill2);
	target.draw(skill3);
}

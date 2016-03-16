#include "Gui.h"

Gui::Gui()
{
	hpBar.setSize(Vector2f(250,50));
	experienceBar.setSize(Vector2f(250, 50));
	skill1.setSize(Vector2f(64, 64));
	skill2.setSize(Vector2f(64, 64));
	skill3.setSize(Vector2f(64, 64));

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
	hpBar.setPosition(window.mapPixelToCoords(Vector2i(170, 650)));
	experienceBar.setPosition(window.mapPixelToCoords(Vector2i(860, 650)));
	skill1.setPosition(window.mapPixelToCoords(Vector2i(482, 636)));
	skill2.setPosition(window.mapPixelToCoords(Vector2i(608, 636)));
	skill3.setPosition(window.mapPixelToCoords(Vector2i(734, 636)));

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

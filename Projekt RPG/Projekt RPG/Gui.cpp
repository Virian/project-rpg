#include "Gui.h"
#include <Windows.h>

Gui::Gui()
{
	if (!font.loadFromFile("game_over.ttf")) /*Reminder - do zmiany sciezka, mozna tez zmienic czcionke*/
	{
		MessageBox(NULL, "Font not found!", "ERROR", NULL);
		return;
	}
	currHp.setFont(font);
	currHp.setCharacterSize(90);
	maximHp.setFont(font);
	maximHp.setCharacterSize(45);
	//hpBar.setSize(Vector2f(250,50));
	texture.loadFromFile("placeholder.png");
	hpGauge.setTexture(texture);
	hpGauge.setTextureRect(IntRect(0, 896, 64, 64));
	hpGauge.setScale(2.5, 2.5);
	experienceBar.setSize(Vector2f(250, 50));
	skill1.setSize(Vector2f(64, 64));
	skill2.setSize(Vector2f(64, 64));
	skill3.setSize(Vector2f(64, 64));

	//hpBar.setFillColor(Color::Green);
	experienceBar.setFillColor(Color::Green);
	skill1.setFillColor(Color::Green);
	skill2.setFillColor(Color::Green);
	skill3.setFillColor(Color::Green);	

	pauseMenu.setSize(Vector2f(350, 450));
	resumeButton.setSize(Vector2f(320, 100));
	loadButton.setSize(Vector2f(320, 100));
	quitButton.setSize(Vector2f(320, 100));
	
	pauseMenu.setFillColor(Color::Black);
	pauseMenu.setOutlineThickness(-2);
	pauseMenu.setOutlineColor(Color::White);
	resumeButton.setFillColor(Color::Cyan);
	resumeButton.setOutlineColor(Color::Red);
	loadButton.setFillColor(Color::Magenta);
	loadButton.setOutlineColor(Color::Red);
	quitButton.setFillColor(Color::White);
	quitButton.setOutlineColor(Color::Red);
}

Gui::~Gui()
{

}

void Gui::drawScreen(RenderWindow &window, short currentHp, short maxHp)
{
	float hpPercent = (static_cast<float>(currentHp) / static_cast<float>(maxHp)) * 100.0f;
	if ((hpPercent <= 100) && (hpPercent > 500.0f/6.0f)) hpGauge.setTextureRect(IntRect(0, 896, 64, 64));
	else if ((hpPercent <= 500.0f / 6.0f) && (hpPercent > 400.0f / 6.0f)) hpGauge.setTextureRect(IntRect(64, 896, 64, 64));
	else if ((hpPercent <= 400.0f / 6.0f) && (hpPercent > 50)) hpGauge.setTextureRect(IntRect(128, 896, 64, 64));
	else if ((hpPercent <= 50) && (hpPercent > 200.0f / 6.0f)) hpGauge.setTextureRect(IntRect(192, 896, 64, 64));
	else if ((hpPercent <= 200.0f / 6.0f) && (hpPercent > 100.0f / 6.0f)) hpGauge.setTextureRect(IntRect(256, 896, 64, 64));
	else if ((hpPercent <= 100.0f / 6.0f) && (hpPercent > 0)) hpGauge.setTextureRect(IntRect(320, 896, 64, 64));
	//hpBar.setPosition(window.mapPixelToCoords(Vector2i(170, 650)));
	hpGauge.setPosition(window.mapPixelToCoords(Vector2i(20, 540)));
	experienceBar.setPosition(window.mapPixelToCoords(Vector2i(860, 650)));
	skill1.setPosition(window.mapPixelToCoords(Vector2i(482, 636)));
	skill2.setPosition(window.mapPixelToCoords(Vector2i(608, 636)));
	skill3.setPosition(window.mapPixelToCoords(Vector2i(734, 636)));

	currHp.setString(std::to_string(currentHp));
	maximHp.setString(std::to_string(maxHp));
	
	currHp.setPosition(window.mapPixelToCoords(Vector2i(70, 540))); /*Reminder - fajnie by bylo dodac zeby pozycja zalezala od ilosci cyfr*/
	maximHp.setPosition(window.mapPixelToCoords(Vector2i(85, 600)));

	//window.draw(hpBar);
	window.draw(hpGauge);
	window.draw(experienceBar);
	window.draw(skill1);
	window.draw(skill2);
	window.draw(skill3);
	currHp.move(Vector2f(2, 2));
	currHp.setColor(Color::Black);
	window.draw(currHp);
	currHp.move(Vector2f(-2, -2));
	currHp.setColor(Color::White);
	window.draw(currHp);
	maximHp.move(Vector2f(2, 2));
	maximHp.setColor(Color::Black);
	window.draw(maximHp);
	maximHp.move(Vector2f(-2, -2));
	maximHp.setColor(Color::White);
	window.draw(maximHp);
}

void Gui::drawPauseMenu(RenderWindow &window)
{
	pauseMenu.setPosition(window.mapPixelToCoords(Vector2i(465, 135)));
	resumeButton.setPosition(window.mapPixelToCoords(Vector2i(480, 172)));
	loadButton.setPosition(window.mapPixelToCoords(Vector2i(480, 310)));
	quitButton.setPosition(window.mapPixelToCoords(Vector2i(480, 447)));
	
	window.draw(pauseMenu);
	window.draw(resumeButton);
	window.draw(loadButton);
	window.draw(quitButton);
}

void Gui::drawEquipment(RenderWindow &window)
{

}

void Gui::draw(RenderTarget &target, RenderStates states) const
{
	states.transform *= getTransform();
	//target.draw(hpBar);
	target.draw(hpGauge);
	target.draw(experienceBar);
	target.draw(skill1);
	target.draw(skill2);
	target.draw(skill3);
}

RectangleShape Gui::getResumeButton()
{
	return resumeButton;
}

RectangleShape Gui::getLoadButton()
{
	return loadButton;
}

RectangleShape Gui::getQuitButton()
{
	return quitButton;
}

void Gui::setResumeHighlight(short swtch)
{
	if (swtch == 0) resumeButton.setOutlineThickness(0);
	else resumeButton.setOutlineThickness(-4);
}

void Gui::setLoadHighlight(short swtch)
{
	if (swtch == 0) loadButton.setOutlineThickness(0);
	else loadButton.setOutlineThickness(-4);
}

void Gui::setQuitHighlight(short swtch)
{
	if (swtch == 0) quitButton.setOutlineThickness(0);
	else quitButton.setOutlineThickness(-4);
}
#include "Game.h"
#include <Windows.h>
#include <string>

Game::Game()
{
	state = END;
	if (!font.loadFromFile("SharpRetro.ttf"))
	{
		MessageBox(NULL, "Font not found!", "ERROR", NULL);
		return;
	}
	state = MENU;
	window.create(VideoMode(1280, 720), "Galaxy Guardian Pre-Alpha 1.02", Style::Close);
}

Game::~Game()
{

}

void Game::menu()
{
	Text title("Galaxy Guardian", font, 150);
	const short numberOfOptions = 3;
	string options[] = {"New game", "Load game", "Quit"};
	Text text[numberOfOptions];

	title.setStyle(Text::Bold);
	title.setPosition(1280 / 2 - title.getGlobalBounds().width / 2, 40);

	for (short i = 0; i < numberOfOptions; i++)
	{
		text[i].setFont(font);
		text[i].setCharacterSize(70);
		text[i].setString(options[i]);
		text[i].setPosition(1280 / 2 - text[i].getGlobalBounds().width / 2, 270 + i * 100);
	}

	while (state == MENU)
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) state = END;
			else if ((text[numberOfOptions - 1].getGlobalBounds().contains(mouse)) && (event.type == Event::MouseButtonReleased) && (event.key.code == Mouse::Left)) state = END;
		}

		for (short i = 0; i < numberOfOptions; i++)
		{
			if (text[i].getGlobalBounds().contains(mouse)) text[i].setColor(Color::Green);
			else text[i].setColor(Color::White);
		}

		window.clear();
		window.draw(title);
		for (short i = 0; i < numberOfOptions; i++) window.draw(text[i]);
		window.display();
	}
}

void Game::start()
{
	while (state != END)
	{
		switch (state)
		{
		case GameState::MENU:
			menu();
			break;
		case GameState::GAME:
			//odpalenie gry
			break;
		}
	}
}
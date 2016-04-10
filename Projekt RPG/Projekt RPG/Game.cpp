#include "Game.h"
#include <Windows.h>
#include <string>

Game::Game()
{
	state = END;
	if (!font.loadFromFile("SharpRetro.ttf")) /*Reminder - do zmiany sciezka, mozna tez zmienic czcionke*/
	{
		MessageBox(NULL, "Font not found!", "ERROR", NULL);
		return;
	}
	if (!texture.loadFromFile("menu.png")) /*Reminder - do zmiany sciezka*/
	{
		MessageBox(NULL, "Menu background not found!", "ERROR", NULL);
		return;
	}
	state = MENU;
	window.create(VideoMode(1280, 720), "Galaxy Guardian Pre-Alpha 1.09", Style::Titlebar);
}

Game::~Game()
{

}

void Game::menu()
{
	Text title("Galaxy Guardian", font, 150);
	const short numberOfOptions = 3; /*ilosc opcji do klikniecia w menu*/
	string options[] = {"New game", "Load game", "Quit"};
	Text text[numberOfOptions];
	/*Reminder - do dodania na pewno jakies tlo
	mozna tez zamienic napisy na obrazki */
	background.setSize(Vector2f(1280, 720));
	background.setTexture(&texture);
	title.setStyle(Text::Bold);
	title.setPosition(1280 / 2 - title.getGlobalBounds().width / 2, 40);

	for (short i = 0; i < numberOfOptions; i++) /*ustawienie poszczegolnych tekstow*/
	{
		text[i].setFont(font);
		text[i].setCharacterSize(70);
		text[i].setString(options[i]);
		text[i].setPosition(1280 / 2 - text[i].getGlobalBounds().width / 2, 270 + i * 100);
	}

	while (state == MENU)
	{
		Vector2f mouse(Mouse::getPosition(window)); /*window jest potrzebny jako argument zeby pozycja byla liczona wzgledem okna, a nie pulpitu*/
		Event event;

		while (window.pollEvent(event))
		{
			/*klikniecie X*/
			if (event.type == Event::Closed) state = END;
			/*klikniecie new game*/
			else if ((text[0].getGlobalBounds().contains(mouse)) && (event.type == Event::MouseButtonReleased) && (event.key.code == Mouse::Left)) state = GAME;
			/*klikniecie quit*/
			else if ((text[numberOfOptions - 1].getGlobalBounds().contains(mouse)) && (event.type == Event::MouseButtonReleased) && (event.key.code == Mouse::Left)) state = END;
		}

		window.clear();
		window.draw(background);
		title.move(Vector2f(4, 4));
		title.setColor(Color::Black);
		window.draw(title);				/*cien rzucany przez tytul*/
		title.move(Vector2f(-4, -4));
		title.setColor(Color::White);
		window.draw(title);				/*tytul*/
		for (short i = 0; i < numberOfOptions; i++)
		{
			text[i].move(Vector2f(3, 3));
			text[i].setColor(Color::Black);
			window.draw(text[i]);
			text[i].move(Vector2f(-3, -3));
			if (text[i].getGlobalBounds().contains(mouse)) text[i].setColor(Color::Green);
			else text[i].setColor(Color::White);
			window.draw(text[i]);
		}
		window.display();
	}
}

void Game::newGame()
{
	Engine engine(window);

	state = MENU;
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
			newGame();
			break;
		}
	}
}
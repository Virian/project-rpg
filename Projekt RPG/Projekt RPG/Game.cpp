#include "Game.h"
#include <Windows.h>
#include <string>
#include <fstream>

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
	window.create(VideoMode(1280, 720), "Galaxy Guardian Alpha 1.01", Style::Titlebar);
}

Game::~Game()
{

}

void Game::menu()
{
	Text title("Galaxy Guardian", font, 150);
	const short numberOfOptions = 3; /*ilosc opcji do klikniecia w menu*/
	string options[] = { "New game", "Load game", "Quit" };
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
		text[i].setPosition(1280.0f / 2 - text[i].getGlobalBounds().width / 2, 270.0f + i * 100);
	}

	while (state == MENU)
	{
		Vector2f mouse(Mouse::getPosition(window)); /*window jest potrzebny jako argument zeby pozycja byla liczona wzgledem okna, a nie pulpitu*/
		Event event;

		while (window.pollEvent(event))
		{
			/*klikniecie new game*/
			if ((text[0].getGlobalBounds().contains(mouse)) && (event.type == Event::MouseButtonReleased) && (event.key.code == Mouse::Left)) state = NEW_GAME;
			/*klikniecie load game*/
			else if ((text[1].getGlobalBounds().contains(mouse)) && (event.type == Event::MouseButtonReleased) && (event.key.code == Mouse::Left)) state = LOAD_GAME;
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
	Text header("Create your character", font, 120);
	Text ok("OK", font, 120);
	Text select("Select your class", font, 90);
	Text enterName("Enter your name", font, 90);
	const short numberOfClasses = 3;
	string classesNames[] = { "Soldier", "Sentinel", "Juggernaut" };
	Text classes[numberOfClasses];
	string characterName;
	Text name;
	short checked = 0;
	bool created = false;

	header.setStyle(Text::Bold);
	header.setPosition(1280 / 2 - header.getGlobalBounds().width / 2, 0.f);
	ok.setStyle(Text::Bold);
	ok.setPosition(1280 / 2 - ok.getGlobalBounds().width / 2, 570.f);
	select.setPosition(1280 / 2 - select.getGlobalBounds().width / 2, 150.f);
	enterName.setPosition(1280 / 2 - enterName.getGlobalBounds().width / 2, 370.f);
	name.setFont(font);
	name.setCharacterSize(120);
	for (short i = 0; i < numberOfClasses; i++)
	{
		classes[i].setFont(font);
		classes[i].setCharacterSize(70);
		classes[i].setString(classesNames[i]);
		classes[i].setPosition(200.f + i * 300.f, 270.f);
	}

	while (!created)
	{
		Vector2f mouse(Mouse::getPosition(window)); /*window jest potrzebny jako argument zeby pozycja byla liczona wzgledem okna, a nie pulpitu*/
		Event event;

		while (window.pollEvent(event))
		{
			if (((ok.getGlobalBounds().contains(mouse)) && (event.type == Event::MouseButtonReleased) && (event.key.code == Mouse::Left)) || ((event.type == Event::KeyReleased) && (event.key.code == Keyboard::Return)))
			{				
				if (checked == 0) MessageBox(NULL, "Select a class for your character!", "ERROR", NULL);
				else if (characterName.size() == 0) MessageBox(NULL, "Enter a name for your character!", "ERROR", NULL);
				else created = true;
			}
			else if ((event.type == Event::KeyReleased) && (event.key.code == Keyboard::BackSpace) && (characterName.size() > 0)) characterName.pop_back();
			else if ((event.type == Event::TextEntered) && (characterName.size() < 20) && ((event.text.unicode > 96) && (event.text.unicode < 123)) || ((event.text.unicode > 64) && (event.text.unicode < 91)) || (event.text.unicode == 32)) characterName.push_back(event.text.unicode);
			for (short i = 0; i < numberOfClasses; ++i)
			{
				if ((event.type == Event::MouseButtonReleased) && (event.key.code == Mouse::Left) && (classes[i].getGlobalBounds().contains(mouse))) checked = i + 1;
			}
		}
		window.clear();
		window.draw(background);
		header.move(Vector2f(4, 4));
		header.setColor(Color::Black);
		window.draw(header);
		header.move(Vector2f(-4, -4));
		header.setColor(Color::White);
		window.draw(header);
		select.move(Vector2f(4, 4));
		select.setColor(Color::Black);
		window.draw(select);
		select.move(Vector2f(-4, -4));
		select.setColor(Color::White);
		window.draw(select);
		enterName.move(Vector2f(4, 4));
		enterName.setColor(Color::Black);
		window.draw(enterName);
		enterName.move(Vector2f(-4, -4));
		enterName.setColor(Color::White);
		window.draw(enterName);
		ok.move(Vector2f(4, 4));
		ok.setColor(Color::Black);
		window.draw(ok);
		ok.move(Vector2f(-4, -4));
		if (ok.getGlobalBounds().contains(mouse)) ok.setColor(Color::Green);
		else ok.setColor(Color::White);
		window.draw(ok);
		name.setString(characterName);
		name.setPosition(1280 / 2 - name.getGlobalBounds().width / 2, 460.f);
		name.move(Vector2f(4, 4));
		name.setColor(Color::Black);
		window.draw(name);
		name.move(Vector2f(-4, -4));
		name.setColor(Color::White);
		window.draw(name);
		for (short i = 0; i < numberOfClasses; i++)
		{
			classes[i].move(Vector2f(3, 3));
			classes[i].setColor(Color::Black);
			window.draw(classes[i]);
			classes[i].move(Vector2f(-3, -3));
			if (checked == i + 1) classes[i].setColor(Color::Green);
			else classes[i].setColor(Color::White);
			window.draw(classes[i]);
		}
		window.display();
	}
	
	Engine engine(window, characterName, checked);

	state = MENU;
}

void Game::loadGame()
{
	fstream file("SavedGame.sav");
	
	if (!file.is_open())
	{
		MessageBox(NULL, "Couldn't find a save file!", "ERROR", NULL);
		state = MENU;
		return;
	}
	Engine engine(window, file);

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
		case GameState::NEW_GAME:
			newGame();
			break;
		case GameState::LOAD_GAME:
			loadGame();
			break;
		}
	}
}
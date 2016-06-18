#include "Game.h"
#include <Windows.h>
#include <string>
#include <fstream>

Game::Game()
{
	state = END;
	if (!font.loadFromFile("fonts/SharpRetro.ttf"))
	{
		MessageBox(NULL, "Font not found!", "ERROR", NULL);
		return;
	}
	if (!texture.loadFromFile("images/menu.png"))
	{
		MessageBox(NULL, "Menu background not found!", "ERROR", NULL);
		return;
	}
	if (!cursorTexture.loadFromFile("images/cursors.png"))
	{
		MessageBox(NULL, "Cursor files not found!", "ERROR", NULL);
		return;
	}
	cursor.setTexture(cursorTexture);
	cursor.setTextureRect(sf::IntRect(0, 0, 26, 32));
	state = MENU;
	window.create(sf::VideoMode(1280, 720), "Galaxy Guardian Alpha 1.04", sf::Style::Titlebar);
	window.setMouseCursorVisible(false);
}

Game::~Game()
{

}

void Game::menu()
{
	sf::Text title("Galaxy Guardian", font, 150);
	const short numberOfOptions = 3; /*ilosc opcji do klikniecia w menu*/
	std::string options[] = { "New game", "Load game", "Quit" };
	sf::Text text[numberOfOptions];
	background.setSize(sf::Vector2f(1280, 720));
	background.setTexture(&texture);
	title.setStyle(sf::Text::Bold);
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
		sf::Vector2f mouse(sf::Mouse::getPosition(window)); /*window jest potrzebny jako argument zeby pozycja byla liczona wzgledem okna, a nie pulpitu*/
		sf::Event event;

		while (window.pollEvent(event))
		{
			/*klikniecie new game*/
			if ((text[0].getGlobalBounds().contains(mouse)) && (event.type == sf::Event::MouseButtonReleased) && (event.key.code == sf::Mouse::Left)) state = NEW_GAME;
			/*klikniecie load game*/
			else if ((text[1].getGlobalBounds().contains(mouse)) && (event.type == sf::Event::MouseButtonReleased) && (event.key.code == sf::Mouse::Left)) state = LOAD_GAME;
			/*klikniecie quit*/
			else if ((text[numberOfOptions - 1].getGlobalBounds().contains(mouse)) && (event.type == sf::Event::MouseButtonReleased) && (event.key.code == sf::Mouse::Left)) state = END;
		}

		cursor.setPosition(mouse);
		window.clear();
		window.draw(background);
		title.move(sf::Vector2f(4, 4));
		title.setColor(sf::Color::Black);
		window.draw(title);				/*cien rzucany przez tytul*/
		title.move(sf::Vector2f(-4, -4));
		title.setColor(sf::Color::White);
		window.draw(title);				/*tytul*/
		for (short i = 0; i < numberOfOptions; i++)
		{
			text[i].move(sf::Vector2f(3, 3));
			text[i].setColor(sf::Color::Black);
			window.draw(text[i]);
			text[i].move(sf::Vector2f(-3, -3));
			if (text[i].getGlobalBounds().contains(mouse)) text[i].setColor(sf::Color::Green);
			else text[i].setColor(sf::Color::White);
			window.draw(text[i]);
		}
		window.draw(cursor);
		window.display();
	}
}

void Game::newGame()
{
	sf::Text header("Create your character", font, 120);
	sf::Text ok("OK", font, 120);
	sf::Text select("Select your class", font, 90);
	sf::Text enterName("Enter your name", font, 90);
	const short numberOfClasses = 3;
	std::string classesNames[] = { "Soldier", "Sentinel", "Juggernaut" };
	sf::Text classes[numberOfClasses];
	std::string characterName;
	sf::Text name;
	short checked = 0;
	bool created = false;

	header.setStyle(sf::Text::Bold);
	header.setPosition(1280 / 2 - header.getGlobalBounds().width / 2, 0.f);
	ok.setStyle(sf::Text::Bold);
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
		sf::Vector2f mouse(sf::Mouse::getPosition(window)); /*window jest potrzebny jako argument zeby pozycja byla liczona wzgledem okna, a nie pulpitu*/
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (((ok.getGlobalBounds().contains(mouse)) && (event.type == sf::Event::MouseButtonReleased) && (event.key.code == sf::Mouse::Left)) || ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Return)))
			{				
				if (checked == 0) MessageBox(NULL, "Select a class for your character!", "ERROR", NULL);
				else if (characterName.size() == 0) MessageBox(NULL, "Enter a name for your character!", "ERROR", NULL);
				else created = true;
			}
			else if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::BackSpace) && (characterName.size() > 0)) characterName.pop_back();
			else if ((event.type == sf::Event::TextEntered) && (characterName.size() < 20) && ((event.text.unicode > 96) && (event.text.unicode < 123)) || ((event.text.unicode > 64) && (event.text.unicode < 91)) || (event.text.unicode == 32)) characterName.push_back(event.text.unicode);
			for (short i = 0; i < numberOfClasses; ++i)
			{
				if ((event.type == sf::Event::MouseButtonReleased) && (event.key.code == sf::Mouse::Left) && (classes[i].getGlobalBounds().contains(mouse))) checked = i + 1;
			}
		}
		cursor.setPosition(mouse);
		window.clear();
		window.draw(background);
		header.move(sf::Vector2f(4, 4));
		header.setColor(sf::Color::Black);
		window.draw(header);
		header.move(sf::Vector2f(-4, -4));
		header.setColor(sf::Color::White);
		window.draw(header);
		select.move(sf::Vector2f(4, 4));
		select.setColor(sf::Color::Black);
		window.draw(select);
		select.move(sf::Vector2f(-4, -4));
		select.setColor(sf::Color::White);
		window.draw(select);
		enterName.move(sf::Vector2f(4, 4));
		enterName.setColor(sf::Color::Black);
		window.draw(enterName);
		enterName.move(sf::Vector2f(-4, -4));
		enterName.setColor(sf::Color::White);
		window.draw(enterName);
		ok.move(sf::Vector2f(4, 4));
		ok.setColor(sf::Color::Black);
		window.draw(ok);
		ok.move(sf::Vector2f(-4, -4));
		if (ok.getGlobalBounds().contains(mouse)) ok.setColor(sf::Color::Green);
		else ok.setColor(sf::Color::White);
		window.draw(ok);
		name.setString(characterName);
		name.setPosition(1280 / 2 - name.getGlobalBounds().width / 2, 460.f);
		name.move(sf::Vector2f(4, 4));
		name.setColor(sf::Color::Black);
		window.draw(name);
		name.move(sf::Vector2f(-4, -4));
		name.setColor(sf::Color::White);
		window.draw(name);
		for (short i = 0; i < numberOfClasses; i++)
		{
			classes[i].move(sf::Vector2f(3, 3));
			classes[i].setColor(sf::Color::Black);
			window.draw(classes[i]);
			classes[i].move(sf::Vector2f(-3, -3));
			if (checked == i + 1) classes[i].setColor(sf::Color::Green);
			else classes[i].setColor(sf::Color::White);
			window.draw(classes[i]);
		}
		window.draw(cursor);
		window.display();
	}
	
	Engine engine(window, cursor, characterName, checked);

	state = MENU;
}

void Game::loadGame()
{
	std::fstream file("save/SavedGame.sav");
	
	if (!file.is_open())
	{
		MessageBox(NULL, "Couldn't find a save file!", "ERROR", NULL);
		state = MENU;
		return;
	}
	Engine engine(window, cursor, file);

	state = MENU;
}

bool Game::checkFiles()
{
	sf::Texture tempTexture;
	sf::Font tempFont;
	sf::Music tempMusic;
	sf::SoundBuffer tempSoundBuffer;
	std::fstream tempFile;

	if (!tempTexture.loadFromFile("images/tilesheet.png")) return false;
	if (!tempFont.loadFromFile("fonts/game_over.ttf")) return false;
	tempFile.open("levels/level1.level");
	if (!tempFile.is_open()) return false;
	else tempFile.close();
	tempFile.open("levels/level2.level");
	if (!tempFile.is_open()) return false;
	else tempFile.close();
	if (!tempMusic.openFromFile("music/background1.ogg")) return false;
	if (!tempMusic.openFromFile("music/background2.ogg")) return false;
	if (!tempSoundBuffer.loadFromFile("sounds/gun.ogg")) return false;
	if (!tempSoundBuffer.loadFromFile("sounds/melee.ogg")) return false;

	return true;
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
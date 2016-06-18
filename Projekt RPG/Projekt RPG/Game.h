#pragma once
#include <SFML/Graphics.hpp>
#include "Engine.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Font font;
	sf::RectangleShape background;
	sf::Texture texture;
	sf::Texture cursorTexture;
	sf::Sprite cursor;
	void menu();
	void newGame();
	void loadGame();
protected:
	enum GameState {MENU, NEW_GAME, LOAD_GAME, END};
	GameState state;
public:
	Game();
	~Game();
	bool checkFiles();
	void start();
};
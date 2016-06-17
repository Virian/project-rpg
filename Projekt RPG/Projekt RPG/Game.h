#pragma once
#include <SFML/Graphics.hpp>
#include "Engine.h"

using namespace sf;
using namespace std;

class Game
{
private:
	RenderWindow window;
	Font font;
	RectangleShape background;
	Texture texture;
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
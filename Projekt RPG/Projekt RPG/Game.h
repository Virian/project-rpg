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
protected:
	enum GameState {MENU, GAME, GAME_OVER, END};
	GameState state;
public:
	Game();
	~Game();
	void start();
};
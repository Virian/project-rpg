#pragma once
#include <SFML/Graphics.hpp>
#include "Engine.h"

class Game
{
private:
	sf::RenderWindow window;							/*okno gry*/
	sf::Font font;										/*czcionka w menu glownym*/
	sf::RectangleShape background;						/*tlo w menu*/
	sf::Texture texture;								/*tekstura tla w menu*/
	sf::Texture cursorTexture;							/*tekstura kursora*/
	sf::Sprite cursor;									/*kursor*/
	void menu();										/*menu*/
	void newGame();										/*rozpoczecie nowej gry*/
	void loadGame();									/*wczytanie stanu gry*/
protected:
	enum GameState {MENU, NEW_GAME, LOAD_GAME, END};	/*stan gry*/
	GameState state;
public:
	Game();
	~Game();
	bool checkFiles();									/*sprawdzenie czy sa wszystkie potrzebne pliki*/
	void start();										/*uruchomienie gry*/
};
#include "Game.h"
#include <ctime>
#include <cstdlib>

/*Reminder - usunac using namespace z plikow .h*/

int main()
{
	/*sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}*/
	Game game;
	srand(time(NULL));
	game.start();
	return 0;
}
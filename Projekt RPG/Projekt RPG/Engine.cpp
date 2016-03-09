#include "Engine.h"

Engine::Engine(RenderWindow &_window)
{
	startEngine(_window);
}

Engine::~Engine()
{

}

void Engine::startEngine(RenderWindow &window)
{
	bool menu = false;

	while (!menu)
	{
		Event event;
		sf::Vector2f mouse(Mouse::getPosition(window));

		while (window.pollEvent(event))
		{
			if ((event.type == Event::KeyReleased) && (event.key.code == Keyboard::Escape))
				menu = true;

			/*if (event.type == Event::KeyPressed && event.key.code == Keyboard::W)
			{
				player.walk();
			}

			else if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::W)
					player.stop();
			}*/
			if ((event.type == Event::MouseButtonPressed) && (event.mouseButton.button == Mouse::Right))
			{
				player.walk();
			}
			else if (event.type == Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == Mouse::Right) player.stop();
			}
		}

		player.update(mouse);

		window.clear();
		window.draw(player);
		window.display();
	}
}
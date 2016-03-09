#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Engine
{
private:
	RenderWindow *window;
public:
	Engine(RenderWindow&);
	~Engine();
	void startEngine();
};
#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace sf;

class Engine
{
private:
	Player player;
public:
	Engine(RenderWindow&);
	~Engine();
	void startEngine(RenderWindow&);
};
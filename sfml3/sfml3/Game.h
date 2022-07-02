#pragma once

#include <iostream>
#include <ctime>

#include "Player.h"

class Game
{
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	bool endGame;
	sf::Event sfmlEvent;

	Player player;

	// Private methods
	void initVariables();
	void initWindow();

public:
	// Constructors and destructor
	Game();
	~Game();

	// Accessors


	// Modifiers


	// Methods
	const bool running() const;
	void pollEvents();

	void update();
	void render();

};


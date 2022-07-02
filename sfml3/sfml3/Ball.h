#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


class Ball
{
private:
	sf::CircleShape shape;

	// Private Methods
	void initShape();

public:
	// Constructor and destructor
	Ball();
	virtual ~Ball();

	// Methods
	void update();
	void render(sf::RenderTarget& target);
};


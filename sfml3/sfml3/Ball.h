#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

enum ballTypes { DEFAULT = 0, DAMAGING, HEALING, NROFTYPES };

class Ball
{
private:
	sf::CircleShape shape;
	int type;

	// Private Methods
	void initShape(const sf::RenderWindow& window);

public:
	// Constructor and destructor
	Ball(const sf::RenderWindow& window, int type);
	virtual ~Ball();

	// Accessors
	const sf::CircleShape& getShape() const;
	const int& getType() const;

	// Methods
	void update();
	void render(sf::RenderTarget& target);
};


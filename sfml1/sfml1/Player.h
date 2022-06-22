#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Player
{
private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;

public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime,
		float speed);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	sf::Vector2f GetPosition() { return body.getPosition(); }
};


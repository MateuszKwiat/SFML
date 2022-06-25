#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"

class Player
{
private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;

	sf::Vector2f velocity;
	bool canJump;
	float jumpHeight;

public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime,
		float speed, float jumpHeight);

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void onCollision(sf::Vector2f direction);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }
};


#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
public:
	sf::IntRect uvRect;

private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	float totalTime;
	float switchTime;

public:
		Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
		void Update(int row, float deltaTime, bool faceRight);
};


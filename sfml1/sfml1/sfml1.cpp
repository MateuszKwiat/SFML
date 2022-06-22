#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"

static const float VIEW_HEIGHT = 512.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(VIEW_HEIGHT, VIEW_HEIGHT), "SFML tutorial",
		sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(512, 512));

	sf::Texture playerTexture;
	playerTexture.loadFromFile("lin-tux-gimp-t.png");

	Player player(&playerTexture, sf::Vector2u(3, 9), 0.3f, 100.0f);

	float deltaTime = 0.0f;
	sf::Clock clock;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		sf::Event eve;
		while (window.pollEvent(eve))
		{
			switch (eve.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				ResizeView(window, view);
				break;
			}	
		}

		player.Update(deltaTime);
		view.setCenter(player.GetPosition());

		window.clear(sf::Color::White);
		window.setView(view);
		player.Draw(window);
		window.display();
	}
}
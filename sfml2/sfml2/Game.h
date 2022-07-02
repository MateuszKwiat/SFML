#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>`

// Wrapper class
class Game
{
private:
	// Variables
	// Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	// Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Resources
	sf::Font font;

	// Text
	sf::Text uiText;

	// Game logic
	bool endGame;
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	// Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	// Private methods
	void InitializeVariables();
	void InitWindow();
	void InitFonts();
	void InitText();
	void InitEnemies();

public:
	// Constructors & destructor
	Game();
	virtual ~Game();

	// Accessors
	const bool Running() const;
	const bool GetEndGame() const;

	// Methods
	void SpawnEnemy();

	void PollEvents();
	void UpdateMousePositions();
	void UpdateText();
	void UpdateEnemies();
	void Update();

	void RenderText(sf::RenderTarget& target);
	void RenderEnemies(sf::RenderTarget& target);
	void Render();
};


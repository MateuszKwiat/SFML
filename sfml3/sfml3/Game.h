#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>

#include "Player.h"
#include "Ball.h"

class Game
{
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	bool endGame;
	sf::Event sfmlEvent;

	Player player;
	
	int points;

	// Font 
	sf::Font font;
	sf::Text guiText;
	sf::Text endGameText;

	// Balls
	std::vector<Ball> balls;
	float spawnTimerMax;
	float spawnTimer;
	int maxBalls;

	// Private methods
	void initVariables();
	void initWindow();
	void initFont();
	void initText();

public:
	// Constructors and destructor
	Game();
	~Game();

	// Accessors
	const bool& getEndGame() const;

	// Modifiers


	// Methods
	const bool running() const;
	void pollEvents();

	void spawnBalls();
	const int randBallType() const;
	void updatePlayer();
	void updateCollision();
	void updateGui();
	void update();

	void renderGui(sf::RenderTarget* target);
	void render();

};


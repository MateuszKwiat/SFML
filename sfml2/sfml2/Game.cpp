#include "Game.h"

// Private methods
void Game::InitializeVariables()
{
	this->window = nullptr;

	// Game logic
	this->endGame = false;
	this->points = 0;
	this->health = 20;
	this->enemySpawnTimerMax = 20.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 10;
	this->mouseHeld = false;
}

void Game::InitWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "1st game",
		sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
}

void Game::InitFonts()
{
	if (this->font.loadFromFile("fonts/Dosis-Light.ttf"))
	{
		std::cout << "Failed to load fonts\n";
	}
}

void Game::InitText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(22);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("NONE");
}

void Game::InitEnemies()
{
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setFillColor(sf::Color::Cyan);
//	this->enemy.setOutlineColor(sf::Color::Green);
//	this->enemy.setOutlineThickness(1.f);
}

// Constructors & destructor
Game::Game()
{
	this->InitializeVariables();
	this->InitWindow();
	this->InitFonts();
	this->InitText();
	this->InitEnemies();
}

Game::~Game()
{
	delete this->window;
}

// Accessors
const bool Game::Running() const
{
	return this->window->isOpen();
}

const bool Game::GetEndGame() const
{
	return this->endGame;
}



// Methods
void Game::SpawnEnemy()
{
	/*
		@return void

		Spawns enemies and sets their types, colors and positions randomly
		- sets a random type(diff)
		- sets a random position
		- sets a random color
		- adds the enemy to the vector
	*/

	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x
			- this->enemy.getSize().x)),
		0.f
			);	

	// Randomize enemy type
	int type = rand() % 5;

	switch (type)
	{
	case 0:
		this->enemy.setSize(sf::Vector2f(10.f, 10.f));
		this->enemy.setFillColor(sf::Color::Magenta);
		break;
	case 1:
		this->enemy.setSize(sf::Vector2f(30.f, 30.f));
		this->enemy.setFillColor(sf::Color::Blue);
		break;
	case 2:
		this->enemy.setSize(sf::Vector2f(50.f, 50.f));
		this->enemy.setFillColor(sf::Color::Cyan);
		break;
	case 3:
		this->enemy.setSize(sf::Vector2f(70.f, 70.f));
		this->enemy.setFillColor(sf::Color::Red);
		break;
	case 4:
		this->enemy.setSize(sf::Vector2f(100.f, 100.f));
		this->enemy.setFillColor(sf::Color::Green);
		break;
	default:
		this->enemy.setSize(sf::Vector2f(100.f, 100.f));
		this->enemy.setFillColor(sf::Color::Yellow);
		break;
	}

	// Spawn the enemy	
	this->enemies.push_back(this->enemy);
}

void Game::PollEvents()
{
	// Event polling
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::UpdateMousePositions()
{
	/*
	@ return void

	updates the mouse positions:
	- mouse position relative to the window (Vector2i)	
	*/

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::UpdateText()
{
	std::stringstream ss;

	ss << "Points: " << this->points << "\n"
		<< "Health: " << this->health << "\n";

	this->uiText.setString(ss.str());
}

void Game::UpdateEnemies()
{
	/*
		@return void

		Updates the enemy spawn timer and spawns enemies
		when the total amount of enemies is smaller than the max.
		Moves the enemies downwards.
		Removes the enemies at the edge of the screen. //TODO
	*/

	// Updating the timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies)
	{

		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			// Spawn the enemy and reset the timer
			this->SpawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	// Moving and updating enemies
	for (int i = 0; i < this->enemies.size(); i++)
	{

		bool deleted = false;

		this->enemies[i].move(0.f, 3.f);

		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
			std::cout << "Health: " << this->health << '\n';
		}
	}


	// Check if clicked upon
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size()
				&& deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().
					contains(this->mousePosView))
				{
					// Gain points
					if (this->enemies[i].getFillColor()
						== sf::Color::Magenta)
						this->points += 10;
					else if (this->enemies[i].getFillColor()
						== sf::Color::Blue)
						this->points += 7;
					else if (this->enemies[i].getFillColor()
						== sf::Color::Cyan)
						this->points += 5;
					else if (this->enemies[i].getFillColor()
						== sf::Color::Red)
						this->points += 3;
					else if (this->enemies[i].getFillColor()
						== sf::Color::Green)
						this->points += 1;

					std::cout << "Points: " << this->points << '\n';
					
					// Delete the enemy
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);
				}
			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}
}

void Game::Update()
{
	this->PollEvents();

	if (this->endGame == false)
	{
		this->UpdateMousePositions();

		this->UpdateText();

		this->UpdateEnemies();
	}

	// End game condition
	if (this->health <= 0)
		this->endGame = true;
}

void Game::RenderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}

void Game::RenderEnemies(sf::RenderTarget& target)
{
	// Rendering all the enemies
	for (auto& x : this->enemies)
	{
		target.draw(x);
	}
}

void Game::Render()
{
	/*
		- clear old frame
		- render objects
		- display frame in window

		Renders the game objects
	*/

	this->window->clear();	

	// Draw game objects
	this->RenderEnemies(*this->window);

	this->RenderText(*this->window);

	this->window->display();
}
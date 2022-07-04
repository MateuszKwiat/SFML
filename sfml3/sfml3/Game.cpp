#include "Game.h"

// Private methods
void Game::initVariables()
{
	this->endGame = false;
	this->spawnTimerMax = 10.f;
	this->spawnTimer = this->spawnTimerMax;
	this->maxBalls = 30;
	this->points = 0;
}

void Game::initWindow()
{
	this->videoMode = sf::VideoMode(800, 600);
	this->window = new sf::RenderWindow(this->videoMode, "Game 2",
		sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

void Game::initFont()
{
	if (!this->font.loadFromFile("fonts/Dosis-Light.ttf"))
	{
		std::cerr << "GAME::INITFONT::CAN'T LODA FROM FILE\n";
	}
}

void Game::initText()
{
	// Gui text initialization
	this->guiText.setFont(this->font);
	this->guiText.setFillColor(sf::Color::White);
	this->guiText.setCharacterSize(24);
	this->guiText.setLetterSpacing(2.f);
	this->guiText.setOutlineColor(sf::Color::White);
	this->guiText.setOutlineThickness(1.f);

	// End game text
	this->endGameText.setFont(this->font);
	this->endGameText.setFillColor(sf::Color::Red);
	this->endGameText.setCharacterSize(60);
	this->endGameText.setLetterSpacing(3.f);
	this->endGameText.setOutlineColor(sf::Color::Red);
	this->endGameText.setOutlineThickness(3.f);
	this->endGameText.setPosition(sf::Vector2f(0.f, 90.f));
	this->endGameText.setString("GAME OVER");
}

// Constructors and destructor
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFont();
	this->initText();
}

Game::~Game()
{
	delete this->window;
}

// Accessors
const bool& Game::getEndGame() const
{
	return this->endGame;
}

// Methods
const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->sfmlEvent))
	{
		switch (this->sfmlEvent.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::spawnBalls()
{
	// Timer
	if (this->spawnTimer < this->spawnTimerMax)
		this->spawnTimer += 1.f;
	else
	{
		if (this->balls.size() < this->maxBalls)
		{
			this->balls.push_back(Ball(*this->window,
				this->randBallType()));
			this->spawnTimer = 0.f;
		}
	}
}

const int Game::randBallType() const
{
	int type = ballTypes::DEFAULT;

	int randValue = rand() % 100 + 1;
	if (randValue > 60 && randValue <= 80)
		type = ballTypes::DAMAGING;
	else if (randValue > 80 && randValue <= 100)
		type = ballTypes::HEALING;

	return type;
	
}

void Game::updatePlayer()
{
	this->player.update(this->window);

	if (this->player.getHp() <= 0)
		this->endGame = true;
}

void Game::updateCollision()
{
	// Check the collision
	for (size_t i = 0; i < this->balls.size(); i++)
	{
		if (this->player.getShape().getGlobalBounds().
			intersects(this->balls[i].getShape().getGlobalBounds()))
		{
			switch (this->balls[i].getType())
			{
			case ballTypes::DEFAULT:
				this->points++;
				break;
			case ballTypes::DAMAGING:
				this->player.takeDamage(3);
				break;
			case ballTypes::HEALING:
				this->player.gainHealth(1);
				break;
			}

			// Remove the ball
			this->balls.erase(this->balls.begin() + i);	
		}
	}
}

void Game::updateGui()
{
	std::stringstream ss;
	
	ss << "Points: " << this->points << "\n"
		<< "Health: " << this->player.getHp()
		<< "/" << this->player.getHpMax() << "\n";

	this->guiText.setString(ss.str());
}

void Game::update()
{
	this->pollEvents();

	if (this->endGame == false)
	{
		this->spawnBalls();
		this->updatePlayer();
		this->updateCollision();
	}
	this->updateGui();
}

void Game::renderGui(sf::RenderTarget* target)
{
	target->draw(this->guiText);
}

void Game::render()
{
	this->window->clear();
	
	// Render stuff
	this->player.render(this->window);

	for (auto x : this->balls)
	{
		x.render(*this->window);
	}

	// Render gui
	this->renderGui(this->window);

	// Render end text
	if (this->endGame)
		this->window->draw(this->endGameText);

	this->window->display();
}

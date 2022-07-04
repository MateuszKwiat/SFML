#include "Ball.h"

// Private methods
void Ball::initShape(const sf::RenderWindow& window)
{
	this->shape.setRadius(static_cast<float>(rand() % 10 + 10));

	sf::Color color;
	switch (this->type)
	{
	case DEFAULT:
		color = sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
		this->shape.setOutlineColor(sf::Color::White);
		break;
	case DAMAGING:
		color = sf::Color::Red;
		this->shape.setOutlineColor(sf::Color::Magenta);
		break;
	case HEALING:
		color = sf::Color::Green;
		this->shape.setOutlineColor(sf::Color::Cyan);
		break;
	}

	this->shape.setFillColor(color);
	this->shape.setOutlineThickness(3.f);
	this->shape.setPosition(sf::Vector2f
		(static_cast<float>(rand() % window.getSize().x 
			- this->shape.getGlobalBounds().width), 
		static_cast<float>(rand() % window.getSize().y
			- this->shape.getGlobalBounds().height)));
}

// Constructor and destructor
Ball::Ball(const sf::RenderWindow& window, int type)
	: type(type)
{
	
	this->initShape(window);
}

Ball::~Ball()
{
}

// Accessors
const sf::CircleShape& Ball::getShape() const
{
	return this->shape;
}

const int& Ball::getType() const
{
	return this->type;
}

// Methods
void Ball::update()
{
}

void Ball::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}

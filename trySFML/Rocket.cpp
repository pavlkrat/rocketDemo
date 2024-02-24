#include "Rocket.h"

Rocket::Rocket(const sf::Texture& texture, const sf::Vector2f& position, float xSpeed, float ySpeed, const sf::Vector2u& windowSize)
{
	rocketSprite.setTexture(texture);
	rocketSprite.setPosition(position);

	this->windowX = windowSize.x;
	this->windowY = windowSize.y;

	this->xSpeed = std::abs(xSpeed);
	if (xSpeed < 0)
	{
		xDirection = false;
		flipTexture();
	}
	else
		xDirection = true;

	this->ySpeed = std::max(ySpeed, 0.f);
}

void Rocket::Update(float deltaTime)
{
	if (xDirection)
		MoveRight(xSpeed * deltaTime * xSpeedCoef, deltaTime);
	else
		MoveLeft(xSpeed * deltaTime * xSpeedCoef, deltaTime);
}

void Rocket::MoveUp(float deltaTime)
{
	rocketSprite.move(sf::Vector2f(0, -std::min(ySpeed * deltaTime * ySpeedCoef, checkUp())));
}

void Rocket::MoveDown(float deltaTime)
{
	rocketSprite.move(sf::Vector2f(0, std::min(ySpeed * deltaTime * ySpeedCoef, checkDown())));
}

void Rocket::MoveLeft(float need, float deltaTime)
{
	float possible = checkLeft();
	rocketSprite.move(sf::Vector2f(-std::min(need, possible), 0));
	if (possible < need)
	{
		reverseDirection();
		MoveRight(need - possible, deltaTime);
	}
}

void Rocket::MoveRight(float need, float deltaTime)
{
	float possible = checkRight();
	rocketSprite.move(sf::Vector2f(std::min(need, possible), 0));
	if (possible < need)
	{
		reverseDirection();
		MoveLeft(need - possible, deltaTime);
	}
}

sf::Sprite Rocket::getSprite()
{
	return rocketSprite;
}

void Rocket::reverseDirection()
{
	xDirection ^= true;
	flipTexture();
}

void Rocket::flipTexture()
{
	auto rect = rocketSprite.getTextureRect();
	rect.left += rect.width;
	rect.width = -rect.width;
	rocketSprite.setTextureRect(rect);
}

float Rocket::checkUp()
{
	return std::max(rocketSprite.getPosition().y, 0.f);
}

float Rocket::checkDown()
{
	return std::max(windowY - (rocketSprite.getPosition().y + rocketSprite.getGlobalBounds().height), 0.f);
}

float Rocket::checkLeft()
{
	return std::max(rocketSprite.getPosition().x, 0.f);
}

float Rocket::checkRight()
{
	return std::max(windowX - (rocketSprite.getPosition().x + rocketSprite.getGlobalBounds().width), 0.f);
}

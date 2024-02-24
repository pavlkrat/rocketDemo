#include <SFML/Graphics.hpp>

#pragma once
class Rocket
{
public:
	Rocket(const sf::Texture &texture, const sf::Vector2f &position, float xSpeed, float ySpeed, const sf::Vector2u &windowSize);

	void Update(float deltaTime);
	void MoveUp(float deltaTime);
	void MoveDown(float deltaTime);

	sf::Sprite getSprite();
private:
	const float xSpeedCoef = 100;
	const float ySpeedCoef = 70;
	sf::Sprite rocketSprite;
	float xSpeed;
	float ySpeed;
	int windowX;
	int windowY;
	bool xDirection;

	void reverseDirection();
	void flipTexture();
	float checkUp();
	float checkDown();
	float checkLeft();
	float checkRight();
	void MoveLeft(float need, float deltaTime);
	void MoveRight(float need, float deltaTime);
};


#include <SFML/Graphics.hpp>
#include "Rocket.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), L"ятлк", sf::Style::Close);
    window.setFramerateLimit(120);

    sf::Clock fpsClock;

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("images/space.jpg"))
        return 1;
    sf::Sprite background(backgroundTexture, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(window.getSize())));

    sf::Texture rocketTexture;
    if (!rocketTexture.loadFromFile("images/rocket.png"))
        return 1;
    Rocket rocket(rocketTexture, sf::Vector2f(300, 100), -7, 8, window.getSize());

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = fpsClock.restart().asSeconds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            rocket.MoveUp(deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            rocket.MoveDown(deltaTime);
        rocket.Update(deltaTime);

        window.clear();

        window.draw(background);
        window.draw(rocket.getSprite());

        window.display();
    }

    return 0;
}
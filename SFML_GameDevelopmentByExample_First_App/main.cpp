#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game.h"
void main(int argc, char** argv[])
{
	{
	//sf::RenderWindow window(sf::VideoMode(640, 480), "First Window!");

	////Adding a rectangle to the window
	//sf::RectangleShape rectangle(sf::Vector2f(128.0f, 128.9f));
	//rectangle.setFillColor(sf::Color::Red);
	//rectangle.setPosition(320, 240);
	//rectangle.setOrigin(rectangle.getSize().x/2, rectangle.getSize().y/2);

	////Loading a texture from memory...
	//sf::Texture texture;
	//if (!texture.loadFromFile("Resources/Textures/MarioMushroom.png"))
	//{
	//	//Handle an error
	//	std::cout << "Error, texture can't be loaded for some reason!" << std::endl;
	//}


	////Creating a sprite 
	//sf::Sprite sprite(texture);
	//sf::Vector2u size = texture.getSize();
	//sprite.setOrigin(size.x / 2, size.y / 2);
	//sprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	////sprite.setScale(.1f, .1f);
	//sf::Vector2f increment(.1f, .1f);

	}

	Game game;
	


	while (!game.GetWindow()->IsDone())
	{
		game.HandleInput();
		game.Update();
		game.Render();
		game.LastUpdate();
	}
}
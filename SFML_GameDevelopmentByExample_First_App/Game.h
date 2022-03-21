#pragma once
#include "Window.h"

#include "World.h"
#include "Snake.h"

//Adding textbox to the game class
#include "TextBox.h"
#include "StateManager.h"
#include "EventManager.h"
#include "TextureManager.h"
#include "SharedContext.h"
#include <iostream>
class Game
{
public:

	Game();
	~Game();

	void HandleInput();
	void Update();
	void Render();

	sf::Time GetElapsed();
	void RestartClock();


	Window* GetWindow();

	//Moving a sprite revisited
	void MoveSprite(EventDetails* l_details);

	void LastUpdate();


private:
	void MoveMushroom();
	Window m_window;

	sf::Texture m_mushroomTexture;
	sf::Sprite m_mushroom;
	sf::Vector2i m_increment;

	//Time Variables
	sf::Clock m_clock;
	sf::Time m_elapsed;


	//World
	World m_world;
	//Snake
	Snake m_snake;

	//TextBox
	TextBox m_textbox;

	//StateManager instance
	StateManager m_stateManager;

	//SharedContext
	SharedContext m_sharedContext;

	//EntityManager
	EntityManager m_entityManager;

	TextureManager m_textureManager;
	
};


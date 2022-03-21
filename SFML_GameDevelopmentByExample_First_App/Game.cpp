#include "Game.h"
Game::Game() :
	m_snake(m_world.GetBlockSize()), 
	m_world(sf::Vector2u(800, 600)),
	m_stateManager(&m_sharedContext),
	m_entityManager(&m_sharedContext, 100)
{
	m_mushroomTexture.loadFromFile("Resources/Textures/MarioMushroom.png");
	m_mushroom.setTexture(m_mushroomTexture);
	m_mushroom.setOrigin(m_mushroomTexture.getSize().x/2, m_mushroomTexture.getSize().y / 2);
	m_increment = sf::Vector2i(400, 400);

	//m_window.GetEventManager()->AddCallback("Move", &Game::MoveSprite, this);

	m_textbox.Setup(5, 14, 350, sf::Vector2f(255, 0));
	m_textbox.Add("Seeded with random number generator with: " + std::to_string(time(NULL)));

	//SharedContext
	m_sharedContext.m_wind = &m_window;
	m_sharedContext.m_eventManager = m_window.GetEventManager();
	m_sharedContext.m_textureManager = &m_textureManager;
	m_sharedContext.m_entityManager = &m_entityManager;
	m_stateManager.SwitchTo(StateType::Intro);

}

Game::~Game()
{
}

void Game::HandleInput()
{
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) 
	//	&& m_snake.GetPhysicalDirection() != Direction::Down)
	//{
	//	m_snake.SetDirection(Direction::Up);
	//}
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
	//	&& m_snake.GetPhysicalDirection() != Direction::Up)
	//{
	//	m_snake.SetDirection(Direction::Down);
	//}
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
	//	m_snake.GetPhysicalDirection() != Direction::Right)
	//{
	//	m_snake.SetDirection(Direction::Left);
	//}
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
	//	m_snake.GetPhysicalDirection() != Direction::Left)
	//{
	//	m_snake.SetDirection(Direction::Right);
	//}
}

void Game::Update()
{
	m_window.Update();	//Update the window events
	/*MoveMushroom();*/




	//float timestep = 1.0f / m_snake.GetSpeed();
	//if (m_elapsed.asSeconds() >= timestep)
	//{
	//	m_world.Update(m_snake);
	//	//m_snake.Tick();
	//	m_elapsed -= sf::seconds(timestep);
	//	//if (m_snake.HasLost())
	//	//{
	//	//	m_snake.Reset();
	//	//}
	//		
	//}
	//Invoking the StateManager Update method
	m_stateManager.Update(m_elapsed);


}

void Game::Render()
{
	m_window.BeginDraw();	//Clear.#
	//Render Here
	m_world.Render(*m_window.GetRenderWindow());
	//m_snake.Render(*m_window.GetRenderWindow());

	//Invoking the StateManager draw method
	m_stateManager.Draw();

	//Textbox render
	//m_textbox.Render(*m_window.GetRenderWindow());
	//m_window.Draw(m_mushroom);
	m_window.EndDraw();		//Display;



}

sf::Time Game::GetElapsed()
{
	return m_elapsed;
}

void Game::RestartClock()
{
	m_elapsed = m_clock.restart();
}

Window * Game::GetWindow()
{
	return &m_window;
}

void Game::MoveSprite(EventDetails * l_details)
{
	sf::Vector2i mousePos =
		m_window.GetEventManager()->GetMousePos(
			m_window.GetRenderWindow());
	m_mushroom.setPosition(mousePos.x, mousePos.y);
	std::cout << "Moiving sprite to: " <<
		mousePos.x << ":" << mousePos.y << std::endl;
}

void Game::LastUpdate()
{
	m_stateManager.ProcessRequests();
	RestartClock();

}

void Game::MoveMushroom()
{
	sf::Vector2u l_windSize = m_window.GetWindowSize();
	sf::Vector2u l_textSize = m_mushroomTexture.getSize();

	if (m_mushroom.getPosition().x > l_windSize.x - l_textSize.x
		&& m_increment.x > 0 || (m_mushroom.getPosition().x < 0 
			&& m_increment.x < 0))
	{
		m_increment.x = -m_increment.x;

	}


	if (m_mushroom.getPosition().y > l_windSize.y - l_textSize.y
		&& m_increment.y > 0 || (m_mushroom.getPosition().y < 0
			&& m_increment.y < 0))
	{
		m_increment.y = -m_increment.y;

	}

	float fElapsed = m_elapsed.asSeconds();

	m_mushroom.setPosition(
		m_mushroom.getPosition().x + (m_increment.x * fElapsed),
		m_mushroom.getPosition().y + (m_increment.y * fElapsed));

}


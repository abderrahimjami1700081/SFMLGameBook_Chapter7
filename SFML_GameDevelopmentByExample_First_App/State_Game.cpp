#include "State_Game.h"
#include "StateManager.h"
State_Game::State_Game(StateManager* l_stateManager)
	: BaseState(l_stateManager) {}

State_Game::~State_Game()
{
}

void State_Game::OnCreate()
{
	m_texture.loadFromFile("Resources/Textures/MarioMushroom.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(0,0);
	m_increment = sf::Vector2f(400.0f, 400.0f);

	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
	evMgr->AddCallback(StateType::Game, "Key_Escape",
		&State_Game::MainMenu, this);
	evMgr->AddCallback(StateType::Game, "Key_P",
		&State_Game::Pause, this);
	
	
	//Chapter 7 map edits
	sf::Vector2u size = m_stateMgr->GetContext()->m_wind->GetWindowSize();
	m_view.setSize(size.x, size.y);
	m_view.setCenter(size.x/2, size.y/2);
	m_view.zoom(.6f);
	m_stateMgr->GetContext()->m_wind->GetRenderWindow()->setView(m_view);



}

void State_Game::OnDestroy()
{
	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
	evMgr->RemoveCallback(StateType::Game, "Key_Escape");
	evMgr->RemoveCallback(StateType::Game, "Key_P");

	//Chapter 7 map
	delete m_gameMap;
	m_gameMap = nullptr;

}

void State_Game::Activate()
{
}

void State_Game::Deactivate()
{
}

void State_Game::Update(const sf::Time & l_time)
{
	{
		//sf::Vector2u l_windSize = m_stateMgr->GetContext()->
		//	m_wind->GetWindowSize();
		//sf::Vector2u l_textSize = m_texture.getSize();

		//if ((m_sprite.getPosition().x > l_windSize.x - l_textSize.x &&
		//	m_increment.x > 0) || (m_sprite.getPosition().x < 0 &&
		//		m_increment.x < 0))
		//{
		//	m_increment.x = -m_increment.x;
		//}

		//if ((m_sprite.getPosition().y > l_windSize.y - l_textSize.y &&
		//	m_increment.y > 0) || (m_sprite.getPosition().y < 0 &&
		//		m_increment.y < 0))
		//{
		//	m_increment.y = -m_increment.y;
		//}

		//m_sprite.setPosition(m_sprite.getPosition().x +
		//	(m_increment.x * l_time.asSeconds()), 
		//	m_sprite.getPosition().y + 
		//	(m_increment.y * l_time.asSeconds()));

	}

	SharedContext* context = m_stateMgr->GetContext();
	//We first try to find the player in the entity list 
	EntityBase* player = context->m_entityManager->Find("Player");;
	if (!player)
	{
		//If it's no there then they must be dead, so we have to respawn them
		std::cout << "Respwaning player..." << std::endl;	
		context->m_entityManager->Add(EntityType::Player, "Player");
		player = context->m_entityManager->Find("Player");
		player->SetPosition(m_gameMap->GetPlayerStart());
	}
	else
	{
		m_view.setCenter(player->GetPosition());
		context->m_wind->GetRenderWindow()->setView(m_view);
	}

	sf::FloatRect viewSpace = context->m_wind->GetViewSpace();
	if (viewSpace.left <= 0)
	{
		m_view.setCenter(viewSpace.width/2, m_view.getCenter().y);
		context->m_wind->GetRenderWindow()->setView(m_view);
	}
	else if (viewSpace.left + viewSpace.width > 
		(m_gameMap->GetMapSize().x + 1) * Sheet::Tile_Size)
	{
		m_view.setCenter(((m_gameMap->GetMapSize().x + 1) * 
		Sheet::Tile_Size) - (viewSpace.width/2), m_view.getCenter().y);
		context->m_wind->GetRenderWindow()->setView(m_view);
	}

	m_gameMap->Update(l_time.asSeconds());
	m_stateMgr->GetContext()->m_entityManager->Update(l_time.asSeconds());


}

void State_Game::Draw()
{
	m_stateMgr->GetContext()->m_wind->GetRenderWindow()->
		draw(m_sprite);


}

void State_Game::MainMenu(EventDetails * l_details)
{
	m_stateMgr->SwitchTo(StateType::MainMenu);

}

void State_Game::Pause(EventDetails * l_details)
{
	m_stateMgr->SwitchTo(StateType::Paused);

}

#pragma once
#include "Window.h"
#include "TextureManager.h"
#include "EventManager.h"
#include "Map.h"
#include "EntityManager.h"
struct SharedContext
{
	SharedContext() :
		m_wind(nullptr), 
		m_eventManager(nullptr), 
		m_textureManager(nullptr),
		m_entityManager(nullptr),
		m_gameMap(nullptr){}
	Window* m_wind;
	Map* m_gameMap;
	EventManager* m_eventManager;
	EntityManager* m_entityManager;
	TextureManager* m_textureManager;
};

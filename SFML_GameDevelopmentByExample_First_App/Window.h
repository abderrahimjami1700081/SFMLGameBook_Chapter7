#pragma once
#include <string>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "EventManager.h"
class Window
{
public:

	Window(const std::string& l_title, 
		const sf::Vector2u& l_size);
	Window();

	void BeginDraw();	//Clear the window
	void EndDraw();		//Display the changes

	void Update();

	bool IsDone();
	bool isFullscreen();
	sf::Vector2u GetWindowSize();

	void ToggleFullscreen();
	void Draw(sf::Drawable& l_drawable);

	sf::RenderWindow* GetRenderWindow() { return &m_window; }

	bool IsFocused();
	EventManager* GetEventManager();
	void ToggleFullscreen(EventDetails* l_details);
	void Close(EventDetails* l_details = nullptr);

	sf::FloatRect GetViewSpace();



private:

	void Setup(const std::string& l_title,
		const sf::Vector2u& l_size);

	void Destroy();
	void Create();


	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;
	bool m_isFullscreen;


	//EventManager 
	EventManager m_eventManager;
	bool m_isFocused;
};


#include "Window.h"

Window::Window(const std::string & l_title, const sf::Vector2u & l_size)
{
	m_windowTitle = l_title;
	m_windowSize = l_size;
	m_isFullscreen = false;
	m_isDone = false;
	Create();
}

Window::Window()
{
	Setup("Window", sf::Vector2u(800, 600));
}


bool Window::IsFocused() 
{
	return m_isFocused; 
}

EventManager* Window::GetEventManager() 
{ 
	return &m_eventManager; 
}

void Window::ToggleFullscreen(EventDetails* l_details) 
{
	m_isFullscreen = !m_isFullscreen;
	m_window.close();
	Create();
}

void Window::Close(EventDetails* l_details) { m_isDone = true; }

sf::FloatRect Window::GetViewSpace()
{
	sf::Vector2f viewCenter = m_window.getView().getCenter();
	sf::Vector2f viewSize = m_window.getView().getSize();
	sf::Vector2f viewSizeHalf(viewSize.x / 2, viewSize.y / 2);
	sf::FloatRect viewSpace(viewCenter - viewSizeHalf, viewSize);
	return viewSpace;
}

void Window::BeginDraw()
{
	m_window.clear(sf::Color::Black);
}

void Window::EndDraw()
{
	m_window.display();
}


void Window::Create()
{
	sf::Uint32 style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	m_window.create({ m_windowSize.x, m_windowSize.y, 32 }, m_windowTitle, style);


}


void Window::Setup(const std::string & l_title, const sf::Vector2u & l_size)
{
	m_windowTitle = l_title;
	m_windowSize = l_size;
	m_isFullscreen = false;
	m_isDone = false;
	Create();
	m_isFocused = true;
	m_eventManager.AddCallback(StateType(0), "Fullscreen_toggle",
		&Window::ToggleFullscreen, this);
	m_eventManager.AddCallback(StateType(0), "Window_close",
		&Window::Close, this);

	Create();

}

void Window::Destroy()
{	
	m_window.close();
}

void Window::Update()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::LostFocus)
		{
			m_isFocused = false;
			m_eventManager.SetFocus(false);
		}
		else if (event.type == sf::Event::GainedFocus)
		{
			m_isFocused = true;
			m_eventManager.SetFocus(true);
		}
		m_eventManager.HandleEvent(event);


		//if (event.type == sf::Event::Closed)
		//{
		//	m_isDone = true;
		//}
		//else if (event.type == sf::Event::KeyPressed 
		//	&& event.key.code == sf::Keyboard::F5)
		//{
		//	ToggleFullscreen();
		//}
	}

	m_eventManager.Update();

}

bool Window::IsDone()
{
	return m_isDone;
}

bool Window::isFullscreen()
{
	return m_isFullscreen;
}

sf::Vector2u Window::GetWindowSize()
{
	return m_windowSize;
}

void Window::ToggleFullscreen()
{
	m_isFullscreen = !m_isFullscreen;
	Destroy();
	Create();

}

void Window::Draw(sf::Drawable & l_drawable)
{
	m_window.draw(l_drawable);
}

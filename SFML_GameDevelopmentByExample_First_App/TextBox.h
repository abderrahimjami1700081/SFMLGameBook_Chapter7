#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
using MessageContainer = std::vector<std::string>;


class TextBox
{

public:
	TextBox();
	TextBox(int l_visible, int l_charSize,
		int l_width, sf::Vector2f l_screenPos);


	~TextBox();

	void Setup(int l_visible, int l_charSize,
		int l_width, sf::Vector2f l_screenPos);

	void Render(sf::RenderWindow& l_wind);
	void Add(std::string l_message);
	void Clear();

private:
	MessageContainer m_messages;
	int m_numVisible;

	sf::RectangleShape m_backdrop;
	sf::Font m_font;
	sf::Text m_content;
};


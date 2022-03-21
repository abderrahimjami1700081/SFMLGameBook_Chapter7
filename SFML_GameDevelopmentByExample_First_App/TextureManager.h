#pragma once
#include "ResourceManager.h"
#include <SFML/Graphics/Texture.hpp>
class TextureManager :
	public ResourceManager<TextureManager, sf::Texture>
{
public:
	//This constructor call to the parent class will call LoadPaths
	//Which will load all the textures paths from textures.cfg
	TextureManager(): ResourceManager("textures.cfg") {}

	sf::Texture* Load(const std::string& l_path)
	{
		sf::Texture* texture = new sf::Texture();
		if (!texture->loadFromFile(
				Utils::GetWorkingDirectory() + l_path))
		{
			delete texture;
			texture = nullptr;
			std::cerr << "! Failed to load the texture: "
				<< l_path << std::endl;
		}

		return texture;
	}


};


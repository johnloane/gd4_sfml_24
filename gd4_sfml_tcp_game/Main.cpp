#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <iostream>

int main()
{
	ResourceHolder<TextureID, sf::Texture> game_textures;
	try
	{
		game_textures.Load(TextureID::kEagle, "Media/Textures/Eagle.png");
	}
	catch(std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
	}
	Game game(game_textures);
	game.Run();
}
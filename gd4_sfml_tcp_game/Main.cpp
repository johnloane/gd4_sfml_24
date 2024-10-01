#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "ResourceIdentifiers.hpp"
#include <iostream>

int main()
{
	//TextureHolder game_textures;
	try
	{
		Game game;
		game.Run();
	}
	catch(std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
	}
}
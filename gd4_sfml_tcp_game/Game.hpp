#pragma once
#include <SFML/Graphics.hpp>
#include "World.hpp"

class Game
{
	public:
		Game();
		void Run();

	private:
		void ProcessEvents();
		void Update(sf::Time delta_time);
		void Render();
		//void HandlePlayerInput(sf::Keyboard::Key key, bool is_pressed);

	private:

		/*ResourceHolder<TextureID, sf::Texture>& m_textures;
		sf::RenderWindow m_window;
		
		sf::Sprite m_player;
		bool m_is_moving_up = false;
		bool m_is_moving_down = false;
		bool m_is_moving_right = false;
		bool m_is_moving_left = false;*/
		static const sf::Time kTimePerFrame;
		sf::RenderWindow m_window;
		World m_world;
};
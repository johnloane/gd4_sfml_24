#pragma once
#include <SFML/Graphics.hpp>
class Utility
{
	public:
		static sf::Vector2f Normalise(const sf::Vector2f& source);
		static void CentreOrigin(sf::Sprite& sprite);
		static void CentreOrigin(sf::Text& text);
};


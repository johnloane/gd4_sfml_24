#pragma once
#include "TextureID.hpp"
#include "Font.hpp"

namespace sf
{
	class Texture;
	class Font;
}

template<typename Identifier, typename Resource>
class ResourceHolder;

typedef ResourceHolder<TextureID, sf::Texture> TextureHolder;
typedef ResourceHolder <Font, sf::Font > FontHolder;
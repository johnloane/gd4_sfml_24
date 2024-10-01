#pragma once
#include "TextureID.hpp"

namespace sf
{
	class Texture;
}

template<typename Identifier, typename Resource>
class ResourceHolder;

typedef ResourceHolder<TextureID, sf::Texture> TextureHolder;
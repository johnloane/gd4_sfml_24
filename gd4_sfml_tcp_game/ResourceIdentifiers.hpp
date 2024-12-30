#pragma once
#include "TextureID.hpp"
#include "Font.hpp"
#include "ShaderTypes.hpp"

namespace sf
{
	class Texture;
	class Font;
	class Shader;
}

template<typename Identifier, typename Resource>
class ResourceHolder;

typedef ResourceHolder<TextureID, sf::Texture> TextureHolder;
typedef ResourceHolder <Font, sf::Font > FontHolder;
typedef ResourceHolder<ShaderTypes, sf::Shader> ShaderHolder;
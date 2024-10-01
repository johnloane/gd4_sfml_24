#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceIdentifiers.hpp"
#include "ResourceHolder.hpp"
#include "SceneNode.hpp"
#include "SceneLayers.hpp"
#include "Aircraft.hpp"
#include "TextureID.hpp"
#include "SpriteNode.hpp"

#include <array>

class World : private sf::NonCopyable
{
public:
	explicit World(sf::RenderWindow& window);
	void Update(sf::Time dt);
	void Draw();

private:
	void LoadTextures();
	void BuildScene();

private:
	sf::RenderWindow& m_window;
	sf::View m_camera;
	TextureHolder m_textures;
	SceneNode m_scenegraph;
	std::array<SceneNode*, static_cast<int>(SceneLayers::kLayerCount)> m_scene_layers;
	sf::FloatRect m_world_bounds;
	sf::Vector2f m_spawn_position;
	float m_scrollspeed;
	Aircraft* m_player_aircraft;
};


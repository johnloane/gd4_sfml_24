#pragma once
#include <vector>
#include <SFML/System/Time.hpp>
#include "ResourceIdentifiers.hpp"
#include <functional>
#include "Aircraft.hpp"


struct Direction
{
	Direction(float angle, float distance)
		: m_angle(angle), m_distance(distance) {}
	float m_angle;
	float m_distance;
};

struct AircraftData
{
	int m_hitpoints;
	float m_speed;
	TextureID m_texture;
	sf::Time m_fire_interval;
	std::vector<Direction> m_directions;
};

struct ProjectileData
{
	int m_damage;
	float m_speed;
	TextureID m_texture;
};

struct PickupData
{
	std::function<void(Aircraft&)> m_action;
	TextureID m_texture;
};

std::vector<AircraftData> InitializeAircraftData();
std::vector<ProjectileData> InitializeProjectileData();
std::vector<PickupData> InitializePickupData();


#pragma once
#include <functional>
#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>

#include "ResourceIdentifiers.hpp"

class Aircraft;

struct Direction
{
	Direction(float angle, float distance)
		: m_angle(angle), m_distance(distance)
	{
	}
	float m_angle;
	float m_distance;
};

struct AircraftData
{
	int m_hitpoints;
	float m_speed;
	Textures m_texture;
	sf::Time m_fire_interval;
	std::vector<Direction> m_directions;
};

/// <summary>
/// Written by: Antanas Zalisauskas
///
///	Data related to a character
/// </summary>

/// <summary>
/// edited by: Patrick Nugent
///
///	Added directions field
/// </summary>
struct CharacterData
{
	int m_hitpoints;
	float m_speed;
	float m_jump_height;
	Textures m_texture;
	std::vector<Direction> m_directions;
};

struct PlatformData
{
	Textures m_texture;
};

struct ProjectileData
{
	int m_damage;
	float m_speed;
	Textures m_texture;
};

struct PickupData
{
	std::function<void(Aircraft&)> m_action;
	Textures m_texture;
};

std::vector<AircraftData> InitializeAircraftData();
std::vector<CharacterData> InitializeCharacterData();
std::vector<ProjectileData> InitializeProjectileData();
std::vector<PickupData> InitializePickupData();
std::vector<PlatformData> InitializePlatformData();



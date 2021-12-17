#pragma once
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "SpriteNode.hpp"
#include "Aircraft.hpp"
#include "Layers.hpp"
#include "AircraftType.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <array>

#include "Character.hpp"
#include "CommandQueue.hpp"

//Foward
namespace sf
{
	class RenderWindow;
}

/// <summary>
/// Edited By: Patrick Nugent
///
///	Reworked to use Character class instead of Aircraft
/// </summary>
class World : private sf::NonCopyable
{
public:
	explicit World(sf::RenderWindow& window, FontHolder& font);
	void Update(sf::Time dt);
	void Draw();
	CommandQueue& getCommandQueue();

private:
	void LoadTextures();
	void BuildScene();
	void AdaptPlayerPosition();
	void AdaptPlayerVelocity();

	sf::FloatRect GetViewBounds() const;
	sf::FloatRect GetBattlefieldBounds() const;
	void SpawnEnemies();
	void AddEnemy(CharacterType type, float relX, float relY);
	void AddEnemies();
	void GuideMissiles();
	void HandleCollisions();
	void DestroyEntitiesOutsideView();

private:
	struct SpawnPoint
	{
		SpawnPoint(CharacterType type, float x, float y) : m_type(type), m_x(x), m_y(y)
		{
			
		}
		CharacterType m_type;
		float m_x;
		float m_y;
	};
	

private:
	sf::RenderWindow& m_window;
	sf::View m_camera;
	TextureHolder m_textures;
	FontHolder& m_fonts;
	SceneNode m_scenegraph;
	std::array<SceneNode*, static_cast<int>(Layers::kLayerCount)> m_scene_layers;
	CommandQueue m_command_queue;

	sf::FloatRect m_world_bounds;
	sf::Vector2f m_spawn_position;
	float m_scrollspeed;
	Aircraft* m_player_aircraft;
	std::vector<SpawnPoint> m_enemy_spawn_points;
	std::vector<Character*>	m_active_enemies;
	Character* m_player_character_1;
	Character* m_player_character_2;
	float m_gravity;
};


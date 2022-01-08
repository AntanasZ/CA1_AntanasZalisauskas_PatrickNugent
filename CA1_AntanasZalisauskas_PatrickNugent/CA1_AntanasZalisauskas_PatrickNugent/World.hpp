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
#include "PickupType.hpp"

//Foward
namespace sf
{
	class RenderWindow;
}

/// <summary>
/// Edited By: Patrick Nugent
///
///	-Reworked to use Character class instead of Aircraft
/// -Added spawn countdown field
/// -Created separate character and pickup spawn point structs
/// -Added methods for adding and spawning pickups
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
	void AdaptPlayerVelocity(sf::Time dt);

	sf::FloatRect GetViewBounds() const;
	sf::FloatRect GetBattlefieldBounds() const;
	void SpawnEnemies();
	void SpawnFlyingEnemies();
	void SpawnPickups();
	void AddEnemy(CharacterType type, bool isFlying, float relX, float relY);
	void AddPickup(PickupType type, int value, float relX, float relY);
	void AddEnemies();
	void AddPickups();
	void GuideMissiles();
	void HandleCollisions();
	void DestroyEntitiesOutsideView();
	void DisplayRemainingGameTime();
	bool IsGameOver() const;

private:
	struct CharacterSpawnPoint
	{
		CharacterSpawnPoint(CharacterType type, float x, float y) : m_type(type), m_x(x), m_y(y)
		{
			
		}
		CharacterType m_type;
		float m_x;
		float m_y;
	};

	struct PickupSpawnPoint
	{
		PickupSpawnPoint(PickupType type, int value, float x, float y) : m_type(type), m_value(value), m_x(x), m_y(y)
		{

		}
		PickupType m_type;
		int m_value;
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
	std::vector<CharacterSpawnPoint> m_enemy_spawn_points;
	std::vector<CharacterSpawnPoint> m_flying_enemy_spawn_points;
	std::vector<PickupSpawnPoint> m_pickup_spawn_points;
	std::vector<Character*>	m_active_enemies;
	Character* m_player_character_1;
	Character* m_player_character_2;
	float m_gravity;
	sf::Time m_enemy_spawn_countdown;
	sf::Time m_flying_enemy_spawn_countdown;
	sf::Time m_pickup_spawn_countdown;
	sf::Time m_player_1_stun_countdown;
	sf::Time m_player_2_stun_countdown;
	sf::Time m_game_countdown;
	TextNode* m_game_timer_display;
	bool m_game_over;
};


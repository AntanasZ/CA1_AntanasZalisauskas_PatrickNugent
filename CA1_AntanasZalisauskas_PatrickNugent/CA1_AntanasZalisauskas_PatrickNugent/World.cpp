#include "World.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <limits>
#include <stdlib.h>

#include "Pickup.hpp"
#include "Projectile.hpp"
#include "Utility.hpp"

World::World(sf::RenderWindow& window, FontHolder& font)
	: m_window(window)
	, m_camera(window.getDefaultView())
	, m_textures()
	, m_fonts(font)
	, m_scenegraph()
	, m_scene_layers()
	, m_world_bounds(0.f, 0.f, m_camera.getSize().x, m_camera.getSize().y)
	, m_spawn_position(m_camera.getSize().x/2.f, m_world_bounds.height - m_camera.getSize().y /2.f)
	, m_scrollspeed(-50.f)
	, m_player_aircraft(nullptr)
	, m_player_character_1(nullptr)
	, m_player_character_2(nullptr)
	, m_gravity(981.f)
	, m_spawn_countdown()
{
	LoadTextures();
	BuildScene();
	std::cout << m_camera.getSize().x << m_camera.getSize().y << std::endl;
	m_camera.setCenter(m_spawn_position);
}

void World::Update(sf::Time dt)
{
	//Scroll the world
	//m_camera.move(0, m_scrollspeed * dt.asSeconds());

	//m_player_aircraft->SetVelocity(0.f, 0.f);
	m_player_character_1->SetVelocity(0.f, m_player_character_1->GetVelocity().y);
	m_player_character_2->SetVelocity(0.f, m_player_character_2->GetVelocity().y);
	DestroyEntitiesOutsideView();
	GuideMissiles();

	

	//Forward commands to the scenegraph until the command queue is empty
	while(!m_command_queue.IsEmpty())
	{
		m_scenegraph.OnCommand(m_command_queue.Pop(), dt);
	}

	AdaptPlayerVelocity(dt);
	

	HandleCollisions();
	//Remove all destroyed entities
	m_scenegraph.RemoveWrecks();

	//Spawn an enemy every 5 seconds and reset the spawn timer
	m_spawn_countdown += dt;
	if (m_spawn_countdown >= sf::seconds(5.0f))
	{
		SpawnEnemies();
		m_spawn_countdown = sf::seconds(0.f);
	}


	//Apply movement
	m_scenegraph.Update(dt, m_command_queue);
	AdaptPlayerPosition();

	
}

void World::Draw()
{
	m_window.setView(m_camera);
	m_window.draw(m_scenegraph);
}

/// <summary>
/// Edited by: Patrick Nugent
///
///	-Added creeper texture
/// -Added michael texture
/// </summary>
void World::LoadTextures()
{
	m_textures.Load(Textures::kEagle, "Media/Textures/Eagle.png");
	m_textures.Load(Textures::kRaptor, "Media/Textures/Raptor.png");
	m_textures.Load(Textures::kAvenger, "Media/Textures/Avenger.png");
	m_textures.Load(Textures::kShaggy, "Media/Textures/ShaggyIdle.png");
	m_textures.Load(Textures::kScooby, "Media/Textures/ScoobyIdle.png");
	//m_textures.Load(Textures::kDesert, "Media/Textures/Desert.png");
	m_textures.Load(Textures::kMansion, "Media/Textures/Mansion.png");
	m_textures.Load(Textures::kCreeper, "Media/Textures/CreeperIdle.png");
	m_textures.Load(Textures::kMichael, "Media/Textures/MichaelIdle.png");

	m_textures.Load(Textures::kBullet, "Media/Textures/Bullet.png");
	m_textures.Load(Textures::kMissile, "Media/Textures/Missile.png");
}

/// <summary>
/// Edited by: Antanas Zalisauskas
///
///	-Changed method to work with m_player_character variables and added player 1 and 2 to game
///	-Changed background texture used
/// </summary>
void World::BuildScene()
{
	//Initialize the different layers
	for (std::size_t i = 0; i < static_cast<int>(Layers::kLayerCount); ++i)
	{
		Category::Type category = (i == static_cast<int>(Layers::kAir)) ? Category::Type::kScene : Category::Type::kNone;
		SceneNode::Ptr layer(new SceneNode(category));
		m_scene_layers[i] = layer.get();
		m_scenegraph.AttachChild(std::move(layer));
	}

	//Prepare the background
	sf::Texture& texture = m_textures.Get(Textures::kMansion);
	sf::IntRect textureRect(m_world_bounds);
	//Tile the texture to cover our world
	texture.setRepeated(true);

	//Add the background sprite to our scene
	std::unique_ptr<SpriteNode> background_sprite(new SpriteNode(texture, textureRect));
	background_sprite->setPosition(m_world_bounds.left, m_world_bounds.top);
	m_scene_layers[static_cast<int>(Layers::kBackground)]->AttachChild(std::move(background_sprite));

	//Add player character
	std::unique_ptr<Character> player1(new Character(CharacterType::kShaggy, m_textures, m_fonts));
	m_player_character_1 = player1.get();
	m_player_character_1->setPosition(m_spawn_position);
	m_scene_layers[static_cast<int>(Layers::kAir)]->AttachChild(std::move(player1));

	std::unique_ptr<Character> player2(new Character(CharacterType::kScooby, m_textures, m_fonts));
	m_player_character_2 = player2.get();
	m_player_character_2->setPosition(m_spawn_position);
	m_scene_layers[static_cast<int>(Layers::kAir)]->AttachChild(std::move(player2));

	//Add player's aircraft
	/*std::unique_ptr<Aircraft> leader(new Aircraft(AircraftType::kEagle, m_textures, m_fonts));
	m_player_aircraft = leader.get();
	m_player_aircraft->setPosition(m_spawn_position);
	m_scene_layers[static_cast<int>(Layers::kAir)]->AttachChild(std::move(leader));*/

	// //Add two escorts
	// std::unique_ptr<Aircraft> leftEscort(new Aircraft(AircraftType::kRaptor, m_textures, m_fonts));
	// leftEscort->setPosition(-80.f, 50.f);
	// m_player_aircraft->AttachChild(std::move(leftEscort));
	//
	// std::unique_ptr<Aircraft> rightEscort(new Aircraft(AircraftType::kRaptor, m_textures, m_fonts));
	// rightEscort->setPosition(80.f, 50.f);
	// m_player_aircraft->AttachChild(std::move(rightEscort));

	AddEnemies();
}

CommandQueue& World::getCommandQueue()
{
	return m_command_queue;
}

void World::AdaptPlayerPosition()
{
	//Keep the player on the screen
	sf::FloatRect view_bounds(m_camera.getCenter() - m_camera.getSize() / 2.f, m_camera.getSize());
	const float border_distance = 50.f;
	sf::Vector2f position = m_player_character_1->GetWorldPosition();
	position.x = std::max(position.x, view_bounds.left + border_distance);
	position.x = std::min(position.x, view_bounds.left + view_bounds.width - border_distance);
	position.y = std::max(position.y, view_bounds.top + border_distance);
	position.y = std::min(position.y, view_bounds.top + view_bounds.height - border_distance - 10.f);
	m_player_character_1->setPosition(position);

	position = m_player_character_2->GetWorldPosition();
	position.x = std::max(position.x, view_bounds.left + border_distance);
	position.x = std::min(position.x, view_bounds.left + view_bounds.width - border_distance);
	position.y = std::max(position.y, view_bounds.top + border_distance);
	position.y = std::min(position.y, view_bounds.top + view_bounds.height - border_distance);
	m_player_character_2->setPosition(position);

}

/// <summary>
/// Edited by: Antanas Zalisauskas
///
///	Added gravity to players
/// </summary>
void World::AdaptPlayerVelocity(sf::Time dt)
{
	//sf::Vector2f velocity = m_player_character_1->GetVelocity();
	////if moving diagonally then reduce velocity
	//if (velocity.x != 0.f && velocity.y != 0.f)
	//{
	//	m_player_character_1->SetVelocity(velocity / std::sqrt(2.f));
	//}

	//velocity = m_player_character_2->GetVelocity();
	////if moving diagonally then reduce velocity
	//if (velocity.x != 0.f && velocity.y != 0.f)
	//{
	//	m_player_character_2->SetVelocity(velocity / std::sqrt(2.f));
	//}

	//Add gravity to players
	m_player_character_1->Accelerate(0.f, m_gravity * dt.asSeconds());
	m_player_character_2->Accelerate(0.f, m_gravity * dt.asSeconds());

	//Add scrolling velocity
	//m_player_character->Accelerate(0.f, m_scrollspeed);
}

sf::FloatRect World::GetViewBounds() const
{
	return sf::FloatRect(m_camera.getCenter() - m_camera.getSize() / 2.f, m_camera.getSize());
}

/// <summary>
/// Edited By: Antanas
///	changed .top & .height to .left & .width
/// </summary>
/// <returns></returns>
sf::FloatRect World::GetBattlefieldBounds() const
{
	//Return camera bounds + a small area at the top where enemies spawn offscreen
	sf::FloatRect bounds = GetViewBounds();
	bounds.left -= 100.f;
	bounds.width += 100.f;

	return bounds;
}

/// <summary>
/// Edited By: Patrick Nugent
///
///	-Reworked to use Character class instead of aircraft
/// -Added enemy randomiser code
/// </summary>
void World::SpawnEnemies()
{
	//Spawn a random enemy from the vector of enemy spawn points
	int randomEnemy = rand() % 2;
	std::cout << randomEnemy;
	SpawnPoint spawn = m_enemy_spawn_points[randomEnemy];
	std::unique_ptr<Character> enemy(new Character(spawn.m_type, m_textures, m_fonts));
	enemy->setPosition(spawn.m_x, spawn.m_y);
	m_scene_layers[static_cast<int>(Layers::kAir)]->AttachChild(std::move(enemy));
}

void World::AddEnemy(CharacterType type, float relX, float relY)
{
	SpawnPoint spawn(type, m_spawn_position.x + relX, m_spawn_position.y - relY);
	m_enemy_spawn_points.emplace_back(spawn);
}

//***********REWORK************//

/// <summary>
/// Edited By: Patrick Nugent
///
///	-Added creeper enemy
/// -Added michael enemy
/// </summary>
void World::AddEnemies()
{
	//Add all enemies
	AddEnemy(CharacterType::kCreeper, -500.f, -332.f);
	AddEnemy(CharacterType::kMichael, -500.f, -330.f);
}
//***********REWORK************//

void World::GuideMissiles()
{
	// Setup command that stores all enemies in mActiveEnemies
	/*Command enemyCollector;
	enemyCollector.category = Category::kEnemyAircraft;
	enemyCollector.action = DerivedAction<Aircraft>([this](Aircraft& enemy, sf::Time)
	{
		if (!enemy.IsDestroyed())
			m_active_enemies.push_back(&enemy);
	});

	// Setup command that guides all missiles to the enemy which is currently closest to the player
	Command missileGuider;
	missileGuider.category = Category::kAlliedProjectile;
	missileGuider.action = DerivedAction<Projectile>([this](Projectile& missile, sf::Time)
	{
		// Ignore unguided bullets
		if (!missile.IsGuided())
			return;

		float minDistance = std::numeric_limits<float>::max();
		Aircraft* closestEnemy = nullptr;

		// Find closest enemy
		for(Aircraft * enemy :  m_active_enemies)
		{
			float enemyDistance = distance(missile, *enemy);

			if (enemyDistance < minDistance)
			{
				closestEnemy = enemy;
				minDistance = enemyDistance;
			}
		}

		if (closestEnemy)
			missile.GuideTowards(closestEnemy->GetWorldPosition());
	});

	// Push commands, reset active enemies
	m_command_queue.Push(enemyCollector);
	m_command_queue.Push(missileGuider);
	m_active_enemies.clear();*/
}

bool MatchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2)
{
	unsigned int category1 = colliders.first->GetCategory();
	unsigned int category2 = colliders.second->GetCategory();

	if(type1 & category1 && type2 & category2)
	{
		return true;
	}
	else if(type1 & category2 && type2 & category1)
	{
		std::swap(colliders.first, colliders.second);
		return true;
	}
	else
	{
		return false;
	}
}

void World::HandleCollisions()
{
	std::set<SceneNode::Pair> collision_pairs;
	m_scenegraph.CheckSceneCollision(m_scenegraph, collision_pairs);
	for(SceneNode::Pair pair : collision_pairs)
	{
		if(MatchesCategories(pair, Category::Type::kPlayerAircraft, Category::Type::kEnemyAircraft))
		{
			auto& player = static_cast<Aircraft&>(*pair.first);
			auto& enemy = static_cast<Aircraft&>(*pair.second);
			//Collision
			player.Damage(enemy.GetHitPoints());
			enemy.Destroy();
		}

		else if (MatchesCategories(pair, Category::Type::kPlayerAircraft, Category::Type::kPickup))
		{
			auto& player = static_cast<Aircraft&>(*pair.first);
			auto& pickup = static_cast<Pickup&>(*pair.second);
			//Apply the pickup effect
			pickup.Apply(player);
			pickup.Destroy();
		}

		else if (MatchesCategories(pair, Category::Type::kPlayerAircraft, Category::Type::kEnemyProjectile) || MatchesCategories(pair, Category::Type::kEnemyAircraft, Category::Type::kAlliedProjectile))
		{
			auto& aircraft = static_cast<Aircraft&>(*pair.first);
			auto& projectile = static_cast<Projectile&>(*pair.second);
			//Apply the projectile damage to the plane
			aircraft.Damage(projectile.GetDamage());
			projectile.Destroy();
		}


	}
}

void World::DestroyEntitiesOutsideView()
{
	Command command;
	command.category = Category::Type::kAircraft | Category::Type::kProjectile;
	command.action = DerivedAction<Entity>([this](Entity& e, sf::Time)
	{
		//Does the object intersect with the battlefield
		if (!GetBattlefieldBounds().intersects(e.GetBoundingRect()))
		{
			e.Destroy();
		}
	});
	m_command_queue.Push(command);
}

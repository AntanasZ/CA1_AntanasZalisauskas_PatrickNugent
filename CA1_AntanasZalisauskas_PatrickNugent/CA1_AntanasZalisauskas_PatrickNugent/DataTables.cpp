#include "DataTables.hpp"
#include "AircraftType.hpp"
#include "Aircraft.hpp"
#include "CharacterType.hpp"
#include "PickupType.hpp"
#include "ProjectileType.hpp"

std::vector<AircraftData> InitializeAircraftData()
{
	std::vector<AircraftData> data(static_cast<int>(AircraftType::kAircraftCount));

	data[static_cast<int>(AircraftType::kEagle)].m_hitpoints = 100;
	data[static_cast<int>(AircraftType::kEagle)].m_speed = 200.f;
	data[static_cast<int>(AircraftType::kEagle)].m_fire_interval = sf::seconds(1);
	data[static_cast<int>(AircraftType::kEagle)].m_texture = Textures::kEagle;

	data[static_cast<int>(AircraftType::kRaptor)].m_hitpoints = 20;
	data[static_cast<int>(AircraftType::kRaptor)].m_speed = 80.f;
	data[static_cast<int>(AircraftType::kRaptor)].m_fire_interval = sf::Time::Zero;
	data[static_cast<int>(AircraftType::kRaptor)].m_texture = Textures::kRaptor;
	//AI
	data[static_cast<int>(AircraftType::kRaptor)].m_directions.emplace_back(Direction(+45.f, 80.f));
	data[static_cast<int>(AircraftType::kRaptor)].m_directions.emplace_back(Direction(-45.f, 160.f));
	data[static_cast<int>(AircraftType::kRaptor)].m_directions.emplace_back(Direction(+45.f, 80.f));

	data[static_cast<int>(AircraftType::kAvenger)].m_hitpoints = 40;
	data[static_cast<int>(AircraftType::kAvenger)].m_speed = 50.f;
	data[static_cast<int>(AircraftType::kAvenger)].m_fire_interval = sf::seconds(2);
	data[static_cast<int>(AircraftType::kAvenger)].m_texture = Textures::kAvenger;
	//AI
	data[static_cast<int>(AircraftType::kAvenger)].m_directions.emplace_back(Direction(+45.f, 50.f));
	data[static_cast<int>(AircraftType::kAvenger)].m_directions.emplace_back(Direction(0.f, 50.f));
	data[static_cast<int>(AircraftType::kAvenger)].m_directions.emplace_back(Direction(-45.f, 100.f));
	data[static_cast<int>(AircraftType::kAvenger)].m_directions.emplace_back(Direction(0.f, 50.f));
	data[static_cast<int>(AircraftType::kAvenger)].m_directions.emplace_back(Direction(+45.f, 50.f));
	return data;
}

/// <summary>
/// Written by: Antanas Zalisauskas
///
///	Data about each character type
///	Added jump height variables to characters
/// 
/// Edited by: Patrick Nugent
///
///	-Added comments to show which characters are players 
/// -Added creeper enemy type 
/// -Added michael enemy type
/// </summary>
///	<returns>Returns a vector of CharacterData which includes info about each character type</returns>
std::vector<CharacterData> InitializeCharacterData()
{
	std::vector<CharacterData> data(static_cast<int>(CharacterType::kCharacterCount));

	//Shaggy - Player 1
	data[static_cast<int>(CharacterType::kShaggy)].m_hitpoints = 100;
	data[static_cast<int>(CharacterType::kShaggy)].m_speed = 200.f;
	data[static_cast<int>(CharacterType::kShaggy)].m_texture = Textures::kShaggy;
	data[static_cast<int>(CharacterType::kShaggy)].m_jump_height = 100.f;

	//Scooby - Player 2
	data[static_cast<int>(CharacterType::kScooby)].m_hitpoints = 100;
	data[static_cast<int>(CharacterType::kScooby)].m_speed = 200.f;
	data[static_cast<int>(CharacterType::kScooby)].m_texture = Textures::kScooby;
	data[static_cast<int>(CharacterType::kScooby)].m_jump_height = 100.f;

	//Creeper
	data[static_cast<int>(CharacterType::kCreeperLeft)].m_hitpoints = 100;
	data[static_cast<int>(CharacterType::kCreeperLeft)].m_speed = 80.f;
	data[static_cast<int>(CharacterType::kCreeperLeft)].m_texture = Textures::kCreeper;
	data[static_cast<int>(CharacterType::kCreeperLeft)].m_jump_height = 0.f;

	data[static_cast<int>(CharacterType::kCreeperRight)] = data[static_cast<int>(CharacterType::kCreeperLeft)];
	data[static_cast<int>(CharacterType::kCreeperLeft)].m_directions.emplace_back(Direction(-90.f, 1000.f));
	data[static_cast<int>(CharacterType::kCreeperRight)].m_directions.emplace_back(Direction(90.f, 1000.f));

	//Michael
	data[static_cast<int>(CharacterType::kMichaelLeft)].m_hitpoints = 100;
	data[static_cast<int>(CharacterType::kMichaelLeft)].m_speed = 200.f;
	data[static_cast<int>(CharacterType::kMichaelLeft)].m_texture = Textures::kMichael;
	data[static_cast<int>(CharacterType::kMichaelLeft)].m_jump_height = 0.f;

	data[static_cast<int>(CharacterType::kMichaelRight)] = data[static_cast<int>(CharacterType::kMichaelLeft)];
	data[static_cast<int>(CharacterType::kMichaelLeft)].m_directions.emplace_back(Direction(-90.f, 1000.f));
	data[static_cast<int>(CharacterType::kMichaelRight)].m_directions.emplace_back(Direction(90.f, 1000.f));

	//Freddy
	data[static_cast<int>(CharacterType::kFreddyLeft)].m_hitpoints = 100;
	data[static_cast<int>(CharacterType::kFreddyLeft)].m_speed = 160.f;
	data[static_cast<int>(CharacterType::kFreddyLeft)].m_texture = Textures::kFreddy;
	data[static_cast<int>(CharacterType::kFreddyLeft)].m_jump_height = 0.f;

	data[static_cast<int>(CharacterType::kFreddyRight)] = data[static_cast<int>(CharacterType::kFreddyLeft)];
	data[static_cast<int>(CharacterType::kFreddyLeft)].m_directions.emplace_back(Direction(-90.f, 1000.f));
	data[static_cast<int>(CharacterType::kFreddyRight)].m_directions.emplace_back(Direction(90.f, 1000.f));

	//Jason
	data[static_cast<int>(CharacterType::kJasonLeft)].m_hitpoints = 100;
	data[static_cast<int>(CharacterType::kJasonLeft)].m_speed = 100.f;
	data[static_cast<int>(CharacterType::kJasonLeft)].m_texture = Textures::kJason;
	data[static_cast<int>(CharacterType::kJasonLeft)].m_jump_height = 0.f;

	data[static_cast<int>(CharacterType::kJasonRight)] = data[static_cast<int>(CharacterType::kJasonLeft)];
	data[static_cast<int>(CharacterType::kJasonLeft)].m_directions.emplace_back(Direction(-90.f, 1000.f));
	data[static_cast<int>(CharacterType::kJasonRight)].m_directions.emplace_back(Direction(90.f, 1000.f));

	return data;
}

std::vector<ProjectileData> InitializeProjectileData()
{
	std::vector<ProjectileData> data(static_cast<int>(ProjectileType::kProjectileCount));

	data[static_cast<int>(ProjectileType::kAlliedBullet)].m_damage = 10;
	data[static_cast<int>(ProjectileType::kAlliedBullet)].m_speed = 300;
	data[static_cast<int>(ProjectileType::kAlliedBullet)].m_texture = Textures::kBullet;

	data[static_cast<int>(ProjectileType::kEnemyBullet)].m_damage = 10;
	data[static_cast<int>(ProjectileType::kEnemyBullet)].m_speed = 300;
	data[static_cast<int>(ProjectileType::kEnemyBullet)].m_texture = Textures::kBullet;

	data[static_cast<int>(ProjectileType::kMissile)].m_damage = 200;
	data[static_cast<int>(ProjectileType::kMissile)].m_speed = 150.f;
	data[static_cast<int>(ProjectileType::kMissile)].m_texture = Textures::kMissile;
	return data;
}


std::vector<PickupData> InitializePickupData()
{
	std::vector<PickupData> data(static_cast<int>(PickupType::kPickupCount));

	/*data[static_cast<int>(PickupType::kHealthRefill)].m_texture = Textures::kHealthRefill;
	data[static_cast<int>(PickupType::kHealthRefill)].m_action = [](Aircraft& a) {a.Repair(25); };

	data[static_cast<int>(PickupType::kMissileRefill)].m_texture = Textures::kMissileRefill;
	data[static_cast<int>(PickupType::kMissileRefill)].m_action = std::bind(&Aircraft::CollectMissiles, std::placeholders::_1, 3);

	data[static_cast<int>(PickupType::kFireSpread)].m_texture = Textures::kFireSpread;
	data[static_cast<int>(PickupType::kFireSpread)].m_action = std::bind(&Aircraft::IncreaseSpread, std::placeholders::_1);

	data[static_cast<int>(PickupType::kFireRate)].m_texture = Textures::kFireRate;
	data[static_cast<int>(PickupType::kFireRate)].m_action = std::bind(&Aircraft::IncreaseFireRate, std::placeholders::_1);*/

	const float pickupSpeed = 200.f;

	data[static_cast<int>(PickupType::kApple)].m_texture = Textures::kApple;
	data[static_cast<int>(PickupType::kApple)].m_speed = pickupSpeed;
	data[static_cast<int>(PickupType::kApple)].m_directions.emplace_back(Direction(0.f, 1000.f));
	//data[static_cast<int>(PickupType::kApple)].m_action = [](Aircraft& a) {a.Repair(25); };

	data[static_cast<int>(PickupType::kOrange)].m_texture = Textures::kOrange;
	data[static_cast<int>(PickupType::kOrange)].m_speed = pickupSpeed;
	data[static_cast<int>(PickupType::kOrange)].m_directions.emplace_back(Direction(0.f, 1000.f));
	//data[static_cast<int>(PickupType::kOrange)].m_action = [](Aircraft& a) {a.Repair(25); };

	data[static_cast<int>(PickupType::kCake)].m_texture = Textures::kCake;
	data[static_cast<int>(PickupType::kCake)].m_speed = pickupSpeed;
	data[static_cast<int>(PickupType::kCake)].m_directions.emplace_back(Direction(0.f, 1000.f));
	//data[static_cast<int>(PickupType::kCake)].m_action = [](Aircraft& a) {a.Repair(25); };

	data[static_cast<int>(PickupType::kCarrot)].m_texture = Textures::kCarrot;
	data[static_cast<int>(PickupType::kCarrot)].m_speed = pickupSpeed;
	data[static_cast<int>(PickupType::kCarrot)].m_directions.emplace_back(Direction(0.f, 1000.f));
	//data[static_cast<int>(PickupType::kCarrot)].m_action = [](Aircraft& a) {a.Repair(25); };

	data[static_cast<int>(PickupType::kCookies)].m_texture = Textures::kCookies;
	data[static_cast<int>(PickupType::kCookies)].m_speed = pickupSpeed;
	data[static_cast<int>(PickupType::kCookies)].m_directions.emplace_back(Direction(0.f, 1000.f));
	//data[static_cast<int>(PickupType::kCookies)].m_action = [](Aircraft& a) {a.Repair(25); };

	data[static_cast<int>(PickupType::kDonut)].m_texture = Textures::kDonut;
	data[static_cast<int>(PickupType::kDonut)].m_speed = pickupSpeed;
	data[static_cast<int>(PickupType::kDonut)].m_directions.emplace_back(Direction(0.f, 1000.f));
	//data[static_cast<int>(PickupType::kDonut)].m_action = [](Aircraft& a) {a.Repair(25); };

	data[static_cast<int>(PickupType::kIceCream)].m_texture = Textures::kIceCream;
	data[static_cast<int>(PickupType::kIceCream)].m_speed = pickupSpeed;
	data[static_cast<int>(PickupType::kIceCream)].m_directions.emplace_back(Direction(0.f, 1000.f));
	//data[static_cast<int>(PickupType::kIceCream)].m_action = [](Aircraft& a) {a.Repair(25); };

	data[static_cast<int>(PickupType::kMelon)].m_texture = Textures::kMelon;
	data[static_cast<int>(PickupType::kMelon)].m_speed = pickupSpeed;
	data[static_cast<int>(PickupType::kMelon)].m_directions.emplace_back(Direction(0.f, 1000.f));
	//data[static_cast<int>(PickupType::kMelon)].m_action = [](Aircraft& a) {a.Repair(25); };

	data[static_cast<int>(PickupType::kPancake)].m_texture = Textures::kPancake;
	data[static_cast<int>(PickupType::kPancake)].m_speed = pickupSpeed;
	data[static_cast<int>(PickupType::kPancake)].m_directions.emplace_back(Direction(0.f, 1000.f));
	//data[static_cast<int>(PickupType::kPancake)].m_action = [](Aircraft& a) {a.Repair(25); };
	return data;
}




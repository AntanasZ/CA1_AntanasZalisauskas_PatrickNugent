#pragma once
//SceneNode category used to dispatch commands

/// <summary>
/// Edited by: Antanas Zalisauskas
///
///	-Included categories for player and enemy characters
///	-Added platform category
/// </summary>
namespace Category
{
	enum Type
	{
		kNone = 0,
		kScene = 1 << 0,
		kPlatform = 1 << 1,
		kPlayerAircraft = 1 << 2,
		kPlayerCharacter1 = 1 << 3,
		kPlayerCharacter2 = 1 << 4,
		kAlliedAircraft = 1 << 5,
		kEnemyAircraft = 1 << 6,
		kEnemyCharacter = 1 << 7,
		kPickup = 1 << 8,
		kAlliedProjectile = 1 << 9,
		kEnemyProjectile = 1 << 10,

		kAircraft = kPlayerAircraft | kAlliedAircraft | kEnemyAircraft,
		kCharacter = kPlayerCharacter1 | kPlayerCharacter2 | kEnemyCharacter,
		kProjectile = kAlliedProjectile | kEnemyProjectile,
	};
}
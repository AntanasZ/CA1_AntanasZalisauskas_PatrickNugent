#pragma once
//SceneNode category used to dispatch commands

/// <summary>
/// Edited by: Antanas Zalisauskas
///
///	Included categories for player and enemy characters
/// </summary>
namespace Category
{
	enum Type
	{
		kNone = 0,
		kScene = 1 << 0,
		kPlayerAircraft = 1 << 1,
		kPlayerCharacter1 = 1 << 2,
		kPlayerCharacter2 = 1 << 3,
		kAlliedAircraft = 1 << 4,
		kEnemyAircraft = 1 << 5,
		kEnemyCharacter = 1 << 6,
		kPickup = 1 << 7,
		kAlliedProjectile = 1 << 8,
		kEnemyProjectile = 1 << 9,

		kAircraft = kPlayerAircraft | kAlliedAircraft | kEnemyAircraft,
		kCharacter = kPlayerCharacter1 | kPlayerCharacter2 | kEnemyCharacter,
		kProjectile = kAlliedProjectile | kEnemyProjectile,
	};
}
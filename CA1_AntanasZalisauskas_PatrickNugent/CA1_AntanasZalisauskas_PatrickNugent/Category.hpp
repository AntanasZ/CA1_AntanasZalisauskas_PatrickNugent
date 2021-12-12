#pragma once
//SceneNode category used to dispatch commands
namespace Category
{
	enum Type
	{
		kNone = 0,
		kScene = 1 << 0,
		kPlayerAircraft = 1 << 1,
		kPlayerCharacter = 1 << 2,
		kAlliedAircraft = 1 << 3,
		kEnemyAircraft = 1 << 4,
		kEnemyCharacter = 1 << 5,
		kPickup = 1 << 6,
		kAlliedProjectile = 1 << 7,
		kEnemyProjectile = 1 << 8,

		kAircraft = kPlayerAircraft | kAlliedAircraft | kEnemyAircraft,
		kCharacter = kPlayerCharacter | kEnemyCharacter,
		kProjectile = kAlliedProjectile | kEnemyProjectile,
	};
}
#pragma once
#include <SFML/Graphics/Sprite.hpp>

#include "CharacterType.hpp"
#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"

/// <summary>
/// Written by: Antanas Zalisauskas
///
///	Contains methods and variables related to a character
/// </summary>
class Character : public Entity
{
public:
	Character(CharacterType type, const TextureHolder& textures, const FontHolder& fonts);
	unsigned int GetCategory() const override;

	void UpdateMovementPattern(sf::Time dt);
	float GetMaxSpeed() const;

	sf::FloatRect GetBoundingRect() const override;
	bool IsMarkedForRemoval() const;

private:
	virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void UpdateCurrent(sf::Time dt, CommandQueue& commands) override;
	bool isPlayer() const;

private:
	CharacterType m_type;
	sf::Sprite m_sprite;

	bool m_is_marked_for_removal;
};


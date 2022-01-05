#pragma once
#include <SFML/Graphics/Sprite.hpp>

#include "CharacterType.hpp"
#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"
#include "TextNode.hpp"

/// <summary>
/// Written by: Antanas Zalisauskas
///
///	Contains methods and variables related to a character
///
/// Edited by: Patrick Nugent
///
///	Added method for flipping sprites
/// </summary>
class Character : public Entity
{
public:
	Character(CharacterType type, const TextureHolder& textures, const FontHolder& fonts);
	unsigned int GetCategory() const override;

	void UpdateMovementPattern(sf::Time dt);
	float GetMaxSpeed() const;
	bool GetCanJump() const;
	float GetJumpHeight() const;
	void ToggleCanJump();
	void FlipSprite();
	void AddScore(int points);

	sf::FloatRect GetBoundingRect() const override;
	bool IsMarkedForRemoval() const;

private:
	virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void UpdateCurrent(sf::Time dt, CommandQueue& commands) override;
	bool isPlayer() const;
	void UpdateScore() const;

private:
	CharacterType m_type;
	sf::Sprite m_sprite;
	bool m_can_jump;
	float m_jump_height;
	int m_score;
	TextNode* m_score_display;

	bool m_is_marked_for_removal;
	float m_travelled_distance;
	int m_directions_index;
};


#include "Character.hpp"

#include <iostream>

#include <SFML/Graphics/RenderTarget.hpp>

#include "DataTables.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

/// <summary>
/// Written by: Antanas Zalisauskas
///
///	Implementation of Character.hpp methods
///
/// Edited by: Patrick Nugent
///
///	Added fields and logic for stun animations
/// </summary>

namespace
{
	const std::vector<CharacterData> Table = InitializeCharacterData();
}

Textures ToTextureID(CharacterType type)
{
	switch (type)
	{
	case CharacterType::kShaggy:
		return Textures::kShaggy;
	}
	return Textures::kShaggy;
}

/// <summary>
/// Edited by: Antanas Zalisauskas
///
///	-Added text to display score for both players
///	-Added different color to score based on the player
///
/// Edited by: Patrick Nugent
///
///	-Added field for a stun animation
///	-Added field for showing stun animation
/// </summary>
Character::Character(CharacterType type, const TextureHolder& textures, const FontHolder& fonts)
	: Entity(Table[static_cast<int>(type)].m_hitpoints),
	m_type(type),
	m_sprite(textures.Get(Table[static_cast<int>(type)].m_texture)),
	m_stunned(),
	m_show_stun(true),
	m_can_jump(true),
	m_jump_height(Table[static_cast<int>(type)].m_jump_height)
{
	Utility::CentreOrigin(m_sprite);

	if(type == CharacterType::kShaggy || type == CharacterType::kScooby)
	{
		std::unique_ptr<TextNode> scoreDisplay(new TextNode(fonts, ""));

		m_stunned.SetNumFrames(4);
		m_stunned.SetDuration(sf::seconds(1));

		if (type == CharacterType::kShaggy)
		{
			scoreDisplay->SetColor(sf::Color::Red);
			m_stunned.SetTexture(textures.Get(Textures::kShaggyStunned));
			m_stunned.SetFrameSize(sf::Vector2i(30, 69));
			Utility::CentreOrigin(m_stunned);
		}
		else if(type == CharacterType::kScooby)
		{
			scoreDisplay->SetColor(sf::Color::Green);
			m_stunned.SetTexture(textures.Get(Textures::kScoobyStunned));
			m_stunned.SetFrameSize(sf::Vector2i(49, 46));
			Utility::CentreOrigin(m_stunned);
		}

		scoreDisplay->setPosition(0, -55);
		m_score_display = scoreDisplay.get();
		AttachChild(std::move(scoreDisplay));
		UpdateScore();
	}
}

/// <summary>
/// Edited by: Antanas Zalisauskas
///
/// Edited to work with player and enemy character categories
/// </summary>
/// <returns></returns>
unsigned Character::GetCategory() const
{
	if (isPlayer())
		if(m_type == CharacterType::kShaggy)
			return static_cast<int>(Category::kPlayerCharacter1);
		else
			return static_cast<int>(Category::kPlayerCharacter2);
	else
		return static_cast<int>(Category::kEnemyCharacter);
}

//********* Implement Later for Enemies ****************//
void Character::UpdateMovementPattern(sf::Time dt)
{
	//Enemy AI
	const std::vector<Direction>& directions = Table[static_cast<int>(m_type)].m_directions;
	if (!directions.empty())
	{
		//Move along the current direction, change direction
		if (m_travelled_distance > directions[m_directions_index].m_distance)
		{
			m_directions_index = (m_directions_index + 1) % directions.size();
			m_travelled_distance = 0.f;
		}

		//Compute velocity from direction
		double radians = Utility::ToRadians(directions[m_directions_index].m_angle + 90.f);
		float vx = GetMaxSpeed() * std::cos(radians);
		float vy = GetMaxSpeed() * std::sin(radians);

		SetVelocity(vx, vy);
		m_travelled_distance += GetMaxSpeed() * dt.asSeconds();

	}
}
//********* Implement Later for Enemies ****************//

float Character::GetMaxSpeed() const
{
	return Table[static_cast<int>(m_type)].m_speed;
}

sf::FloatRect Character::GetBoundingRect() const
{
	return GetWorldTransform().transformRect(m_sprite.getGlobalBounds());
}

bool Character::IsMarkedForRemoval() const
{
	return m_is_marked_for_removal;
}

void Character::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_is_stunned && m_show_stun)
	{
		target.draw(m_stunned, states);
	}
	else
	{
		target.draw(m_sprite, states);
	}
}

void Character::UpdateCurrent(sf::Time dt, CommandQueue& commands)
{
	if (IsDestroyed())
	{
		m_is_marked_for_removal = true;
		return;
	}
	else if (m_is_stunned)
	{
		//Update stun animation as long as it isn't on the last frame
		if (!m_stunned.IsFinished())
		{
			m_stunned.Update(dt);
		}
	}
	UpdateMovementPattern(dt);
	Entity::UpdateCurrent(dt, commands);
}

bool Character::isPlayer() const
{
	if (m_type == CharacterType::kShaggy || m_type == CharacterType::kScooby)
		return true;
	else
		return false;
}

/// <summary>
/// Written by: Antanas Zalisauskas
///
///	Added getters and setters for jump variables
/// </summary>
/// <returns></returns>
bool Character::GetCanJump() const
{
	return m_can_jump;
}

float Character::GetJumpHeight() const
{
	return m_jump_height;
}

/// <summary>
/// Written by: Patrick Nugent
///
///	Added getter for score variable
/// </summary>
int Character::GetScore() const
{
	return m_score;
}


void Character::ToggleCanJump(bool value)
{
	m_can_jump = value;
}

/// <summary>
/// Written by: Patrick Nugent
///
///	Flips the sprite of a character
/// </summary>
/// <returns></returns>
void Character::FlipSprite()
{
	m_sprite.scale(-1, 1);
}

/// <summary>
/// Written By: Antanas Zalisauskas
///
///	Updates player score
/// </summary>
void Character::UpdateScore() const
{
	if(m_type == CharacterType::kShaggy)
	{
		m_score_display->SetString("Player 1\n\t " + std::to_string(m_score));
	}
	else
	{
		m_score_display->SetString("Player 2\n\t " + std::to_string(m_score));
	}
}

/// <summary>
/// Written By: Antanas Zalisauskas
///
///	Adds a specified amount to player's score
/// </summary>
/// <param name="points"> The number of points to add to player's score </param>
void Character::AddScore(int points)
{
	m_score += points;
	UpdateScore();
}

/// <summary>
/// Written By: Antanas Zalisauskas
///
/// -Added getter and setter for player stun mechanic
///
/// Edited By: PAtrick Nugent
///
/// -Added call to restart stun animation in setter
/// </summary>
/// <returns></returns>
bool Character::GetStunned()
{
	return m_is_stunned;
}

void Character::SetStunned(bool value)
{
	m_is_stunned = value;
	m_stunned.Restart();
}

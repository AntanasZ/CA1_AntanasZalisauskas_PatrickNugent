#include "GameOverState.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Player.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"
#include "Character.hpp"

/// <summary>
/// Edited by: Patrick Nugent
///
///	-Added player score check
/// -Added game over text
/// </summary>
GameOverState::GameOverState(StateStack& stack, Context context)
	: State(stack, context)
	, m_world(*context.window, *context.fonts)
	, m_game_over_text()
	, m_elapsed_time(sf::Time::Zero)
{
	sf::Font& font = context.fonts->Get(Fonts::Main);
	sf::Vector2f windowSize(context.window->getSize());

	m_game_over_text.setFont(font);
	std::string text;

	if (m_world.GetPlayer1Score() > m_world.GetPlayer2Score())
	{
		m_game_over_text.setString("Player 1 wins with: " + std::to_string(m_world.GetPlayer1Score()) + " points!");
	}
	else if (m_world.GetPlayer2Score() > m_world.GetPlayer1Score())
	{
		m_game_over_text.setString("Player 2 wins with: " + std::to_string(m_world.GetPlayer1Score()) + " points!");
	}
	else
	{
		m_game_over_text.setString("It's a draw, both players have: " + std::to_string(m_world.GetPlayer1Score()) + " points");
	}

	m_game_over_text.setCharacterSize(35);
	Utility::CentreOrigin(m_game_over_text);
	m_game_over_text.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);
}

void GameOverState::Draw()
{
	sf::RenderWindow& window = *GetContext().window;
	window.setView(window.getDefaultView());

	// Create dark, semitransparent background
	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(m_game_over_text);
}

bool GameOverState::Update(sf::Time dt)
{
	// Show state for 3 seconds, after return to menu
	m_elapsed_time += dt;
	if (m_elapsed_time > sf::seconds(5))
	{
		RequestStackClear();
		RequestStackPush(StateID::kMenu);
	}
	return false;
}

bool GameOverState::HandleEvent(const sf::Event&)
{
	return false;
}
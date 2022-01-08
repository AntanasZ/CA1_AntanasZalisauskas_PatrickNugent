#include "GameState.hpp"

#include "Player.hpp"

/// <summary>
/// Edited By: Antanas Zalisauskas
///
///	Included player 2 in constructor, update and handleEvent
/// </summary>

GameState::GameState(StateStack& stack, Context context)
: State(stack, context)
, m_world(*context.window, *context.fonts)
, m_player_1(*context.player1)
, m_player_2(*context.player2)
, m_game_countdown(sf::seconds(120))
{
	//Add game timer
	std::unique_ptr<TextNode> gameTimerDisplay(new TextNode(m_fonts, ""));
	gameTimerDisplay->setPosition(m_world_bounds.width / 2, 20);
	m_game_timer_display = gameTimerDisplay.get();
	m_scene_layers[static_cast<int>(Layers::kAir)]->AttachChild(std::move(gameTimerDisplay));
}

void GameState::Draw()
{
	m_world.Draw();
}

bool GameState::Update(sf::Time dt)
{
	m_world.Update(dt);
	CommandQueue& player_1_commands = m_world.getCommandQueue();
	CommandQueue& player_2_commands = m_world.getCommandQueue();
	m_player_1.HandleRealtimeInput(player_1_commands);
	m_player_2.HandleRealtimeInput(player_2_commands);

	//Check if remaining game time is greater than 0
	if (m_game_countdown > sf::Time::Zero)
	{
		//Decrease and Display remaining game time
		m_game_countdown -= dt;
		DisplayRemainingGameTime();
	}
	else
	{
		m_game_countdown = sf::Time::Zero;
		m_game_timer_display->SetString("Game Over");
	}

	return true;
}

bool GameState::HandleEvent(const sf::Event& event)
{
	CommandQueue& player_1_commands = m_world.getCommandQueue();
	CommandQueue& player_2_commands = m_world.getCommandQueue();
	m_player_1.HandleEvent(event, player_1_commands);
	m_player_2.HandleEvent(event, player_2_commands);

	//Escape should bring up the Pause Menu
	if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		RequestStackPush(StateID::kPause);
	}
	return true;
}

/// <summary>
/// Written by: Antanas Zalisauskas
///
///	Displays remaining time in the game as minutes and seconds
/// </summary>
void GameState::DisplayRemainingGameTime()
{
	int minutes = (int)(m_game_countdown.asSeconds() / 60);
	int seconds = (int)(m_game_countdown.asSeconds()) % 60;

	m_game_timer_display->SetString(std::to_string(minutes) + ":" + std::to_string(seconds));
}

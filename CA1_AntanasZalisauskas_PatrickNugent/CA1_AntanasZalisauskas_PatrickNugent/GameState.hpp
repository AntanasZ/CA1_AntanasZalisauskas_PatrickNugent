#pragma once
#include "State.hpp"
#include "World.hpp"

class GameState : public State
{
public:
	GameState(StateStack& stack, Context context);
	virtual void Draw();
	virtual bool Update(sf::Time dt);
	virtual bool HandleEvent(const sf::Event& event);
	void DisplayRemainingGameTime();

private:
	World m_world;
	Player& m_player_1;
	Player& m_player_2;
	sf::Time m_game_countdown;
	TextNode* m_game_timer_display;
};


#include "State.hpp"

#include "StateStack.hpp"

/// <summary>
/// Edited by: Antanas Zalisauskas
///
///	Included player 2 in context
/// </summary>

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player1, Player& player2)
: window(&window)
, textures(&textures)
, fonts(&fonts)
, player1(&player1)
, player2(&player2)
{
}

State::State(StateStack& stack, Context context)
:m_stack(&stack)
, m_context(context)
{
}

State::~State()
{
}


void State::RequestStackPush(StateID state_id)
{
	m_stack->PushState(state_id);
}

void State::RequestStackPop()
{
	m_stack->PopState();
}

void State::RequestStackClear()
{
	m_stack->ClearStates();
}

State::Context State::GetContext() const
{
	return m_context;
}

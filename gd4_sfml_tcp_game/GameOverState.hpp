#pragma once
#include "State.hpp"
#include <SFML/Graphics/Text.hpp>

class GameOverState : public State
{
public:
	GameOverState(StateStack& stack, Context context);
	virtual void Draw() override;
	virtual bool Update(sf::Time dt) override;
	virtual bool HandleEvent(const sf::Event& event);

private:
	sf::Text m_game_over_text;
	sf::Time m_elapsed_time;
};

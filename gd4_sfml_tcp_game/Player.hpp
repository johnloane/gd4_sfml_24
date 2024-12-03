#pragma once
#include <SFML/Window/Event.hpp>
#include "Action.hpp"
#include "CommandQueue.hpp"
#include "MissionStatus.hpp"
#include <map>

class Command;


class Player
{
public:
	Player();
	void HandleEvent(const sf::Event& event, CommandQueue& command_queue);
	void HandleRealTimeInput(CommandQueue& command_queue);

	void AssignKey(Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key GetAssignedKey(Action action) const;
	void SetMissionStatus(MissionStatus status);
	MissionStatus GetMissionStatus() const;

private:
	void InitialiseActions();
	static bool IsRealTimeAction(Action action);

private:
	std::map<sf::Keyboard::Key, Action> m_key_binding;
	std::map<Action, Command> m_action_binding;
	MissionStatus m_current_mission_status;

};


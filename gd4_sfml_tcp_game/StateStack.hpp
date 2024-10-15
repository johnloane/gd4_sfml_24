#pragma once
#include <SFML/System/NonCopyable.hpp>
#include "State.hpp"
#include "StackAction.hpp"
#include "StateID.hpp"

#include <vector>
#include <map>
#include <functional>

class StateStack : private sf::NonCopyable
{
public:
	explicit StateStack(State::Context context);
	template<typename T>
	void RegisterState(StateID state_id);
	void Update(sf::Time dt);
	void Draw();
	void HandleEvent(const sf::Event& event);

	void PushState(StateID state_id);
	void PopState();
	void ClearStack();
	bool IsEmpty() const;


private:
	State::Ptr CreateState(StateID state_id);
	void ApplyPendingChanges();

private:
	struct PendingChange
	{
		explicit PendingChange(StackAction action, StateID state_id = StateID::kNone);
		StackAction action;
		StateID state_id;
	};

private:
	std::vector<State::Ptr> m_stack;
	std::vector<PendingChange> m_pending_list;
	State::Context m_context;
	std::map<StateID, std::function<State::Ptr()>> m_state_factory;
};

template<typename T>
void StateStack::RegisterState(StateID state_id)
{
	m_state_factory[state_id] = [this]()
		{
			return State::Ptr(new T(*this, m_context));
		};
}


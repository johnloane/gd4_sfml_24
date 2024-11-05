#include "SettingsState.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

SettingsState::SettingsState(StateStack& stack, Context context)
	: State(stack, context)
	, m_gui_container()
{
	m_background_sprite.setTexture(context.textures->Get(TextureID::kTitleScreen));

	//Build key binding buttons and labels
	AddButtonLabel(Action::kMoveUp, 150.f, "Move Up", context);
	AddButtonLabel(Action::kMoveDown, 200.f, "Move Down", context);
	AddButtonLabel(Action::kMoveRight, 250.f, "Move Right", context);
	AddButtonLabel(Action::kMoveLeft, 300.f, "Move Left", context);

	UpdateLabels();

	auto back_button = std::make_shared<gui::Button>(*context.fonts, *context.textures);
	back_button->setPosition(80.f, 375.f);
	back_button->SetText("Back");
	back_button->SetCallback(std::bind(&SettingsState::RequestStackPop, this));
	m_gui_container.Pack(back_button);
}

void SettingsState::Draw()
{
	sf::RenderWindow& window = *GetContext().window;
	window.draw(m_background_sprite);
	window.draw(m_gui_container);
}

bool SettingsState::Update(sf::Time dt)
{
	return true;
}

bool SettingsState::HandleEvent(const sf::Event& event)
{
	bool is_key_binding = false;

	//Iterate through all of the key binding buttons to see if they are being presssed, waiting for the user to enter a key
	for (std::size_t action = 0; action < static_cast<int>(Action::kActionCount); ++action)
	{
		if (m_binding_buttons[action]->IsActive())
		{
			is_key_binding = true;
			if (event.type == sf::Event::KeyReleased)
			{
				GetContext().player->AssignKey(static_cast<Action>(action), event.key.code);
				m_binding_buttons[action]->Deactivate();
			}
			break;
		}
	}

	//If pressed button changed key bindings, then update the labels
	if (is_key_binding)
	{
		UpdateLabels();
	}
	else
	{
		m_gui_container.HandleEvent(event);
	}
	return false;
}

void SettingsState::UpdateLabels()
{
	Player& player = *GetContext().player;
	for (std::size_t i = 0; i < static_cast<int>(Action::kActionCount); ++i)
	{
		sf::Keyboard::Key key = player.GetAssignedKey(static_cast<Action>(i));
		m_binding_labels[i]->SetText(Utility::toString(key));
	}
}

void SettingsState::AddButtonLabel(Action action, float y, const std::string& text, Context context)
{
}

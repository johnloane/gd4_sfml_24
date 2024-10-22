#include "MenuState.hpp"

MenuState::MenuState(StateStack& stack, Context context)
    :State(stack, context), m_option_index(0)
{
    sf::Texture& texture = context.textures->Get(TextureID::kTitleScreen);
}

void MenuState::Draw()
{
}

bool MenuState::Update(sf::Time dt)
{
    return false;
}

bool MenuState::HandleEvent(const sf::Event& event)
{
    return false;
}

void MenuState::UpdateOptionText()
{
}

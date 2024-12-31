#include "Button.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"
#include "ButtonType.hpp"

gui::Button::Button(State::Context context)
    : m_sprite(context.textures->Get(TextureID::kButtons))
    , m_text("", context.fonts->Get(Font::kMain), 16)
    , m_is_toggle(false)
    , m_sounds(*context.sounds)
{
    ChangeTexture(ButtonType::kNormal);
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_text.setPosition(bounds.width / 2, bounds.height / 2);
}

void gui::Button::SetCallback(Callback callback)
{
    m_callback = std::move(callback);
}

void gui::Button::SetText(const std::string& text)
{
    m_text.setString(text);
    Utility::CentreOrigin(m_text);
}

void gui::Button::SetToggle(bool flag)
{
    m_is_toggle = flag;
}

bool gui::Button::IsSelectable() const
{
    return true;
}

void gui::Button::Select()
{
    Component::Select();
    ChangeTexture(ButtonType::kSelected);
}

void gui::Button::Deselect()
{
    Component::Deselect();
    ChangeTexture(ButtonType::kNormal);
}

void gui::Button::Activate()
{
    Component::Activate();

    //If toggle button then show the button is activated
    if (m_is_toggle)
    {
        ChangeTexture(ButtonType::kPressed);
    }
    if (m_callback)
    {
        m_callback();
    }
    if (!m_is_toggle)
    {
        Deactivate();
    }
    m_sounds.Play(SoundEffect::kButton);
}

void gui::Button::Deactivate()
{
    Component::Deactivate();
    if (m_is_toggle)
    {
        if (IsSelected())
        {
            ChangeTexture(ButtonType::kSelected);
        }
        else
        {
            ChangeTexture(ButtonType::kNormal);
        }
    }
}

void gui::Button::HandleEvent(const sf::Event& event)
{
}

void gui::Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_sprite, states);
    target.draw(m_text, states);
}


void gui::Button::ChangeTexture(ButtonType buttonType)
{
    sf::IntRect textureRect(0, 50 * static_cast<int>(buttonType), 200, 50);
    m_sprite.setTextureRect(textureRect);
}
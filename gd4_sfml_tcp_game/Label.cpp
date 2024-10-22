#include "Label.hpp"
#include "ResourceHolder.hpp"

gui::Label::Label(const std::string& text, const FontHolder& fonts)
    :m_text(text, fonts.Get(Font::kMain), 16)
{
}

bool gui::Label::IsSelectable() const
{
    return false;
}

void gui::Label::SetText(const std::string& text)
{
    m_text.setString(text);
}

void gui::Label::HandleEvent(const sf::Event& event)
{
}

void gui::Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_text, states);
}

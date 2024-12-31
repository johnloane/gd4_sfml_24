#include "PauseState.hpp"
#include "ResourceHolder.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Utility.hpp"

PauseState::PauseState(StateStack& stack, Context context)
    :State(stack, context)
    , m_background_sprite()
    , m_paused_text()
    , m_instruction_text()
{
    sf::Font& font = context.fonts->Get(Font::kMain);
    sf::Vector2f view_size = context.window->getView().getSize();

    m_paused_text.setFont(font);
    m_paused_text.setString("Game Paused");
    m_paused_text.setCharacterSize(70);
    Utility::CentreOrigin(m_paused_text);
    m_paused_text.setPosition(0.5f * view_size.x, 0.4f * view_size.y);

    m_instruction_text.setFont(font);
    m_instruction_text.setString("Press backspace to return to main menu, esc to game");
    Utility::CentreOrigin(m_instruction_text);
    m_instruction_text.setPosition(0.5f * view_size.x, 0.6f * view_size.y);

    //Pause the music
    GetContext().music->SetPaused(true);
}

void PauseState::Draw()
{
    sf::RenderWindow& window = *GetContext().window;
    window.setView(window.getDefaultView());

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(window.getView().getSize());

    window.draw(backgroundShape);
    window.draw(m_paused_text);
    window.draw(m_instruction_text);
}

bool PauseState::Update(sf::Time dt)
{
    return false;
}

bool PauseState::HandleEvent(const sf::Event& event)
{
    if (event.type != sf::Event::KeyPressed)
    {
        return false;
    }

    if (event.key.code == sf::Keyboard::Escape)
    {
        RequestStackPop();
    }

    if (event.key.code == sf::Keyboard::BackSpace)
    {
        RequestStackClear();
        RequestStackPush(StateID::kMenu);
    }
    return false;
}

PauseState::~PauseState()
{
    GetContext().music->SetPaused(false);
}
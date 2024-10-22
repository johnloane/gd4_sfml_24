#include "Container.hpp"

gui::Container::Container()
    :m_selected_child(-1)
{
}

void gui::Container::Pack(Component::Ptr component)
{
    m_children.emplace_back(component);
    if (!HasSelection() && component->IsSelectable())
    {
        Select(m_children.size() - 1);
    }
}

bool gui::Container::IsSelectable() const
{
    return false;
}

void gui::Container::HandleEvent(const sf::Event& event)
{
    if (HasSelection() && m_children[m_selected_child]->IsActive())
    {
        m_children[m_selected_child]->HandleEvent(event);
    }
    else if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
        {
            SelectPrevious();
        }
        else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
        {
            SelectNext();
        }
        else if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)
        {
            if (HasSelection())
            {
                m_children[m_selected_child]->Activate();
            }
        }
    }
}

void gui::Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    for (const Component::Ptr& child : m_children)
    {
        target.draw(*child, states);
    }
}

bool gui::Container::HasSelection() const
{
    return m_selected_child >= 0;
}

void gui::Container::Select(std::size_t index)
{
    if (index < m_children.size() && m_children[index]->IsSelectable())
    {
        if (HasSelection())
        {
            m_children[m_selected_child]->Deselect();
        }
        m_children[index]->Select();
        m_selected_child = index;
    }
}

void gui::Container::SelectNext()
{
    if (!HasSelection())
    {
        return;
    }
    //Search for the next selectable component
    int next = m_selected_child;
    do
    {
        next = (next + 1) % m_children.size();
    } while (!m_children[next]->IsSelectable());
    Select(next);
}

void gui::Container::SelectPrevious()
{
    if (!HasSelection())
    {
        return;
    }
    int prev = m_selected_child;
    do
    {
        prev = (prev + m_children.size() - 1) % m_children.size();
    } while (!m_children[prev]->IsSelectable());
    Select(prev);
}

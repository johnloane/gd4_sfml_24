#include "SceneNode.hpp"
#include <cassert>

SceneNode::SceneNode():m_children(), m_parent(nullptr)
{
}

void SceneNode::AttachChild(Ptr child)
{
    child->m_parent = this;
    //Homework: Understand this -> Cherno
    m_children.emplace_back(std::move(child));
}

SceneNode::Ptr SceneNode::DetachChild(const SceneNode& node)
{
    auto found = std::find_if(m_children.begin(), m_children.end(), [&](Ptr& p) {return p.get() == &node; });
    assert(found != m_children.end());

    Ptr result = std::move(*found);
    result->m_parent = nullptr;
    m_children.erase(found);
    return Ptr();
}

void SceneNode::Update(sf::Time dt, CommandQueue& commands)
{
    UpdateCurrent(dt, commands);
    UpdateChildren(dt, commands);
}

sf::Vector2f SceneNode::GetWorldPosition() const
{
    return GetWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::GetWorldTransform() const
{
    sf::Transform transform = sf::Transform::Identity;
    for (const SceneNode* node = this; node != nullptr; node = node->m_parent)
    {
        transform = node->getTransform() * transform;
    }
    return transform;
}

void SceneNode::OnCommand(const Command& command, sf::Time dt)
{
    //Is this command for me? If it is execute
    //Regardless of answer forward to all of my children
    if (command.category & GetCategory())
    {
        command.action(*this, dt);
    }

    //Pass it on to my children
    for (Ptr& child : m_children)
    {
        child->OnCommand(command, dt);
    }
}

void SceneNode::UpdateCurrent(sf::Time dt, CommandQueue& commands)
{
    //Do nothing here
}

void SceneNode::UpdateChildren(sf::Time dt, CommandQueue& commands)
{
    for (Ptr& child : m_children)
    {
        child->Update(dt, commands);
    }
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //Apply the tranform of the current node
    states.transform *= getTransform();
    //Draw the node and its children with the changed transform
    DrawCurrent(target, states);
    DrawChildren(target, states);
}

void SceneNode::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    //Do nothing
}

void SceneNode::DrawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const Ptr& child : m_children)
    {
        child->draw(target, states);
    }
}

unsigned int SceneNode::GetCategory() const
{
    return static_cast<unsigned int>(ReceiverCategories::kScene);
}

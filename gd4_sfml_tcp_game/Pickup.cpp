#include "Pickup.hpp"
#include "DataTables.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"


namespace
{
    const std::vector<PickupData> Table = InitializePickupData();
}

Pickup::Pickup(PickupType type, const TextureHolder& textures)
    : Entity(1)
    , m_type(type)
    , m_sprite(textures.Get(Table[static_cast<int>(type)].m_texture))
{
    Utility::CentreOrigin(m_sprite);
}

unsigned int Pickup::GetCategory() const
{
    return static_cast<int>(ReceiverCategories::kPickup);
}

void Pickup::Apply(Aircraft& player)
{
    Table[static_cast<int>(m_type)].m_action(player);
}

void Pickup::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}

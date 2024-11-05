#include "DataTables.hpp"
#include "AircraftType.hpp"

std::vector<AircraftData> InitializeAircraftData()
{
    std::vector<AircraftData> data(static_cast<int>(AircraftType::kAircraftCount));

    data[static_cast<int>(AircraftType::kEagle)].m_hitpoints = 100;
    data[static_cast<int>(AircraftType::kEagle)].m_speed = 200.f;
    data[static_cast<int>(AircraftType::kEagle)].m_fire_interval = sf::seconds(1);
    data[static_cast<int>(AircraftType::kEagle)].m_texture = TextureID::kEagle;

    data[static_cast<int>(AircraftType::kRaptor)].m_hitpoints = 20;
    data[static_cast<int>(AircraftType::kRaptor)].m_speed = 80.f;
    data[static_cast<int>(AircraftType::kRaptor)].m_fire_interval = sf::Time::Zero;
    data[static_cast<int>(AircraftType::kRaptor)].m_texture = TextureID::kRaptor;

    //AI for Raptor
    data[static_cast<int>(AircraftType::kRaptor)].m_directions.emplace_back(Direction(+45.f, 80.f));
    data[static_cast<int>(AircraftType::kRaptor)].m_directions.emplace_back(Direction(-45.f, 160.f));
    data[static_cast<int>(AircraftType::kRaptor)].m_directions.emplace_back(Direction(+45.f, 80.f));

    return data;
}

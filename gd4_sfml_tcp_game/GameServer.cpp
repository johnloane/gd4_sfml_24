#include "GameServer.hpp"
#include <SFML/Network/Packet.hpp>
#include "NetworkProtocol.hpp"

GameServer::GameServer(sf::Vector2f battlefield_size)
    : m_thread(&GameServer::ExecutionThread, this)
    , m_listening_state(false)
    , m_client_timeout(sf::seconds(1.f))
    , m_max_connected_players(15)
    , m_connected_players(0)
    , m_world_height(5000)
    , m_battlefield_rect(0.f, m_world_height - battlefield_size.y, battlefield_size.x, battlefield_size.y)
    , m_battlefield_scrollspeed(-50.f)
    , m_aircraft_count(0)
    , m_peers(1)
    , m_aircraft_identifier_counter(1)
    , m_waiting_thread_end(false)
    , m_last_spawn_time(sf::Time::Zero)
    , m_time_for_next_spawn(sf::seconds(5.f))
{
    m_listener_socket.setBlocking(false);
    m_peers[0].reset(new RemotePeer());
    m_thread.launch();
}

GameServer::~GameServer()
{
    m_waiting_thread_end = true;
    m_thread.wait();
}

void GameServer::NotifyPlayerSpawn(sf::Int32 aircraft_identifier)
{ 
    sf::Packet packet;
    //First thing in every packets is what type of packet it is
    packet << static_cast<sf::Int8>(Server::PacketType::kPlayerConnect);
    packet << aircraft_identifier << m_aircraft_info[aircraft_identifier].m_position.x << m_aircraft_info[aircraft_identifier].m_position.y;
    for (std::size_t i = 0; i < m_connected_players; ++i)
    {
        if (m_peers[i]->m_ready)
        {
            m_peers[i]->m_socket.send(packet);
        }
    }

}

void GameServer::NotifyPlayerRealtimeChange(sf::Int32 aircraft_identifier, sf::Int32 action, bool action_enabled)
{
}

void GameServer::NotifyPlayerEvent(sf::Int32 aircraft_identifier, sf::Int32 action)
{
}

void GameServer::SetListening(bool enable)
{
}

void GameServer::ExecutionThread()
{
}

void GameServer::Tick()
{
}

sf::Time GameServer::Now() const
{
    return sf::Time();
}

void GameServer::HandleIncomingPackets()
{
}

void GameServer::HandleIncomingPackets(sf::Packet& packet, RemotePeer& receiving_peer, bool& detected_timeout)
{
}

void GameServer::HandleIncomingConnections()
{
}

void GameServer::HandleDisconnections()
{
}

void GameServer::InformWorldState(sf::TcpSocket& socket)
{
}

void GameServer::BroadcastMessage(const std::string& message)
{
}

void GameServer::SendToAll(sf::Packet& packet)
{
}

void GameServer::UpdateClientState()
{
}

GameServer::RemotePeer::RemotePeer() : m_ready(false), m_timed_out(false)
{
    m_socket.setBlocking(false);
}

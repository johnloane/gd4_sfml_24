#include "ParticleNode.hpp"
#include "DataTables.hpp"
#include "ResourceHolder.hpp"

namespace
{
    const std::vector<ParticleData> Table = InitialializeParticleData();
}

ParticleNode::ParticleNode(ParticleType type, const TextureHolder& textures)
    : SceneNode()
    , m_texture(textures.Get(TextureID::kParticle))
    , m_type(type)
    , m_vertex_array(sf::TriangleStrip)
    , m_needs_vertex_update(true)
{
}

void ParticleNode::AddParticle(sf::Vector2f position)
{
    Particle particle;
    particle.m_position = position;
    particle.m_color = Table[static_cast<int>(m_type)].m_color;
    particle.m_lifetime = Table[static_cast<int>(m_type)].m_lifetime;

    m_particles.emplace_back(particle);
}

ParticleType ParticleNode::GetParticleType() const
{
    return m_type;
}

unsigned int ParticleNode::GetCategory() const
{
    return static_cast<int>(ReceiverCategories::kParticleSystem);
}

void ParticleNode::UpdateCurrent(sf::Time dt, CommandQueue& commands)
{
    //Remove expired particles at beginning
    while (!m_particles.empty() && m_particles.front().m_lifetime <= sf::Time::Zero)
    {
        m_particles.pop_front();
    }

    //Decrease lifetime of existing particles
    for (Particle& particle : m_particles)
    {
        particle.m_lifetime -= dt;
    }
    m_needs_vertex_update = true;
}

void ParticleNode::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_needs_vertex_update)
    {
        ComputeVertices();
        m_needs_vertex_update = false;
    }

    //Apply particle texture
    states.texture = &m_texture;

    //Draw the vertices
    target.draw(m_vertex_array, states);
}

void ParticleNode::AddVertex(float worldX, float worldY, float texCoordX, float textCoordY, const sf::Color& color) const
{
}

void ParticleNode::ComputeVertices() const
{
}

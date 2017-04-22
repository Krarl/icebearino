#include "particlesystem.h"
#include "util.h"

ParticleSystem::ParticleSystem(int numParticles, ParticleMode mode, string textureFile) : vertices(sf::PrimitiveType::Triangles, numParticles * 6) {
    this->mode = mode;
    
    loadTexture(texture, textureFile);

    particles.resize(numParticles);
    for (size_t i = 0; i < particles.size(); i++) {
        resetParticle(i);
    }
}

ParticleSystem::~ParticleSystem() {

}

void ParticleSystem::update(float dt) {
    float particleSize = texture.getSize().x;

    for (size_t i = 0; i < particles.size(); ++i)
    {
        Particle& p = particles[i];

        p.vel.x += sin(p.pos.y / 20.0f) * 100.0f * dt;
        p.pos += p.vel * dt;

        if (p.pos.y > 600)
            resetParticle(i);

        vertices[i*6+0].position = p.pos + sf::Vector2f(0.0f, 0.0f);
        vertices[i*6+1].position = p.pos + sf::Vector2f(particleSize, 0.0f);
        vertices[i*6+2].position = p.pos + sf::Vector2f(particleSize, particleSize);

        vertices[i*6+3].position = p.pos + sf::Vector2f(0.0f, 0.0f);
        vertices[i*6+4].position = p.pos + sf::Vector2f(0.0f, particleSize);
        vertices[i*6+5].position = p.pos + sf::Vector2f(particleSize, particleSize);

        vertices[i*6+0].texCoords = sf::Vector2f(0.0f, 0.0f);
        vertices[i*6+1].texCoords = sf::Vector2f(particleSize, 0.0f);
        vertices[i*6+2].texCoords = sf::Vector2f(particleSize, particleSize);

        vertices[i*6+3].texCoords = sf::Vector2f(0.0f, 0.0f);
        vertices[i*6+4].texCoords = sf::Vector2f(0.0f, particleSize);
        vertices[i*6+5].texCoords = sf::Vector2f(particleSize, particleSize);
    }
}

void ParticleSystem::resetParticle(int i) {
    if (mode == ParticleMode::Snow) {
        particles[i].pos.x = rnd() * 800.0f;
        particles[i].pos.y = rnd() * -800.0f - 200.0f;

        particles[i].vel.x = rnd() * 10.0f - 5.0f;
        particles[i].vel.y = rnd() * 100.0f + 50.0f;
    }
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &texture;
    target.draw(vertices, states);
}
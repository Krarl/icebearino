#include "particlesystem.h"
#include "util.h"

ParticleSystem:: ParticleSystem(int numParticles, ParticleMode mode, string textureFile, sf::Vector2f pos) : vertices(sf::PrimitiveType::Triangles, numParticles * 6) {
    this->mode = mode;
    this->pos = pos;
    this->stillAlive = numParticles;
    
    loadTexture(texture, textureFile);

    particles.resize(numParticles);
    for (size_t i = 0; i < particles.size(); i++) {
        resetParticle(i, true);
    }
}

ParticleSystem::~ParticleSystem() {

}

void ParticleSystem::update(float dt) {
    float particleSize = texture.getSize().x;

    for (size_t i = 0; i < particles.size(); ++i)
    {
        Particle& p = particles[i];

        p.pos += p.vel * dt;


        if (mode == ParticleMode::Snow) {
            p.vel.x += sin(p.pos.y / p.factor) * 100.0f * dt;
            
            if (p.pos.y > 600)
                resetParticle(i);
        } else if (mode == ParticleMode::Explosion) {
            if (p.alpha != 0.0f)
                p.alpha -= 2.0f * dt;

            if (p.alpha < 0.0f)
                resetParticle(i);
        }
        

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

        for (int j = 0; j < 6; j++)
            vertices[i*6 + j].color.a = particles[i].alpha * 255.0f;
    }
}

void ParticleSystem::resetParticle(int i, bool setup) {
    if (mode == ParticleMode::Snow) {
        particles[i].pos.x = rnd() * 800.0f;
        if (setup) {
            particles[i].pos.y = rnd() * 800.0f;
        } else {
            particles[i].pos.y = rnd() * -600.0f;
        }

        particles[i].vel.x = rnd() * 10.0f - 5.0f;
        particles[i].vel.y = rnd() * 100.0f + 50.0f;

        particles[i].factor = rnd() * 20.0f + 10.0f;
        particles[i].alpha = 0.5f + rnd() * 0.5f;
    } else if (mode == ParticleMode::Explosion || mode == ParticleMode::Splash) {
        if (setup) {
            particles[i].pos = pos;

            float angle = 2 * M_PI * rnd();
            float speed = 20.0f + rnd() * 60.0f;
			if (mode == ParticleMode::Splash)
				speed = 20.0f + rnd() * 160.f;

            particles[i].vel = sf::Vector2f(cos(angle), sin(angle)) * speed;
            particles[i].alpha = 0.8f + rnd() * 0.2f;
        } else {
            particles[i].alpha = 0.0f;
            stillAlive -= 1;
        }
    }
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &texture;
    target.draw(vertices, states);
}
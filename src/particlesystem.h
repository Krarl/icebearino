#ifndef PARTICLESYSTEM_H_
#define PARTICLESYSTEM_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>

using namespace std;

struct Particle {
    sf::Vector2f pos;
    sf::Vector2f vel;
};

enum ParticleMode {
    Snow
};

class ParticleSystem : public sf::Drawable, public sf::Transformable {
public:
    ParticleSystem(int numParticles, ParticleMode mode, string textureFile);
    ~ParticleSystem();

    void update(float dt);

private:
    void resetParticle(int i);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    vector<Particle> particles;
    sf::Texture texture;
    sf::VertexArray vertices;
    ParticleMode mode;
};

#endif
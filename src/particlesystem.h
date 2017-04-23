#ifndef PARTICLESYSTEM_H_
#define PARTICLESYSTEM_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>

using namespace std;

struct Particle {
    sf::Vector2f pos;
    sf::Vector2f vel;
    float alpha;
};

enum ParticleMode {
    Snow,
    Explosion,
	Splash
};

class ParticleSystem : public sf::Drawable, public sf::Transformable {
public:
    ParticleSystem(int numParticles, ParticleMode mode, string textureFile, sf::Vector2f pos = sf::Vector2f(0.0f, 0.0f));
    ~ParticleSystem();

    void update(float dt);

    int stillAlive;
private:
    void resetParticle(int i, bool setup = false);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    vector<Particle> particles;
    sf::Texture texture;
    sf::VertexArray vertices;
    ParticleMode mode;

    sf::Vector2f pos;
};

#endif
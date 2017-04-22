#include "util.h"
#include <math.h>
#include <random>

void loadTexture(sf::Texture& texture, string file) {
    auto size = texture.getSize();
    if (size.x == 0 && size.y == 0) {
        if (!texture.loadFromFile(file)) {
            cout << "Error loading texture " << file << endl;
        } else {
            cout << "Loaded texture " << file << endl;
        }
    }
}

void loadSoundBuffer(sf::SoundBuffer& soundBuffer, string file) {
    if (soundBuffer.getSampleCount() == 0) {
        if (!soundBuffer.loadFromFile(file)) {
            cout << "Error loading sound " << file << endl;
        } else {
            cout << "Loaded sound " << file << endl;
        }
    }
}

void drawSprite(sf::Sprite& sprite, Game* game) {
    sprite.setPosition(sprite.getPosition() + game->center + game->screenCenter);
    game->window->draw(sprite);
}

float length(sf::Vector2f v) {
    return sqrt(v.x*v.x + v.y*v.y);
}

float rnd(){
    return (rand()%1000)/1000.0f;
}

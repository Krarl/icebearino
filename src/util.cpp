#include "util.h"
#include <math.h>
#include <SFML/Graphics.hpp>
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
    sprite.setPosition(sprite.getPosition() - game->center + game->screenCenter);
    game->window->draw(sprite);
}

void centerSprite(sf::Sprite& sprite) {
    sprite.setOrigin(sprite.getTexture()->getSize().x / 2.0f, sprite.getTexture()->getSize().y / 2.0f);
}

void centerText(sf::Text& text) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
}

float length(sf::Vector2f v) {
    return sqrt(v.x*v.x + v.y*v.y);
}

float dist(sf::Vector2f a, sf::Vector2f b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}

float rnd(){
    return (rand() % 10000) / 10000.0f;
}

float len(V2f v){
    return sqrt(v.x*v.x+v.y*v.y);
}

V2f norm(V2f v){
    return v/len(v);
}

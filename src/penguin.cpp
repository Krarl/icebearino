#include "penguin.h"
#include "util.h"

sf::Texture Penguin::texture;

Penguin::Penguin(int icefloe) {
    loadTexture(texture, "res/img/penguin.png");
    texture.setSmooth(true);
    sprite.setTexture(texture);
    centerSprite(sprite);
    sprite.setRotation(rnd() * 360.0f);
    sprite.setScale(0.5f, 0.5f);

    pos = sf::Vector2f(rnd() * 50.0f - 25.0f, rnd() * 50.0 - 25.0f);
    this->icefloe = icefloe;
}

void Penguin::update(Game* game) {
    sprite.setRotation(sprite.getRotation() + 30.0 * game->dt);
}

void Penguin::render(Game* game) {
    sprite.setPosition(getRealPos(game));
    drawSprite(sprite, game);
}

sf::Vector2f Penguin::getRealPos(Game* game) {
    sf::Vector2f realPos = pos;

    if (icefloe != -1) {
        Icefloe* floe = game->icefloes[icefloe];
        realPos += floe->pos;
    }

    return realPos;
}

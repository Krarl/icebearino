#include "penguin.h"
#include "util.h"

Player::Player(int icefloe) {
    loadTexture(texture, "res/img/bear.png");
    sprite.setTexture(texture);

    this->icefloe = icefloe;
    pos = sf::Vector2f(0.0f, 0.0f);
}

void Player::update(Game* game) {
    
}

void Player::render(Game* game) {
    sf::Vector2f realPos = pos;

    if (icefloe != -1) {
        Icefloe* floe = game->icefloes[icefloe];
        realPos += floe->pos;
    }

    sprite.setPosition(realPos);
    drawSprite(sprite, game);
}
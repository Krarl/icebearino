#include "penguin.h"
#include "util.h"

Player::Player(int icefloe) {
    loadTexture(texture, "res/img/bear.png");
    sprite.setTexture(texture);

    this->icefloe = icefloe;
    pos = sf::Vector2f(0.0f, 0.0f);
    rot = 0.0f;
}

void Player::update(Game* game) {
    const auto leftKey = sf::Keyboard::Key::A;
    const auto rightKey = sf::Keyboard::Key::D;
    const auto runKey = sf::Keyboard::Key::W;
    const auto backKey = sf::Keyboard::Key::S;

    const float runSpeed = 15.0f;
    const float turnSpeed = 10.0f;

    if (sf::Keyboard::isKeyPressed(runKey)) {
        pos.y -= game->dt * runSpeed;
    }
    if (sf::Keyboard::isKeyPressed(backKey)) {
        pos.y += game->dt * runSpeed * 0.4f;
    }
    if (sf::Keyboard::isKeyPressed(leftKey)) {
        rot -= game->dt * turnSpeed;
    }
    if (sf::Keyboard::isKeyPressed(rightKey)) {
        rot += game->dt * turnSpeed;
    }
}

void Player::render(Game* game) {
    sprite.setPosition(getRealPos(game));
    sprite.setRotation(rot);
    drawSprite(sprite, game);
}

sf::Vector2f Player::getRealPos(Game* game) {
    sf::Vector2f realPos = pos;

    if (icefloe != -1) {
        Icefloe* floe = game->icefloes[icefloe];
        realPos += floe->pos;
    }

    return realPos;
}
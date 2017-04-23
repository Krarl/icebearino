#include "penguin.h"
#include "util.h"
#include <math.h>
using namespace std;

sf::Texture Player::texture;
sf::Texture Player::feet1;
sf::Texture Player::feet2;
sf::SoundBuffer Player::walkSoundBuffer;
sf::SoundBuffer Player::splashSoundBuffer;

float bodyLength;

Player::Player(int icefloe) {
    loadTexture(texture, "res/img/bear.png");
    loadTexture(feet1, "res/img/feet1.png");
    loadTexture(feet2, "res/img/feet2.png");
    bodyLength = (float)texture.getSize().y / 2.0f;

    sprite.setTexture(texture);
    centerSprite(sprite);
    feetS1.setTexture(feet1);
    feetS2.setTexture(feet2);
    centerSprite(sprite);
    centerSprite(feetS1);
    centerSprite(feetS2);

    loadSoundBuffer(walkSoundBuffer, "res/sound/walk.ogg");
    walkSound.setBuffer(walkSoundBuffer);
    walkSound.setLoop(true);

    loadSoundBuffer(splashSoundBuffer, "res/sound/splash.ogg");
    splashSound.setBuffer(splashSoundBuffer);

    this->icefloe = icefloe;
    pos = sf::Vector2f(0.0f, 0.0f);
    rot = 0.0f;
    height = 0.0f;
    vel = sf::Vector2f(0.0f, 0.0f);
    velY = 0.0f;
	dying = false;
	walkProg = 0;
	walkUp = 0;
}

Player::~Player() {
    //walkSound.stop();
}

void Player::update(Game* game) {
    const auto leftKey = sf::Keyboard::Key::A;
    const auto rightKey = sf::Keyboard::Key::D;
    const auto runKey = sf::Keyboard::Key::W;
    const auto backKey = sf::Keyboard::Key::S;
    const auto jumpKey = sf::Keyboard::Key::Space;

    float runSpeed = 1200.0f - length(vel);
    const float reverseFraction = 0.25f;
    const float turnSpeed = 1.7f;
    const float friction = 3.0f;

    auto forward = getForwardVector();

    bool moving = false;

    // Move forward/backward
    if (height == 0.0f && !dying) {
        if (sf::Keyboard::isKeyPressed(runKey)) {
            vel += game->dt * forward * runSpeed;
            moving = true;
        }
        if (sf::Keyboard::isKeyPressed(backKey)) {
            vel -= game->dt * forward * runSpeed * reverseFraction;
            moving = true;
        }
    }
    // Rotate left/right
    if (sf::Keyboard::isKeyPressed(leftKey) && !dying) {
        rot -= game->dt * turnSpeed;
        moving = true;
    }
    if (sf::Keyboard::isKeyPressed(rightKey) && !dying) {
        rot += game->dt * turnSpeed;
        moving = true;
    }

	if (moving){
		if (abs(walkProg) > 1)
			walkUp = !walkUp;
		float spd = walkUp ? 1 : -1;
		walkProg += spd*8*game->dt;
	}

    // Update position and velocity
    pos += vel * game->dt;
    if (height == 0.0f || dying)
        vel -= vel * friction * game->dt;

    // Walk sound
    if (moving && walkSound.getStatus() != sf::SoundSource::Status::Playing) {
        walkSound.play();
    }
    else if (!moving && walkSound.getStatus() == sf::SoundSource::Status::Playing) {
        walkSound.stop();
    }

    // Jumping
    if (height == 0.0f && sf::Keyboard::isKeyPressed(jumpKey) && !dying) {
        height = 0.01;
        pos = getRealPos(game);
        icefloe = -1;
        velY = 1.5f;
    }

    height += velY * game->dt * (dying ? 0.3f : 1.f);
    velY -= 5.0f * game->dt;

    // Detect if we moved outside our floe
    if (icefloe != -1 && !onFloe(game, game->icefloes[icefloe])) {
        pos = getRealPos(game);
        icefloe = -1;
    }

    // Landing and switching ice floe
    if (height <= 0.0f && velY <= 0.0f && !dying) {
        velY = height = 0.0f;
        if (icefloe == -1) {
            for (auto f : game->icefloes) {
                sf::Vector2f relativePos = getRealPos(game) - f.second->pos;
                if (onFloe(game, f.second)) {
                    icefloe = f.first;
                    pos = relativePos;
                    break;
                }
            }

            if (icefloe == -1) {
                dying = true;
				velY = min(velY, -2.f);
				splashSound.play();
            }
        }
    }

	if (dying && height < -0.7f)
		game->over = true;
}

bool Player::onFloe(Game* game, Icefloe* floe){
    int hits = 0;
    V2f relPos = getRealPos(game) - floe->pos
        , forward = getForwardVector()
        , perp = getPerpVector();

    float sideFactor = bodyLength*0.2f, forwardFactor = bodyLength*0.5f;

    rep(dx, -1, 2) rep(dy, -1, 2)
        hits += floe->inside(relPos + perp*(sideFactor*dx) + forward*(forwardFactor*dy));

    return hits >= 1;
}

void Player::render(Game* game) {
    sprite.setPosition(getRealPos(game));
    sprite.setRotation(rot * 180.0f / M_PI);
    float scale = 1.0f + height;
    sprite.setScale(scale, scale);

	for (sf::Sprite* foot : {&feetS1, &feetS2}){
		foot->setRotation(rot * 180.0f / M_PI);
		foot->setScale(scale, scale);
	}
	feetS1.setPosition(getRealPos(game)+getForwardVector()*10.f*walkProg);
	feetS2.setPosition(getRealPos(game)-getForwardVector()*10.f*walkProg);

	char colVal = min(255, max(0, int(255*(1+height*3))));
	sf::Color col(colVal, colVal, colVal, colVal);

	for (auto foot : {feetS1, feetS2}){
		foot.setColor(col);
		drawSprite(foot, game);
	}

	sprite.setColor(col);
    drawSprite(sprite, game);

}

sf::Vector2f Player::getForwardVector() {
    return sf::Vector2f(cos(rot - M_PI / 2.0f), sin(rot - M_PI / 2.0f));
}

sf::Vector2f Player::getPerpVector() {
    return sf::Vector2f(cos(rot), sin(rot));
}

sf::Vector2f Player::getRealPos(Game* game) {
    sf::Vector2f realPos = pos;

    if (icefloe != -1) {
        Icefloe* floe = game->icefloes[icefloe];
        realPos += floe->pos;
    }

    return realPos;
}

sf::Vector2f Player::getRealMouthPos(Game* game) {
    return getRealPos(game) + getForwardVector() * ((float)texture.getSize().y / 2.0f - 20);
}

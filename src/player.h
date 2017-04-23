#ifndef PLAYER_H_
#define PLAYER_H_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "game.h"
#include "icefloe.h"

using namespace std;

class Game;

class Player {
public:
	Player(int icefloe);
	~Player();

	void update(Game* game);
	void render(Game* game);
	bool onFloe(Game* game, Icefloe* floe);

	sf::Vector2f getForwardVector();
	sf::Vector2f getPerpVector();

	sf::Vector2f getRealPos(Game* game);
	sf::Vector2f getRealMouthPos(Game* game);

	int icefloe;
	sf::Vector2f pos;
	float rot;
	float height;
	sf::Vector2f vel;
	float velY;
	bool dying = false;

private:
	static sf::Texture texture, feet1, feet2;
	sf::Sprite sprite, feetS1, feetS2;
	float walkProg;
	float walkUp;

	static sf::SoundBuffer walkSoundBuffer;
	static sf::SoundBuffer splashSoundBuffer;
	sf::Sound walkSound;
	sf::Sound splashSound;
};

#endif

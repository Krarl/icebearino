#ifndef PLAYER_H_
#define PLAYER_H_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "game.h"

using namespace std;

class Game;

class Player {
public:
	Player(int icefloe);

	void update(Game* game);
	void render(Game* game);

	sf::Vector2f getRealPos(Game* game);

	int icefloe;
	sf::Vector2f pos;
	float rot;
	float height;
	sf::Vector2f vel;
	float velY;

private:
	static sf::Texture texture;
	sf::Sprite sprite;

	static sf::SoundBuffer walkSoundBuffer;
	sf::Sound walkSound;
};

#endif
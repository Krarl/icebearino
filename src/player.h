#ifndef PLAYER_H_
#define PLAYER_H_

#include <SFML/Graphics.hpp>
#include "game.h"

using namespace std;

class Game;

class Player {
public:
	Player(int icefloe);

	void update(Game* game);
	void render(Game* game);

	int icefloe;
	sf::Vector2f pos;

private:
	sf::Texture texture;
	sf::Sprite sprite;
};

#endif
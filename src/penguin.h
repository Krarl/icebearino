#ifndef PENGUIN_H_
#define PENGUIN_H_

#include <SFML/Graphics.hpp>
#include "game.h"

using namespace std;

class Game;

class Penguin {
public:
	Penguin(int icefloe);

	void update(Game* game);
	void render(Game* game);

	sf::Vector2f getRealPos(Game* game);

	sf::Vector2f pos;
	int icefloe;

private:
	static sf::Texture texture;
	sf::Sprite sprite;
};

#endif
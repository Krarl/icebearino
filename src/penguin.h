#ifndef PENGUIN_H_
#define PENGUIN_H_

#include <SFML/Graphics.hpp>
#include "game.h"

using namespace std;

class Game;

class Penguin {
public:
	Penguin();

	void update(Game* game);
	void render(Game* game);

private:
	static sf::Texture texture;
};

#endif
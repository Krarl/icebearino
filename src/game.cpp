#include "game.h"
#include "util.h"
#include <iostream>
#include <string>
#include "macros.h"
using namespace std;

int floeIndex = 0;
set<pair<int, int> > addedPositions;
void addFloes(Game* game);

void Game::init(sf::RenderWindow* window){
	this->window = window;
	center = V2f(0, 0);
	screenCenter = V2f(400, 300);

	player = new Player(0);
	over = 0;
	floeIndex = 0;

	loadTexture(waterTexture, "res/img/water.png");
	waterTexture.setRepeated(true);
	water.setTexture(waterTexture);
	water.setTextureRect(sf::IntRect(0, 0, 800, 600));

	addedPositions.insert({0, 0});
	icefloes[floeIndex ++] = new Icefloe();
}

void Game::cleanup() {
	cout << "Deleting player" << endl;
	delete player;

	cout << "Deleting penguins" << endl;
	for (Penguin* penguin : penguins)
		delete penguin;
	penguins.clear();

	cout << "Deleting floes" << endl;
	for (auto floe : icefloes)
		delete floe.second;
	icefloes.clear();

	cout << "Done" << endl;	
	
	addedPositions.clear();
}

void Game::update(float dt){
	this->dt = dt;
	for (auto penguin : penguins)
		penguin->update(this);

	player->update(this);
	for (auto icefloe : icefloes)
		icefloe.second->update(this);

	addFloes(this);
}


void Game::render(){
	window->draw(water);

	for (auto icefloe : icefloes)
		icefloe.second->render(this);
	for (auto penguin : penguins)
		penguin->render(this);

	player->render(this);
}

void Game::addPenguinOnFloe(int floe)  {
	Penguin* penguin = new Penguin(floe);
	penguins.push_back(penguin);
}


float sectionSize = 150;
void addFloes(Game* game){
	V2f ppos = game->player->getRealPos(game);
	int rx = int(ppos.x/sectionSize), ry = int(ppos.y/sectionSize), margin = 10;
	rep(x, rx-margin, rx+margin) {
		rep(y, ry-margin, ry+margin) {
			pair<int, int> pos = {x, y};
			if (addedPositions.find(pos) != addedPositions.end())
				continue;
			addedPositions.insert(pos);
			V2f rpos = V2f((x+rnd())*sectionSize, (y+rnd())*sectionSize);

			game->icefloes[floeIndex] = new Icefloe(rpos, floeIndex++);

			if (rnd() < 0.1f) {
				game->addPenguinOnFloe(floeIndex - 1);
			}
		}
	}
}

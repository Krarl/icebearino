#include "game.h"
#include "util.h"
#include <iostream>
#include <string>
#include "macros.h"
#include "perlin.h"
#include <sstream>
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
	score = 0;

	loadTexture(waterTexture, "res/img/water.png");
	waterTexture.setRepeated(true);
	water.setTexture(waterTexture);
	water.setTextureRect(sf::IntRect(0, 0, 800, 600));

	loadSoundBuffer(penguinDeathBuffer, "res/sound/bird.ogg");
	penguinDeath.setBuffer(penguinDeathBuffer);

	addedPositions.insert({0, 0});
	icefloes[floeIndex] = new Icefloe(sf::Vector2f(0.0f, 0.0f), floeIndex);
	floeIndex++;
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

Perlin perlin;
float perlinh = 0;

void Game::update(float dt){
	perlinh += dt;
	this->dt = dt;
	for (int i = 0; i < (int)penguins.size(); i++) {
		penguins[i]->update(this);

		if (dist(player->getRealMouthPos(this), penguins[i]->getRealPos(this)) < 50.0f) {
			delete penguins[i];
			penguins.erase(penguins.begin() + i);
			i--;
			penguinDeath.play();
			score ++;
		}
	}

	player->update(this);
	for (auto icefloe : icefloes)
		icefloe.second->update(this);

	addFloes(this);

	center = player->getRealPos(this);
}

bool fontloaded = 0;
sf::Font font;
void loadFont(){
	if (fontloaded)
		return;
	fontloaded = 1;
	font.loadFromFile("res/fonts/arial.ttf");
}

void Game::render(){
	/*float wstep = 10;
	perlin.scale = 0.1;
	for(float x = 0; x < 800; x += wstep)
		for(float y = 0; y < 600; y += wstep) {
			sf::Color col(0, 0, 120+perlin.perlAt(V3f(x, y, perlinh))*50);
			sf::RectangleShape shape;
			shape.setSize(V2f(wstep, wstep));
			shape.setPosition(V2f(x, y));
			shape.setFillColor(col);
			window->draw(shape);
		}*/

	window->draw(water);

	for (auto icefloe : icefloes)
		icefloe.second->render(this);
	for (auto penguin : penguins)
		penguin->render(this);

	player->render(this);

	if (score != 0){
		stringstream ss;
		ss << " " << score << " penguins eaten.";
		loadFont();
		sf::Text text(ss.str(), font, 30);
		text.setPosition(V2f(1, 1));
		text.setColor(sf::Color::Black);
		window->draw(text);
		text.setPosition(V2f(0, 0));
		text.setColor(sf::Color::White);
		window->draw(text);
	}
}

void Game::addPenguinOnFloe(int floe)  {
	Penguin* penguin = new Penguin(floe);
	penguins.push_back(penguin);
}


float sectionSize = 150;
float minDist = 1000, maxDist = 2000;

void addFloes(Game* game){
	V2f ppos = game->player->getRealPos(game);
	int rx = int(ppos.x/sectionSize), ry = int(ppos.y/sectionSize), margin = 10;
	rep(x, rx-margin, rx+margin) {
		rep(y, ry-margin, ry+margin) {
			pair<int, int> pos = {x, y};
			if (addedPositions.find(pos) != addedPositions.end())
				continue;
			V2f rpos = V2f((x+rnd())*sectionSize, (y+rnd())*sectionSize);
			if (len(game->player->pos-rpos) > minDist)
				continue;
			addedPositions.insert(pos);

			game->icefloes[floeIndex] = new Icefloe(rpos, floeIndex);
			floeIndex++;

			if (rnd() < 0.1f) {
				game->addPenguinOnFloe(floeIndex - 1);
			}
		}
	}
	cout << game->icefloes.size() << endl;
}

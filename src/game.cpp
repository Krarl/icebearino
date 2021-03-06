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

	splash = nullptr;

	loadTexture(waterTexture, "res/img/water.png");
	waterTexture.setRepeated(true);
	water.setTexture(waterTexture);
	//water.setTextureRect(sf::IntRect(0, 0, 800, 600));

	loadSoundBuffer(penguinDeathBuffer, "res/sound/bird.ogg");
	penguinDeath.setBuffer(penguinDeathBuffer);

	loadSoundBuffer(chompBuffer, "res/sound/chomp.ogg");
	chomp.setBuffer(chompBuffer);

	addedPositions.insert({0, 0});
	icefloes[floeIndex] = new Icefloe(sf::Vector2f(0.0f, 0.0f), floeIndex);
	floeIndex++;
	hunger = 0.7;
	sinceStart = 0;
	blockSpace = true;
}

void Game::cleanup() {
	delete player;

	for (Penguin* penguin : penguins)
		delete penguin;
	penguins.clear();

	for (auto floe : icefloes)
		delete floe.second;
	icefloes.clear();

	for (auto bloodSplash : bloodSplashes)
		delete bloodSplash;
	bloodSplashes.clear();

	addedPositions.clear();

	if (splash != nullptr)
		delete splash;
}

Perlin perlin;
float perlinh = 0;

void Game::update(float dt){
	perlinh += dt;
	this->dt = dt;

	hunger -= dt*0.08f;
	sinceStart += dt;

	blockSpace &= sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);


	addFloes(this);

	for (int i = 0; i < (int)penguins.size(); i++) {
		if (icefloes.find(penguins[i]->icefloe) == icefloes.end()){
			penguins.erase(penguins.begin() + i);
			i--;
			continue;
		}
		penguins[i]->update(this);

		float eatingDistance = 50.0f;

		if (dist(player->getRealMouthPos(this), penguins[i]->getRealPos(this)) < eatingDistance * 1.5f && chomp.getStatus() != sf::SoundSource::Status::Playing) {
			chomp.play();
		}
		if (dist(player->getRealMouthPos(this), penguins[i]->getRealPos(this)) < eatingDistance) {
			addBloodAt(penguins[i]->getRealPos(this));			
			delete penguins[i];
			penguins.erase(penguins.begin() + i);
			i--;
			penguinDeath.play();
			
			score ++;
			hunger = min(1.f, hunger + 0.3f);
		}
	}

	if (hunger < 0)
		over = true;

	for (size_t i = 0; i < bloodSplashes.size(); i++) {
		bloodSplashes[i]->update(dt);
		if (!bloodSplashes[i]->stillAlive) {
			delete bloodSplashes[i];
			bloodSplashes.erase(bloodSplashes.begin() + i);
			--i;
		}
	}

	if (splash != nullptr) {
		splash->update(dt);
	}

	player->update(this);
	for (auto icefloe : icefloes)
		icefloe.second->update(this);

	center = player->getRealPos(this);
}

bool fontloaded = 0;
sf::Font font;
void loadFont(){
	if (fontloaded)
		return;
	fontloaded = 1;
	font.loadFromFile("res/fonts/courier.ttf");
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

	int w_width = waterTexture.getSize().x, w_height = waterTexture.getSize().y;
	int wx = ((int(center.x)/w_width)*w_width-int(center.x))%w_width-w_width;
	int wy = ((int(center.y)/w_height)*w_height-int(center.y))%w_height-w_height;
	for(int x = wx; x <= wx+800*2+w_width; x += w_width)
		for(int y = wy; y <= wy+600*2+w_height; y += w_height)
			water.setPosition(V2f(x, y)), window->draw(water);

	if (player->dying)
		player->render(this);

	for (auto icefloe : icefloes)
		icefloe.second->render(this);
	for (auto penguin : penguins)
		penguin->render(this);
	for (auto bloodSplash : bloodSplashes) {
		bloodSplash->setPosition(-center + screenCenter);
		window->draw(*bloodSplash);
	}

	if (splash != nullptr) {
		splash->setPosition(-center + screenCenter);
		window->draw(*splash);
	}

	if (!player->dying)
		player->render(this);

	auto drawWithOutline = [&](sf::Text text, V2f pos, sf::Color in, sf::Color out){
		text.setColor(out);
		rep(i, 0, 8) {
			text.setPosition(pos+V2f(cos(0.25f*M_PI*i), sin(0.25f*M_PI*i))*2.f);
			window->draw(text);
		}
		text.setColor(in);
		text.setPosition(pos);
		window->draw(text);
	};

	loadFont();
	if (score != 0){
		stringstream ss;
		ss << " " << score << " penguins eaten.";
		sf::Text text(ss.str(), font, 30);
		drawWithOutline(text, V2f(1, 1), sf::Color::White, sf::Color::Black);
	}
	
	stringstream ss;
	int barlen = 10, filled = int(hunger*barlen)+1;
	ss << "Hunger: [";
	rep(i, 0, filled)
		ss << "#";
	rep(i, 0, 10-filled)
		ss << " ";
	ss << "]";
	sf::Text text(ss.str(), font, 30);
    centerText(text);
	drawWithOutline(text, V2f(400, 570), hunger < 0.3f ? sf::Color::Red : sf::Color::White, sf::Color::Black);
}

void Game::addPenguinOnFloe(int floe) {
	Penguin* penguin = new Penguin(floe);
	penguins.push_back(penguin);
}

void Game::addBloodAt(sf::Vector2f pos) {
	bloodSplashes.push_back(new ParticleSystem(100, ParticleMode::Explosion, "res/img/blood.png", pos));
}

void Game::addSplash() {
	splash = new ParticleSystem(200, ParticleMode::Splash, "res/img/splash.png", player->getRealPos(this)+player->getForwardVector()*30.f);
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
			if (len(game->center-rpos) > minDist)
				continue;
			addedPositions.insert(pos);

			bool haspenguin = rnd() < 0.1f;


			if (!haspenguin && rnd() > 1.f-0.54f*min(1.f, game->sinceStart/60))
				continue;

			game->icefloes[floeIndex] = new Icefloe(rpos, floeIndex);
			floeIndex++;

			if (haspenguin) {
				game->addPenguinOnFloe(floeIndex - 1);
			}
		}
	}
	vector<int> toBeDeleted;
	for (auto floe : game->icefloes){
		if (len(game->center-floe.second->pos) > maxDist)
			toBeDeleted.push_back(floe.first);
	}
	for (int i : toBeDeleted){
		game->icefloes.erase(i);
	}
}

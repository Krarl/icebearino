#include "game.h"
#include <iostream>
#include <string> 
using namespace std;

void Game::init(){
	cout << "hej" << endl;
}

void Game::update(float dt){
	this->dt = dt;
	for (auto p : penguins)
		p.second->update(this);
}


void Game::render(){

}
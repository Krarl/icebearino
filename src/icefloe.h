#ifndef ICEFLOE_H_
#define ICEFLOE_H_
#include <SFML/Graphics.hpp>
#include "polygon.h"
#include "macros.h"

class Game;

struct Part {
public:
	Part();
	Part(vector<V2f> pol);
	float life;
	Polygon polygon;
};

class Icefloe {
public:
	Icefloe();
	Icefloe(V2f pos, int ind);
	int ind;
	V2f pos, vel;
	vector<Part> parts;
	void update(Game* game);
	void render(Game* game);
	bool inside(V2f point, bool precise = true);
	float mass, rad;

};

#endif

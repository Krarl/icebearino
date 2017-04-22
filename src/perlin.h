#ifndef PERLIN_H_
#define PERLIN_H_
#include "macros.h"

class Perlin {
public:
	float scale = 0.01;
	map<piii, float> cache;
	float smooth(float a, float b, float f);
	float perlAt(V3f p);

};

#endif

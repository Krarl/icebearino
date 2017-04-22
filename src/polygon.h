#ifndef POLYGON_H_
#define POLYGON_H_
#include <SFML/Graphics.hpp>
#include "macros.h"
using namespace std;


class Polygon {
public:
	Polygon();
	Polygon(vector<V2f> points);
	bool inside(V2f point);
	float area();
	vector<V2f> points;
};

#endif

#ifndef POLYGON_H_
#define POLYGON_H_
#include <SFML/Graphics.hpp>
#include "macros.h"
using namespace std;


class Polygon {
	Polygon();
	Polygon(vector<V2f> points);
	vector<V2f> points;
};

#endif
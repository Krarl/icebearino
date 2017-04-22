#ifndef MACROS_H_
#define MACROS_H_
#include <map>
#include <set>
#include <utility>
#include <math.h>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

typedef sf::Vector2f V2f;
typedef sf::Vector3f V3f;
typedef pair<int, int> pii;
typedef pair<pii, int> piii;
#define rep(a, b, c) for(int a = (b); a < int(c); a++)

#define MT(a, b, c) piii(pii(a, b), c)
#define FST first.first
#define SND first.second
#define TRD second

#endif

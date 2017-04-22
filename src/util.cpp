#include "util.h"

void loadTexture(sf::Texture& texture, string file) {
    auto size = texture.getSize();
    if (size.x == 0 && size.y == 0) {
        if (!texture.loadFromFile(file)) {
            cout << "Error loading texture " << file << endl;
        } else {
            cout << "Loaded texture " << file << endl;
        }
    }
}
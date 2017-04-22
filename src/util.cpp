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

void drawSprite(sf::Sprite& sprite, Game* game) {
    sf::FloatRect rect = sprite.getLocalBounds();
    sprite.setPosition(sprite.getPosition() + game->center + game->screenCenter - sf::Vector2f(rect.width / 2.0f, rect.height / 2.0f));
    game->window->draw(sprite);
}

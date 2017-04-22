#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "game.h"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    Game game;
    game.init(&window);

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("res/fonts/arial.ttf"))
        return EXIT_FAILURE;
    sf::Text text("Hello SFML", font, 50.0f);

    // Start the game loop
    sf::Clock deltaClock;
    float dt = 0.0f;
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            window.close();

        

        // Update game
        game.update(dt);        

        // Clear screen
        window.clear();

        // Render game
        game.render();

        // Update the window
        window.display();

        dt = deltaClock.restart().asSeconds();
    }
    return EXIT_SUCCESS;
}
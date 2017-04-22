#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "game.h"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Icebearino");
    Game game;
    game.init(&window);

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("res/fonts/arial.ttf"))
        return EXIT_FAILURE;

    bool gamerunning = false;

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
        if (gamerunning) {
            game.update(dt);
            if (game.over) {
                gamerunning = false;
            }
        } else {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)){
                game.init(&window);
                gamerunning = true;
            }
        }

        // Clear screen
        window.clear();

        // Render game
        game.render();
        if (!gamerunning){
            sf::Text title("ICEBEARINO", font, 100.0f);
            sf::FloatRect textRect = title.getLocalBounds();
            title.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
            title.setPosition(sf::Vector2f(400, 300));
            window.draw(title);

            //sf::Text startText("press space to start", font, 30.0f);
        }

        // Update the window
        window.display();

        dt = deltaClock.restart().asSeconds();
    }
    return EXIT_SUCCESS;
}

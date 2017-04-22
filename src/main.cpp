#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "game.h"
#include "util.h"
#include <sstream>

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

    // Death sound
    sf::SoundBuffer deathSoundBuffer;
    loadSoundBuffer(deathSoundBuffer, "res/sound/death.ogg");
    sf::Sound deathSound;
    deathSound.setBuffer(deathSoundBuffer);

    // Icebearino sound
    sf::SoundBuffer icebearinoBuffer;
    loadSoundBuffer(icebearinoBuffer, "res/sound/icebearino.ogg");
    sf::Sound icebearinoSound;
    icebearinoSound.setBuffer(icebearinoBuffer);
    icebearinoSound.play();

    bool gamerunning = false;
    int highscore = 0;

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
                highscore = max(game.score, highscore);
                gamerunning = false;
                deathSound.play();
                game.cleanup();
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
        if (gamerunning) {
            game.render();
        } else if (!gamerunning) {
            sf::Text title("ICEBEARINO", font, 100.0f);
            sf::Text pressEnter("Press enter to start the game", font, 20.0f);

        	stringstream ss;
        	ss << "Highscore: " << highscore;
            sf::Text hs(ss.str(), font, 20.0f);

            sf::FloatRect textRect = title.getLocalBounds();
            title.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
            title.setPosition(sf::Vector2f(400, 250));

            textRect = pressEnter.getLocalBounds();
            pressEnter.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
            pressEnter.setPosition(sf::Vector2f(400, 320));

            textRect = hs.getLocalBounds();
            hs.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
            hs.setPosition(sf::Vector2f(400, 400));

            window.draw(title);
            window.draw(pressEnter);
            window.draw(hs);

            //sf::Text startText("press space to start", font, 30.0f);
        }

        // Update the window
        window.display();

        dt = deltaClock.restart().asSeconds();
    }
    return EXIT_SUCCESS;
}

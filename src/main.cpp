#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "game.h"
#include "particlesystem.h"
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
    if (!font.loadFromFile("res/fonts/Cinzel-Bold.ttf"))
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

    // Fact sounds
    sf::SoundBuffer factBuffers[7];
    loadSoundBuffer(factBuffers[0], "res/sound/facts-01.ogg");
    loadSoundBuffer(factBuffers[1], "res/sound/facts-02.ogg");
    loadSoundBuffer(factBuffers[2], "res/sound/facts-03.ogg");
    loadSoundBuffer(factBuffers[3], "res/sound/facts-04.ogg");
    loadSoundBuffer(factBuffers[4], "res/sound/facts-05.ogg");
    loadSoundBuffer(factBuffers[5], "res/sound/facts-06.ogg");
    loadSoundBuffer(factBuffers[6], "res/sound/facts-07.ogg");
    sf::Sound factSound;
    float elapsedTime = 0.0f;

    // Zimmer sound
    sf::SoundBuffer zimmerBuffer;
    loadSoundBuffer(zimmerBuffer, "res/sound/zimmer.ogg");
    sf::Sound zimmerSound;
    zimmerSound.setBuffer(zimmerBuffer);

    // Snow effect
    ParticleSystem snow(1000, ParticleMode::Snow, "res/img/snowflake.png");

    bool gamerunning = false;
    int highscore = 0;

    sf::Clock gameTimer;

    sf::Text intro1("CLIMATE CHANGE IS REAL", font, 50.0f);
    sf::Text intro2a("THE ARCTIC WORLD", font, 50.0f);
    sf::Text intro2b("IS SHRINKING", font, 50.0f);
    sf::Text intro3a("YOU ARE THE LAST", font, 50.0f);
    sf::Text intro3b("OF YOUR KIND", font, 50.0f);
    sf::Text intro4("WILL YOU SURVIVE?", font, 50.0f);

    centerText(intro1);
    centerText(intro2a);
    centerText(intro2b);
    centerText(intro3a);
    centerText(intro3b);
    centerText(intro4);

    intro1.setPosition(400, 200);
    intro2a.setPosition(400, 200);
    intro2b.setPosition(400, 250);
    intro3a.setPosition(400, 200);
    intro3b.setPosition(400, 250);
    intro4.setPosition(400, 200);

    const float perText = 4.0f;
    const int numTexts = 4;

	sf::Music music;
	music.openFromFile("res/sound/music.ogg");
	music.setLoop(true);
	music.setVolume(50);
	bool musicPlaying = false;

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
            snow.update(dt);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)){
                game.init(&window);
                gamerunning = true;
            }
        }

        float fade = 0.0f;

        // Clear screen
        window.clear();

        // Render game
        if (gamerunning) {
			if (!musicPlaying){
				musicPlaying = true;
				music.play();
			}
            game.render();
        } else if (!gamerunning) {
			if (musicPlaying)
				music.stop(), musicPlaying = false;
            sf::Text title("ICEBEARINO", font, 100.0f);
            sf::Text pressEnter("Press enter to start the game", font, 20.0f);

        	stringstream ss;
        	ss << "Highscore: " << highscore;
            sf::Text hs(ss.str(), font, 20.0f);


            centerText(title);
            title.setPosition(sf::Vector2f(400, 250));

            centerText(pressEnter);
            pressEnter.setPosition(sf::Vector2f(400, 320));

            centerText(hs);
            hs.setPosition(sf::Vector2f(400, 400));

            auto curTime = gameTimer.getElapsedTime();
            if (curTime > sf::seconds(numTexts * perText)) {
                float t = (curTime - sf::seconds(perText * numTexts)).asSeconds();
                fade = 1.0f - max(0.0f, min(1.0f, 2.0f - t));
                if (t > 1.0f && t < 2.0f && icebearinoSound.getStatus() != sf::SoundSource::Status::Playing)
                    icebearinoSound.play();              

                window.draw(title);
                window.draw(pressEnter);
                window.draw(hs);
            }

            if (curTime > sf::seconds(0.0f * perText) && curTime < sf::seconds(1.0f * perText)) {
                float t = (curTime - sf::seconds(perText * 0.0f)).asSeconds();
                fade = 1.0f - max(0.0f, min(1.0f, abs(2.0f - t)));
                window.draw(intro1);
                if (t > 1.0f && t < 2.0f && zimmerSound.getStatus() != sf::SoundSource::Status::Playing)
                    zimmerSound.play();
            }
            if (curTime > sf::seconds(1.0f * perText) && curTime < sf::seconds(2.0f * perText)) {
                float t = (curTime - sf::seconds(perText * 1.0f)).asSeconds();
                fade = 1.0f - max(0.0f, min(1.0f, abs(2.0f - t)));
                window.draw(intro2a);
                window.draw(intro2b);
                if (t > 1.0f && t < 2.0f && zimmerSound.getStatus() != sf::SoundSource::Status::Playing)
                    zimmerSound.play();
            }
            if (curTime > sf::seconds(2.0f * perText) && curTime < sf::seconds(3.0f * perText)) {
                float t = (curTime - sf::seconds(perText * 2.0f)).asSeconds();
                fade = 1.0f - max(0.0f, min(1.0f, abs(2.0f - t)));
                window.draw(intro3a);
                window.draw(intro3b);
                if (t > 1.0f && t < 2.0f && zimmerSound.getStatus() != sf::SoundSource::Status::Playing)
                    zimmerSound.play();
            }
            if (curTime > sf::seconds(3.0f * perText) && curTime < sf::seconds(4.0f * perText)) {
                float t = (curTime - sf::seconds(perText * 3.0f)).asSeconds();
                fade = 1.0f - max(0.0f, min(1.0f, abs(2.0f - t)));
                window.draw(intro4);
                if (t > 1.0f && t < 2.0f && zimmerSound.getStatus() != sf::SoundSource::Status::Playing)
                    zimmerSound.play();
            }            

            sf::RectangleShape fadeRect(sf::Vector2f(800.0f, 600.0f));
            fadeRect.setPosition(0.0f, 0.0f);
            fadeRect.setFillColor(sf::Color(0, 0, 0, 255*(1.0f-fade)));
            window.draw(fadeRect);

            window.draw(snow);            
        }

        elapsedTime += dt;
        if (elapsedTime > 15.0f) {
            elapsedTime = 0.0f;            
            if (rnd() < 0.1f) {
                factSound.setBuffer(factBuffers[rand() % 7]);
                factSound.play();
            }
        }

        // Update the window
        window.display();

        dt = deltaClock.restart().asSeconds();
    }
    return EXIT_SUCCESS;
}

#include "Application.h"
#include "GameManager.h"
#include "HumanAgent.h"

Application::Application(sf::RenderWindow &window) : window(window) {
    this->window.setFramerateLimit(60);

    bgTexture.loadFromFile("../assets/background-day.png");
    bgSprite.setTexture(bgTexture);
    bgSprite.setPosition(0.f, 0.f);

    // TODO: add buttons
    startGameBtn = Button(100.f, 100.f, sf::Color::Green, sf::Vector2f(50.f, 50.f));
}

void Application::run() {
    bool isRunning = true;
    while (isRunning) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                isRunning = false;
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (startGameBtn.isPressed(float(event.mouseButton.x), float(event.mouseButton.y))) {
                        // TODO: create agent
                        HumanAgent agent;

                        GameManager game(window, agent);
                        game.startGame();
                    }
                }
            }
        }

        draw();
        window.display();
    }
}

void Application::draw() {
    window.draw(bgSprite);
    window.draw(startGameBtn.getShape());
}

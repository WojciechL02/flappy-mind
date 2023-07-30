#include "Application.h"

Application::Application(sf::RenderWindow &window) : window(window) {
    this->window.setFramerateLimit(60);
//    add button
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
                        // TODO: start game
                        isRunning = false;
                        window.close();
                    }
                }
            }
        }

        draw();
        window.display();
    }
}

void Application::draw() {
    window.draw(startGameBtn.getShape());
}
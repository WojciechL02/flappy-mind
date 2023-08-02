#include <memory>
#include "Application.h"
#include "GameManager.h"
#include "HumanAgent.h"

Application::Application(sf::RenderWindow &window) : window(window) {
    this->window.setFramerateLimit(60);

    bgTexture.loadFromFile("../assets/background-day.png");
    bgSprite.setTexture(bgTexture);
    bgSprite.setPosition(0.f, 0.f);

    titleTexture.loadFromFile("../assets/title.png");
    titleSprite.setTexture(titleTexture);
    titleSprite.setPosition(45.f, 45.f);

    playerBtnTexture.loadFromFile("../assets/player_btn.png");
    qlearningBtnTexture.loadFromFile("../assets/qlearning_btn.png");
    sarsaBtnTexture.loadFromFile("../assets/sarsa_btn.png");

    humanAgentBtn = Button(65.f, 220.f, playerBtnTexture);
    qlearningBtn = Button(65.f, 300.f, qlearningBtnTexture);
    sarsaBtn = Button(65.f, 380.f, sarsaBtnTexture);
}

void Application::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    bool isButtonPressed = false;
                    std::unique_ptr<Agent> agent;

                    if (humanAgentBtn.isPressed(float(event.mouseButton.x), float(event.mouseButton.y))) {
                        // TODO: create agent
                        agent = std::make_unique<HumanAgent>();
                        isButtonPressed = true;
                    }// TODO: add other agents

                    if (isButtonPressed) {
                        GameManager game(window, *agent);
                        while (game.isRunNewGame()) {
                            game.startGame();
                            game.resetGameConfiguration();
                        }
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
    window.draw(titleSprite);
    window.draw(humanAgentBtn.sprite);
    window.draw(qlearningBtn.sprite);
    window.draw(sarsaBtn.sprite);
}

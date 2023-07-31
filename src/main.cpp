#include <SFML/Graphics.hpp>
#include "Application.h"

int main()
{
    sf::RenderWindow win(sf::VideoMode(288, 512), "Flappy Mind");
    Application app(win);
    app.run();
    return 0;
}

#include "stdafx.h"
#include "Game.h"

int main() {

   /* sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(50.f, 50.f));
    shape.setPosition(0, 0);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);
        window.draw(shape);
        std::cout << shape.getGlobalBounds().left << " " << shape.getGlobalBounds().top;

        // end the current frame
        window.display();
    }*/

	Game game;

	while(game.run()){}

	return 0;
}
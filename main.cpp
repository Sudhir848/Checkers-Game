/* Copyright [2023] <Sudhir Gunaseelan> */

#include <iostream>
#include "Checkers.hpp"
#include <SFML/Graphics.hpp>

int main(int argc, const char* argv[]) {
    sf::RenderWindow window(sf::VideoMode(8 * 64 + 64, 8 * 64 + 64), "Checkers");
    Checkers checkers;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                // Convert the pixel coordinates to tile coordinates and handle user input
                int x = (event.mouseButton.x - checkers.getBorderSize()) / 64;
                int y = (event.mouseButton.y - checkers.getBorderSize()) / 64;
                // Handle user input
                if (x >= 0 && x < 8 && y >= 0 && y < 8) {
                    if (checkers.getSelectedX() == -1 && checkers.getSelectedY() == -1) {
                        // No piece selected yet, select a piece
                        checkers.selectPiece(x, y);
                    } else {
                        // A piece is already selected, move it to the new location
                        checkers.movePiece(x, y, [&](int newX, int newY) {});
                    }
                }
            }
        }
        window.clear(sf::Color(128, 128, 128));
        window.draw(checkers);
        window.display();
    }
    return 0;
}

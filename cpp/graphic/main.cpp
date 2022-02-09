#include "Window.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

void poll_window_events(Window &window)
{
    sf::Event ev;

    while (window.pollEvent(ev));
}

void draw_window(Window &window)
{
    // Draw grid
    // Draw players name and objects
    // Draw which player turn
    // If is ai, draw
}

int main(void)
{
    Window window(sf::VideoMode::getDesktopMode(), "Gomoku", sf::Style::Fullscreen);
    sf::Event ev;

    while (window.isOpen()) {
        poll_window_events(window);
        draw_window(window);
    }
}
#include "Window.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>

void manage_mouse_release(sf::Event &ev, Window &window)
{
    sf::Vector2u size = window.getSize();
    float decal = (size.x - size.y) / 1.2;
    float spacing = size.y / 22;
    int x = int(round((ev.mouseButton.x - decal - spacing) / spacing));
    int y = int(round((ev.mouseButton.y - spacing * 2) / spacing));
    if (x < 0 || y < 0 || x > 18 || y > 18 || window[x][y] != 0)
        return;
    window[x][y] = 1;
}

void poll_window_events(Window &window)
{
    sf::Event ev;

    while (window.pollEvent(ev)) {
        if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
            window.close();
        if (ev.type == sf::Event::MouseButtonReleased)
            manage_mouse_release(ev, window);
    }
}

void draw_window(Window &window)
{
    window.clear(sf::Color(246,230,189, 255));
    // Draw which player turn, players name and objects
    window.draw_texts();

    // Draw grid
    draw_grid(window);
    // Draw pebbles

    // If is ai playing, draw a text
    window.draw_ai_thinking();
    // Draw players name and objects
    // Draw which player turn
    // If is ai, draw
    window.display();
}

int main(void)
{
    Window window(sf::VideoMode::getDesktopMode(), "Gomoku", sf::Style::Fullscreen);

    while (window.isOpen()) {
        poll_window_events(window);
        draw_window(window);
        if (window.get_is_ia_thinking()) {
            // play_ai(window);
            window.set_is_ia_thinking(false);
        }
    }
}
#include "Window.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

void draw_pebble(Window &window, float decal, float spacing)
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (window[i][j] == 1) {
                window.white_pebble.setPosition(sf::Vector2f(decal + spacing * (i + 1), spacing * (j + 2)));
                window.draw(window.white_pebble);
            }
            if (window[i][j] == -1) {
                window.black_pebble.setPosition(sf::Vector2f(decal + spacing * (i + 1), spacing * (j + 2)));
                window.draw(window.black_pebble);
            }
        }
    }
}

void draw_grid(Window &window)
{
    sf::Vector2u size = window.getSize();
    float decal = (size.x - size.y) / 1.2;
    float spacing = size.y / 22;
    sf::RectangleShape rectangle_h(sf::Vector2f(size.y - spacing * 2 + 2, 4));
    sf::RectangleShape rectangle_v(sf::Vector2f(4, size.y - spacing * 2));
    rectangle_h.setFillColor(sf::Color::Black);
    rectangle_v.setFillColor(sf::Color::Black);
    rectangle_h.setPosition(sf::Vector2f(decal, spacing));
    rectangle_v.setPosition(sf::Vector2f(decal, spacing));
    window.draw(rectangle_h);
    window.draw(rectangle_v);
    for (int i = 0; i < SIZE + 1; i++) {
        rectangle_h.setPosition(sf::Vector2f(decal, spacing * (i + 2)));
        rectangle_v.setPosition(sf::Vector2f(decal + spacing * (i + 1), spacing));
        window.draw(rectangle_h);
        window.draw(rectangle_v);
    }
    draw_pebble(window, decal, spacing);
}
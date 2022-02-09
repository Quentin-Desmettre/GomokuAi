#include "Window.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <thread>

void play_ai(Window &window);

void manage_mouse_release(sf::Event &ev, Window &window)
{
    sf::Vector2u size = window.getSize();
    float decal = (size.x - size.y) / 1.2;
    float spacing = size.y / 22;
    int x = int(round((ev.mouseButton.x - decal - spacing) / spacing));
    int y = int(round((ev.mouseButton.y - spacing * 2) / spacing));
    if (x < 0 || y < 0 || x > 18 || y > 18 || window[x][y] != 0 || window.get_victory() != 0)
        return;
    window[x][y] = 1;
    print_winner(window);
    window.set_is_ia_thinking(true);
    window.is_thread = false;
}

void reset_window(Window &win)
{
    char **grid = win.get_grid();

    win.set_is_ia_thinking(false);
    win.is_thread = false;
    win.set_turn(1);
    win.change_victory(0);
    for (int i = 0; i < SIZE; i++)
        memset(grid[i], 0, sizeof(char) * SIZE);
}

void poll_window_events(Window &window)
{
    sf::Event ev;

    while (window.pollEvent(ev)) {
        if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
            window.close();
        if (ev.type == sf::Event::MouseButtonReleased && !window.get_is_ia_thinking())
            manage_mouse_release(ev, window);
        if (window.get_victory() && ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Enter)
            reset_window(window);
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
    sf::Event ev;

    while (window.isOpen()) {
        poll_window_events(window);
        draw_window(window);
        if (window.get_is_ia_thinking() && !window.is_thread) {
            window.is_thread = true;
            play_ai(window);
            print_winner(window);
            while (window.pollEvent(ev))
                if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
                    window.close();
            window.is_thread = false;
            window.set_is_ia_thinking(false);
            window.set_turn(window.get_turn() + 1);
        }
    }
}
#include "Window.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

void manage_mouse_release(sf::Event &ev)
{
    /*
        if (is_on_grid(ev))
            play_move(ev);
            window.set_ai_thinking(true);
        
    */
}

void poll_window_events(Window &window)
{
    sf::Event ev;

    while (window.pollEvent(ev)) {
        if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
            window.close();
        if (ev.type == sf::Event::MouseButtonReleased)
            manage_mouse_release(ev);
    }
}

void draw_window(Window &window)
{
    window.clear(sf::Color::White);
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
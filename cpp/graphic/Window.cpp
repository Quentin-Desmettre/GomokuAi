#include "Window.hpp"
#include <string>

std::string toString(int integer)
{
    char numstr[10]; // enough to hold all numbers up to 32-bits
    sprintf(numstr, "%i", integer);
    return numstr;
}

Window::Window(sf::VideoMode mode, std::string name, sf::Uint8 style):
    sf::RenderWindow(mode, name, style)
{
    for (int i = 0; i < SIZE; i++)
        memset(m_grid[i], 0, sizeof(char) * SIZE);
    sf::Vector2u size = getSize();

    sf::Font font;
    font.loadFromFile("font.ttf");

    m_turn.setFont(font);

    m_player_1.setFont(font);

    m_player_2.setFont(font);
    
    m_turn.setCharacterSize(size.y / 20);
    m_player_1.setCharacterSize(size.y / 20);
    m_player_2.setCharacterSize(size.y / 20);
}

void Window::draw_ai_thinking()
{
    if (m_is_ia_thinking)
        draw(ai_thinking);
}

void Window::draw_texts()
{
    m_turn.setString(toString(this->turn));
    draw(m_turn);
    draw(m_player_1);
    draw(m_player_2);
}

Window::~Window()
{
}
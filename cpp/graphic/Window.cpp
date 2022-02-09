#include "Window.hpp"
#include <string>
#include <iostream>

std::string toString(int integer)
{
    char numstr[10];
    sprintf(numstr, "%i", integer);
    return numstr;
}

void init_text(sf::Text &text, sf::Font &font, Window *w, std::string t, sf::Vector2f pos = sf::Vector2f(0, 0))
{
    text.setFont(font);
    text.setColor(sf::Color::Black);
    text.setString(t);
    text.setPosition(pos);
    text.setCharacterSize(w->getSize().y / 20);
}

Window::Window(sf::VideoMode mode, std::string name, sf::Uint8 style):
    sf::RenderWindow(mode, name, style),
    m_is_ia_thinking(false),
    turn(0)
{
    for (int i = 0; i < SIZE; i++)
        memset(m_grid[i], 0, sizeof(char) * SIZE);
    sf::Vector2u size = getSize();

    font.loadFromFile("font.ttf");

    init_text(m_turn, font, this, "", sf::Vector2f());
    init_text(ai_thinking, font, this, "AI is thinking...");
    init_text(m_player_1, font, this, "Player 1: ");
    init_text(m_player_2, font, this, "AI: ");
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
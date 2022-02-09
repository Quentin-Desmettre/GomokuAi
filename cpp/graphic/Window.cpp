#include "Window.hpp"
#include <string>
#include <iostream>

std::string toString(int integer)
{
    char numstr[10]; // enough to hold all numbers up to 32-bits
    sprintf(numstr, "%i", integer);
    return numstr;
}

Window::Window(sf::VideoMode mode, std::string name, sf::Uint8 style):
    sf::RenderWindow(mode, name, style),
    m_is_ia_thinking(false),
    turn(0)
{
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++)
        memset(m_grid[i], rand() % 3 - 1, sizeof(char) * SIZE);
    sf::Vector2u size = getSize();

    sf::Font *font = new sf::Font;
    font->loadFromFile("font.ttf");

    m_turn.setFont(*font);
    ai_thinking.setFont(*font);
    m_player_1.setFont(*font);
    m_player_2.setFont(*font);

    m_turn.setPosition(sf::Vector2f(100, 100));

    m_turn.setCharacterSize(30);
    ai_thinking.setCharacterSize(size.y / 20);
    m_player_1.setCharacterSize(size.y / 20);
    m_player_2.setCharacterSize(size.y / 20);

    sf::Texture *a = new sf::Texture;
    sf::Texture *b = new sf::Texture;
    a->loadFromFile("img/white.png");
    white_pebble.setOrigin(sf::Vector2f(128, 128));
    white_pebble.setTexture(*a);
    white_pebble.setScale(sf::Vector2f(0.19, 0.19));
    b->loadFromFile("img/black.png");
    black_pebble.setOrigin(sf::Vector2f(128, 128));
    black_pebble.setScale(sf::Vector2f(0.19, 0.19));
    black_pebble.setTexture(*b);
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
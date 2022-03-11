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
    text.setFillColor(sf::Color::Black);
    text.setString(t);
    text.setPosition(pos);
    text.setCharacterSize(w->getSize().y / 15);
    text.setFillColor(sf::Color::Black);
}

Window::Window(sf::VideoMode mode, std::string name, sf::Uint8 style):
    sf::RenderWindow(mode, name, style),
    m_is_ia_thinking(false),
    turn(1),
    mode(false),
    is_pause(false)
{
    victory = 0;
    sf::Vector2u size = getSize();
    m_grid = (char **)malloc(sizeof(char *) * SIZE);
    for (int i = 0; i < SIZE; i++) {
        m_grid[i] = (char *)malloc(sizeof(char) * SIZE);
        memset(m_grid[i], 0, sizeof(char) * SIZE);
    }

    font.loadFromFile("font.ttf");

    init_text(m_new_round, font, this, "ENTER to retry", sf::Vector2f(size.x * 0.01, size.y * 0.85));
    init_text(m_turn, font, this, "", sf::Vector2f(size.x * 0.01, size.y * 0.55));
    init_text(ai_thinking, font, this, "AI is thinking...", sf::Vector2f(size.x / 2, size.y / 2.5));
    init_text(m_player_1, font, this, "Player 1: ", sf::Vector2f(size.x * 0.01, size.y * 0.15));
    init_text(m_player_2, font, this, "AI: ", sf::Vector2f(size.x * 0.01, size.y * 0.35));
    init_text(y_lose, font, this, "You Lose !", sf::Vector2f(size.x * 0.01, size.y * 0.75));
    init_text(y_win, font, this, "You Won !", sf::Vector2f(size.x * 0.01, size.y * 0.75));

    y_win.setFillColor(sf::Color::Red);
    y_lose.setFillColor(sf::Color::Red);

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
    if (m_is_ia_thinking && !mode)
        draw(ai_thinking);
}

void Window::change_victory(int nb)
{
    victory = nb;
}

int Window::get_victory()
{
    return victory;
}

void Window::draw_texts()
{
    sf::Vector2u size = getSize();
    const double scale_fac = 1.7;

    m_turn.setString("Turn number " + toString(this->turn));

    draw(m_turn);
    draw(m_player_1);

    white_pebble.setPosition(size.x * 0.25, size.y * 0.185);
    white_pebble.scale(scale_fac, scale_fac);
    draw(white_pebble);
    white_pebble.scale(1/scale_fac, 1/scale_fac);

    draw(m_player_2);
    black_pebble.setPosition(size.x * 0.12, size.y * 0.385);
    black_pebble.scale(scale_fac, scale_fac);
    draw(black_pebble);
    black_pebble.scale(1/scale_fac, 1/scale_fac);
    if (victory == 1)
        draw(y_win);
    if (victory == 2)
        draw(y_lose);
    if (victory)
        draw(m_new_round);
}

Window::~Window()
{
}
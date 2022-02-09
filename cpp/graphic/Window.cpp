#include "Window.hpp"

Window::Window(sf::VideoMode mode, std::string name, sf::Uint8 style):
    sf::RenderWindow(mode, name, style)
{
    for (int i = 0; i < SIZE; i++)
        memset(m_grid[i], 0, sizeof(char) * SIZE);
}

Window::~Window()
{
}
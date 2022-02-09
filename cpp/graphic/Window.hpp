#include <SFML/Graphics.hpp>
#include <string>
#include "gomoku.hpp"

class Window : public sf::RenderWindow
{
private:
    bool m_is_ia_thinking;
    char m_grid[SIZE][SIZE];

public:
    Window(sf::VideoMode mode, std::string name, sf::Uint8 style);
    ~Window();
};

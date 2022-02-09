#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
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

    char **get_grid(void) {return (char **)m_grid;}
    bool get_is_ia_thinking(void) {return m_is_ia_thinking;}

    char *operator[](int const& i) {return m_grid[i];}
};

void draw_grid(Window &window);

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include "gomoku.hpp"

class Window : public sf::RenderWindow
{
private:
    bool m_is_ia_thinking;
    char m_grid[SIZE][SIZE];
    int turn;
    sf::Text m_turn, m_player_1, m_player_2, ai_thinking;
    sf::Font font;

public:
    Window(sf::VideoMode mode, std::string name, sf::Uint8 style);
    ~Window();

    sf::Sprite white_pebble;
    sf::Sprite black_pebble;

    char **get_grid(void) {return (char **)m_grid;}
    bool get_is_ia_thinking(void) {return m_is_ia_thinking;}

    char *operator[](int const& i) {return m_grid[i];}
    void set_is_ia_thinking(bool new_val) {m_is_ia_thinking = new_val;}

    void draw_texts();
    void draw_ai_thinking();
};

void draw_grid(Window &window);
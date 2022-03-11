#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include "gomoku.hpp"

class Window : public sf::RenderWindow
{
private:
    bool m_is_ia_thinking;
    char **m_grid;
    int turn;
    int victory;
    sf::Text m_turn, m_player_1, ai_thinking, y_lose, y_win;
    sf::Font font;
    sf::Text m_new_round;

public:
    move_t last_move;
    int mode;
    bool is_pause;
    sf::Sprite white_pebble;
    sf::Sprite black_pebble;
    move_list moves;
    sf::Text m_player_2;

    Window(sf::VideoMode mode, std::string name, sf::Uint8 style);
    ~Window();


    char **get_grid(void) {return (char **)m_grid;}
    bool get_is_ia_thinking(void) {return m_is_ia_thinking;}

    char *operator[](int const& i) {return m_grid[i];}
    void set_is_ia_thinking(bool new_val) {m_is_ia_thinking = new_val;}

    void draw_texts();
    void draw_ai_thinking();
    void change_victory(int nb);
    int get_victory();
    void set_turn(int nb) {turn = nb;}
    int get_turn(void) {return turn;}
};

void draw_grid(Window &window);
void print_winner(Window &window);
void play_ai(Window &window, bool is_ia = true);

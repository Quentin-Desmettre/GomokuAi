#include "Window.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <thread>
#include <unistd.h>

void manage_mouse_release(sf::Event &ev, Window &window, bool *turn)
{
    sf::Vector2u size = window.getSize();
    float decal = (size.x - size.y) / 1.2;
    float spacing = size.y / 22;
    int x = int(round((ev.mouseButton.x - decal - spacing) / spacing));
    int y = int(round((ev.mouseButton.y - spacing * 2) / spacing));
    if (x < 0 || y < 0 || x > 18 || y > 18 || window[x][y] != 0 || window.get_victory() != 0)
        return;
    if (turn) {
        window[x][y] = *turn ? 1 : -1;
        *turn = !(*turn);
        window.set_turn(window.get_turn() + *turn);
    } else
        window[x][y] = 1;
    print_winner(window);
    window.set_is_ia_thinking(turn ? false : true);
}

void reset_window(Window &win, bool *gen, int *z, bool *turn)
{
    char **grid = win.get_grid();

    win.set_is_ia_thinking(false);
    win.set_turn(1);
    win.change_victory(0);
    if (gen)
        *gen = true;
    if (z)
        *z = 0;
    if (turn)
        *turn = true;
    for (int i = 0; i < SIZE; i++)
        memset(grid[i], 0, sizeof(char) * SIZE);
}

void undo_last_move(Window &window, bool *gen)
{
    move_t m = window.moves.back();

    window[m.first][m.second] = 0;
    window.moves.pop_back();
    if (window.moves.size() == 0)
        *gen = true;
}

void manage_direction(Window &window, sf::Event &ev, int *i, bool *turn, bool *gen)
{
    if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Right)
        window.is_pause = !window.is_pause;
    if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Left) {
        if (window.moves.size() == 0)
            return;
        undo_last_move(window, gen);
        if (i)
            *i += 1;
        if (turn)
            *turn = !(*turn);
        window.change_victory(0);
    }
}

void poll_window_events(Window &window, bool *gen, int *i, bool *turn)
{
    sf::Event ev;

    while (window.pollEvent(ev)) {
        if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
            window.close();
        if (!window.mode && ev.type == sf::Event::MouseButtonReleased && !window.get_is_ia_thinking())
            manage_mouse_release(ev, window, turn);
        if (window.get_victory() && ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Enter)
            reset_window(window, gen, i, turn);
        if (window.mode)
            manage_direction(window, ev, i, turn, gen);
    }
}

void ai_playing(Window &window, bool turn = true)
{
    sf::Event ev;

    play_ai(window, turn);
    while (window.pollEvent(ev) && !window.mode)
        if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
            window.close();
}

void draw_window(Window &window)
{
    window.clear(sf::Color(246,230,189, 255));

    window.draw_texts();
    draw_grid(window);
    if (!window.get_victory())
        window.draw_ai_thinking();

    window.display();
}

void game_loop(Window &window, bool *gen = nullptr, int *i = nullptr, bool *turn = nullptr)
{
    print_winner(window);
    poll_window_events(window, gen, i, turn);
    draw_window(window);
}

void ai_vs_ai(Window &window)
{
    bool gen = true;
    bool turn = false;

    window.mode = 1;
    window.is_pause = true;
    srand(time(nullptr));
    for (int i = 0; window.isOpen(); i++) {
        game_loop(window, &gen, &i, &turn);
        if (window.is_pause || window.get_victory()) {
            i--;
            continue;
        }
        ai_playing(window, turn);
        turn = !turn;
        window.is_pause = true;
    }
}

void player_vs_ai(Window &window)
{
    srand(time(nullptr));
    int is_ai_first = rand() % 2;
    bool is_victory = false;

    if (is_ai_first)
        ai_playing(window);
    while (window.isOpen()) {
        game_loop(window);
        if (window.get_victory()) {
            is_victory = true;
            continue;
        }
        if (is_victory) {
            is_ai_first = rand() % 2;
            if (is_ai_first)
                ai_playing(window);
            is_victory = false;
            continue;
        }
        if (window.get_is_ia_thinking()) {
            ai_playing(window);
            window.set_is_ia_thinking(false);
            window.set_turn(window.get_turn() + 1);
        }
    }
}

void pvp_mode(Window &window)
{
    bool turn = true;

    for (int i = 0; window.isOpen(); i++) {
        game_loop(window, nullptr, nullptr, &turn);
        if (window.get_victory())
            continue;
    }
}

int main(int ac, char **av)
{
    Window window(sf::VideoMode::getDesktopMode(), "Gomoku", sf::Style::Fullscreen);
    window.setFramerateLimit(24);

    if (ac > 1 && av[1] == std::string("spectator"))
        ai_vs_ai(window);
    else if (ac > 1 && av[1] == std::string("2player"))
        pvp_mode(window);
    else
        player_vs_ai(window);
    return 0;
}

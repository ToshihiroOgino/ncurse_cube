#include "game.h"

#include "cube_3d_view.h"
#include "linked_list.h"
#include <ncurses.h>
#include <time.h>

int game_init();
void game_loop();
void print_list(int x, int y, Node *list);

void game_main() {
    if (game_init())
        game_loop();
}

int game_init() {
    initscr();

    if (has_colors() == FALSE)
        mvprintw(1, 0, "Ur therminal does not support color\n");

    start_color();
    init_cube_colors();

    clear();

    load_3d_format();

    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, true);
    timeout(100);
    return 1;
}

void game_loop() {
    Cube *cube = gen_cube();
    scramble_cube(20, cube);

    draw_cube(cube);
    draw_3d_cube(cube);
    refresh();

    int lastSize = LINES * 10000 + COLS;

    char input;
    int q_count = 0;
    bool loop = true;

    time_t start = time(NULL);

    while (loop) {
        input = getch();
        switch (input) {
        case 'q':
        case 'Q':
            q_count++;
            if (q_count >= 2)
                loop = false;
            for (int i = 0; i < COLS; i++)
                mvprintw(1, i, " ");
            mvprintw(1, 0, "Press Q again to close the game");
            break;
        case 'c':
        case 'C':
            if (cube->moves != 0) {
                Node *tmp = cube->moves->edge->head;
                int cnt = 0;
                while (tmp != 0) {
                    mvprintw(0, cnt, " ");
                    tmp = tmp->next;
                    cnt++;
                }
                cube->moves = 0;
            }
            break;
        default:
            if (input != -1) {
                q_count = 0;
                if (move_cube(input, cube)) {
                    print_list(0, 0, cube->moves);
                    draw_cube(cube);
                    draw_3d_cube(cube);
                    if (is_solved(cube)) {
                        for (int i = 0; i < COLS; i++)
                            mvprintw(1, i, " ");
                        time_t t = time(NULL) - start;
                        mvprintw(1, 0, "Solved! Time:%2dmin%2dsec (press Q to close the game)", t / 60, t % 60);
                        q_count = 1;
                    }
                }
            }
            break;
        }

        if (lastSize != LINES * 10000 + COLS) {
            lastSize = LINES * 10000 + COLS;
            draw_3d_cube(cube);
            draw_3d_format();
        }

        refresh();
    }
    endwin();
}

void print_list(int x, int y, Node *list) {
    if (list == 0)
        return;
    int len = list->edge->length;
    list = list->edge->head;
    for (int i = 0; i < len; i++) {
        mvprintw(y, x + i, "%c", list->key);
        list = list->next;
    }
}

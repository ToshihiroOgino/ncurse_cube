#include "cube.h"

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

Cube *gen_cube() {
    Cube *c = (Cube *)malloc(sizeof(Cube));
    srand((unsigned)time(NULL));
    for (int i = 0; i < 9; i++) {
        c->u[i] = White;
        c->d[i] = Yellow;
        c->f[i] = Green;
        c->b[i] = Blue;
        c->l[i] = Orange;
        c->r[i] = Red;
    }
    c->moves = 0;
    return c;
}

void init_cube_colors() {
    init_color(Black, 0, 0, 0);
    init_color(White, 1000, 1000, 1000);
    init_color(Yellow, 1000, 1000, 0);
    init_color(Orange, 900, 370, 0);
    init_color(Red, 1000, 0, 0);
    init_color(Green, 0, 1000, 0);
    init_color(Blue, 0, 0, 1000);
    init_pair(Black, White, Black);
    init_pair(White, Black, White);
    init_pair(Yellow, Black, Yellow);
    init_pair(Orange, Black, Orange);
    init_pair(Red, Black, Red);
    init_pair(Green, Black, Green);
    init_pair(Blue, Black, Blue);
}

void scramble_cube(int t, Cube *c) {
    int r1, r2;
    for (int i = 0; i < t; i++) {
        r1 = rand() % 6;
        r2 = rand() % 3 + 1;
        for (int j = 0; j < r2; j++) {
            switch (r1) {
            case 0:
                u_op(c);
                break;
            case 1:
                d_op(c);
                break;
            case 2:
                f_op(c);
                break;
            case 3:
                b_op(c);
                break;
            case 4:
                r_op(c);
                break;
            case 5:
                l_op(c);
                break;
            }
        }
    }
}

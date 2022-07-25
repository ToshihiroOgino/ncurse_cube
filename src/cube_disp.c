#include "cube.h"

#include <ncurses.h>

static char col_char[7] = {'#', 'W', 'G', 'O', 'Y', 'R', 'B'};

void draw_surface(int x, int y, Surface_Color s[9]) {
    for (int dy = 0; dy < 3; dy++)
        for (int dx = 0; dx < 3; dx++) {
            int i = dx + dy * 3;
            attron(COLOR_PAIR(s[i]));
            mvprintw(y + dy, x + dx, "%c", col_char[s[i]]);
            attroff(COLOR_PAIR(s[i]));
        }
}

void draw_cube(Cube *c) {
    int offset = 2;
    int gap = 1;
    draw_surface(3 + offset + gap, 0 + offset, c->u);
    draw_surface(0 + offset, 3 + offset + gap, c->l);
    draw_surface(3 + offset + gap, 3 + offset + gap, c->f);
    draw_surface(6 + offset + gap * 2, 3 + offset + gap, c->r);
    draw_surface(9 + offset + gap * 3, 3 + offset + gap, c->b);
    draw_surface(3 + offset + gap, 6 + offset + gap * 2, c->d);
}

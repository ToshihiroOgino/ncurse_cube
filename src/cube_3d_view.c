#include "cube_3d_view.h"

#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct SF {
    int x, y;
} SF;

SF *format;
char format_str[25][100];

static char col_char[7] = {'#', 'W', 'G', 'O', 'Y', 'R', 'B'};

const int bx = 20;
const int by = 3;

void load_3d_format() {
    format = (SF *)malloc(sizeof(SF) * 9 * 6);
    char str[100] = {};
    FILE *fp = fopen("./format.txt", "r");
    SF sf;
    sf.x = 0;
    sf.y = 0;
    while (fgets(str, 100, fp) != NULL) {
        for (sf.x = 0; sf.x < 85; sf.x += 1) {
            char ch = str[sf.x];
            format_str[sf.y][sf.x] = ch;
            if ('a' <= ch && ch <= '{')
                format[ch - 'a'] = sf;
            else if ('A' <= ch && ch <= '[')
                format[27 + ch - 'A'] = sf;
        }
        sf.y += 1;
    }
    fclose(fp);
    draw_3d_format();
}

void draw_3d_format() {
    attron(COLOR_PAIR(Black));
    for (int i = 0; i < 23; i++)
        for (int j = 0; j < 85; j++)
            if (format_str[i][j] == '|' || format_str[i][j] == '*')
                mvprintw(by + i, bx + j, "%c", format_str[i][j]);
    attroff(COLOR_PAIR(Black));
}

void draw_sf(SF sf, Surface_Color col) {
    attron(COLOR_PAIR(col));
    char ch = col_char[col];
    mvprintw(by + sf.y, bx + sf.x, "%c", ch);
    for (int i = 1; i <= 2; i++) {
        mvprintw(by + sf.y, bx + sf.x + i, "%c", ch);
        mvprintw(by + sf.y, bx + sf.x - i, "%c", ch);
    }
    for (int i = -1; i <= 1; i++) {
        mvprintw(by + sf.y + 1, bx + sf.x + i, "%c", ch);
        mvprintw(by + sf.y - 1, bx + sf.x - i, "%c", ch);
    }
    attroff(COLOR_PAIR(col));
}

void draw_sf_arr(int sf_num, Surface_Color col_arr[9], char face) {
    int bs = sf_num * 9;
    for (int i = 0; i < 9; i++)
        draw_sf(format[bs + i], col_arr[i]);

    SF s = format[bs + 4];
    attron(COLOR_PAIR(Black));
    mvprintw(by + s.y, bx + s.x, "%c", face);
    attroff(COLOR_PAIR(col_arr[4]));
}

void draw_3d_cube(Cube *c) {
    draw_sf_arr(0, c->u, 'U');
    draw_sf_arr(1, c->f, 'F');
    draw_sf_arr(2, c->r, 'R');
    draw_sf_arr(3, c->b, 'B');
    draw_sf_arr(4, c->l, 'L');
    draw_sf_arr(5, c->d, 'D');
}

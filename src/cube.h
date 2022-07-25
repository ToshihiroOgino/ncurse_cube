#ifndef CUBE_H_
#define CUBE_H_
#include "linked_list.h"
#include <stdbool.h>
typedef enum Surface_Color {
    Black = 0,
    White = 1,
    Green = 2,
    Orange = 3,
    Yellow = 4,
    Red = 5,
    Blue = 6
} Surface_Color;
typedef struct Cube {
    Surface_Color u[9], d[9], f[9], b[9], l[9], r[9];
    Node *moves;
} Cube;

Cube *gen_cube();
void init_cube_colors();
void scramble_cube(int times, Cube *cube);

void draw_surface(int x, int y, Surface_Color surface[9]);
void draw_cube(Cube *cube);

bool is_solved(Cube *cube);
bool move_cube(char input, Cube *cube);
void u_op(Cube *cube);
void d_op(Cube *cube);
void l_op(Cube *cube);
void r_op(Cube *cube);
void f_op(Cube *cube);
void b_op(Cube *cube);
void m_op(Cube *cube);
void s_op(Cube *cube);
void e_op(Cube *cube);
void x_op(Cube *cube);
void y_op(Cube *cube);
void z_op(Cube *cube);
#endif /* CUBE_H_ */

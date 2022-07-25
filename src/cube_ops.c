#include "cube.h"

// a->b->cb->d->a
void cycle(int *a, int *b, int *c, int *d);
void cycle_surface(Surface_Color surface[9]);

bool isOK(Surface_Color col[9]) {
    Surface_Color sc = col[0];
    for (int i = 1; i < 9; i++)
        if (sc != col[i])
            return false;
    return true;
}

bool is_solved(Cube *c) {
    if (isOK(c->u) && isOK(c->d) && isOK(c->f) && isOK(c->b) && isOK(c->r) && isOK(c->l))
        return true;
    return false;
}

void u_op(Cube *cb) {
    cycle_surface(cb->u);
    for (int i = 0; i < 3; i++)
        cycle((int *)&cb->f[i], (int *)&cb->l[i], (int *)&cb->b[i], (int *)&cb->r[i]);
}

void d_op(Cube *cb) {
    cycle_surface(cb->d);
    for (int i = 6; i < 9; i++)
        cycle((int *)&cb->f[i], (int *)&cb->r[i], (int *)&cb->b[i], (int *)&cb->l[i]);
}

void l_op(Cube *cb) {
    cycle_surface(cb->l);
    int n1[] = {0, 3, 6}, n2[] = {0, 3, 6}, n3[] = {0, 3, 6}, n4[] = {8, 5, 2};
    for (int i = 0; i < 3; i++)
        cycle((int *)&cb->u[n1[i]], (int *)&cb->f[n2[i]], (int *)&cb->d[n3[i]], (int *)&cb->b[n4[i]]);
}

void r_op(Cube *cb) {
    cycle_surface(cb->r);
    int n1[] = {2, 5, 8}, n2[] = {6, 3, 0}, n3[] = {2, 5, 8}, n4[] = {2, 5, 8};
    for (int i = 0; i < 3; i++)
        cycle((int *)&cb->u[n1[i]], (int *)&cb->b[n2[i]], (int *)&cb->d[n3[i]], (int *)&cb->f[n4[i]]);
}

void f_op(Cube *cb) {
    cycle_surface(cb->f);
    int n1[] = {6, 7, 8}, n2[] = {0, 3, 6}, n3[] = {2, 1, 0}, n4[] = {8, 5, 2};
    for (int i = 0; i < 3; i++)
        cycle((int *)&cb->u[n1[i]], (int *)&cb->r[n2[i]], (int *)&cb->d[n3[i]], (int *)&cb->l[n4[i]]);
}

void b_op(Cube *cb) {
    cycle_surface(cb->b);
    int n1[] = {2, 1, 0}, n2[] = {0, 3, 6}, n3[] = {6, 7, 8}, n4[] = {8, 5, 2};
    for (int i = 0; i < 3; i++)
        cycle((int *)&cb->u[n1[i]], (int *)&cb->l[n2[i]], (int *)&cb->d[n3[i]], (int *)&cb->r[n4[i]]);
}

void m_op(Cube *cb) {
    int n1[] = {1, 4, 7}, n2[] = {1, 4, 7}, n3[] = {1, 4, 7}, n4[] = {7, 4, 1};
    for (int i = 0; i < 3; i++)
        cycle((int *)&cb->u[n1[i]], (int *)&cb->f[n2[i]], (int *)&cb->d[n3[i]], (int *)&cb->b[n4[i]]);
}

void s_op(Cube *cb) {
    int n1[] = {3, 4, 5}, n2[] = {1, 4, 7}, n3[] = {5, 4, 3}, n4[] = {7, 4, 1};
    for (int i = 0; i < 3; i++)
        cycle((int *)&cb->u[n1[i]], (int *)&cb->r[n2[i]], (int *)&cb->d[n3[i]], (int *)&cb->l[n4[i]]);
}

void e_op(Cube *cb) {
    int n1[] = {3, 4, 5}, n2[] = {3, 4, 5}, n3[] = {3, 4, 5}, n4[] = {3, 4, 5};
    for (int i = 0; i < 3; i++)
        cycle((int *)&cb->f[n1[i]], (int *)&cb->r[n2[i]], (int *)&cb->b[n3[i]], (int *)&cb->l[n4[i]]);
}

void x_op(Cube *cb) {
    r_op(cb);
    for (int i = 0; i < 3; i++) {
        m_op(cb);
        l_op(cb);
    }
}
void y_op(Cube *cb) {
    u_op(cb);
    for (int i = 0; i < 3; i++) {
        e_op(cb);
        d_op(cb);
    }
}
void z_op(Cube *cb) {
    f_op(cb);
    s_op(cb);
    for (int i = 0; i < 3; i++)
        b_op(cb);
}

void cycle(int *a, int *b, int *c, int *d) {
    int temp = *a;
    *a = *d;
    *d = *c;
    *c = *b;
    *b = temp;
}

void cycle_surface(Surface_Color s[9]) {
    cycle((int *)&s[0], (int *)&s[2], (int *)&s[8], (int *)&s[6]);
    cycle((int *)&s[1], (int *)&s[5], (int *)&s[7], (int *)&s[3]);
}

bool move_cube(char input, Cube *cube) {
    switch (input) {
    case 'u':
        list_add_back(&cube->moves, 'U');
        u_op(cube);
        break;
    case 'U':
        list_add_back(&cube->moves, 'U');
        list_add_back(&cube->moves, '\'');
        for (int i = 0; i < 3; i++)
            u_op(cube);
        break;

    case 'd':
        list_add_back(&cube->moves, 'D');
        d_op(cube);
        break;
    case 'D':
        list_add_back(&cube->moves, 'D');
        list_add_back(&cube->moves, '\'');
        for (int i = 0; i < 3; i++)
            d_op(cube);
        break;

    case 'f':
        list_add_back(&cube->moves, 'F');
        f_op(cube);
        break;
    case 'F':
        list_add_back(&cube->moves, 'F');
        list_add_back(&cube->moves, '\'');
        for (int i = 0; i < 3; i++)
            f_op(cube);
        break;

    case 'b':
        list_add_back(&cube->moves, 'B');
        b_op(cube);
        break;
    case 'B':
        list_add_back(&cube->moves, 'B');
        list_add_back(&cube->moves, '\'');
        for (int i = 0; i < 3; i++)
            b_op(cube);
        break;

    case 'l':
        list_add_back(&cube->moves, 'L');
        l_op(cube);
        break;
    case 'L':
        list_add_back(&cube->moves, 'L');
        list_add_back(&cube->moves, '\'');
        for (int i = 0; i < 3; i++)
            l_op(cube);
        break;

    case 'r':
        list_add_back(&cube->moves, 'R');
        r_op(cube);
        break;
    case 'R':
        list_add_back(&cube->moves, 'R');
        list_add_back(&cube->moves, '\'');
        for (int i = 0; i < 3; i++)
            r_op(cube);
        break;

    case 'm':
        list_add_back(&cube->moves, 'M');
        m_op(cube);
        break;
    case 'M':
        list_add_back(&cube->moves, 'M');
        list_add_back(&cube->moves, '\'');
        for (int i = 0; i < 3; i++)
            m_op(cube);
        break;

    case 's':
        list_add_back(&cube->moves, 'S');
        s_op(cube);
        break;
    case 'S':
        list_add_back(&cube->moves, 'S');
        list_add_back(&cube->moves, '\'');
        for (int i = 0; i < 3; i++)
            s_op(cube);
        break;

    case 'e':
        list_add_back(&cube->moves, 'E');
        e_op(cube);
        break;
    case 'E':
        list_add_back(&cube->moves, 'E');
        list_add_back(&cube->moves, '\'');
        for (int i = 0; i < 3; i++)
            e_op(cube);
        break;

    case 'x':
        list_add_back(&cube->moves, 'x');
        x_op(cube);
        break;
    case 'X':
        list_add_back(&cube->moves, 'x');
        list_add_back(&cube->moves, '\'');
        for (int i = 0; i < 3; i++)
            x_op(cube);
        break;

    case 'y':
        list_add_back(&cube->moves, 'y');
        y_op(cube);
        break;
    case 'Y':
        list_add_back(&cube->moves, 'y');
        list_add_back(&cube->moves, '\'');
        for (int i = 0; i < 3; i++)
            y_op(cube);
        break;

    case 'z':
        list_add_back(&cube->moves, 'z');
        z_op(cube);
        break;
    case 'Z':
        list_add_back(&cube->moves, 'z');
        list_add_back(&cube->moves, '\'');
        for (int i = 0; i < 3; i++)
            z_op(cube);
        break;

    default:
        return false;
    }
    return true;
}

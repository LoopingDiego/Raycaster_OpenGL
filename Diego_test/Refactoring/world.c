#include "maze.h"
/*===================*/
/* mapping           */
/*===================*/
int map_x = 8;
int map_y = 8;
int block_size = 64;
int map[] =
{
1, 1, 1, 1, 1, 1, 1, 1,
1, 0, 0, 0, 0, 0, 0, 1,
1, 0, 1, 0, 0, 0, 0, 1,
1, 0, 1, 0, 0, 0, 0, 1,
1, 1, 0, 0, 0, 0, 0, 1,
1, 0, 0, 0, 0, 1, 0, 1,
1, 0, 0, 0, 0, 0, 0, 1,
1, 1, 1, 1, 1, 1, 1, 1,
};

/**
 * draw_MAP2D - draws the map
 */
void draw_map2D()
{
    int x_init, y_init;
    int x_final, y_final;

    for (y_init = 0; y_init < map_y; y_init++)
    {
        for (x_init = 0; x_init < map_x; x_init++)
        {
            if (map[y_init * map_x + x_init] == 1)
                glColor3f(0, 0, 1);
            else
                glColor3f(0, 0, 0);
        x_final = x_init * block_size;
        y_final = y_init * block_size;
        glBegin(GL_QUADS);
        glVertex2i(x_final + 1, y_final + 1);
        glVertex2i(x_final + 1, y_final + block_size - 1);
        glVertex2i(x_final + block_size - 1, y_final + block_size - 1);
        glVertex2i(x_final + block_size - 1, y_final + 1);
        glEnd();
        }
    }
}

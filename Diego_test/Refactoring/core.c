#include "maze.h"
/**
 * window_init - init window
 */

void window_init()
{    
    player.x = 300;
    player.y = 300;
    player.dx = cos(player.angle) * 5;
    player.dy = sin(player.angle) * 5;

    glClearColor(0.3, 0.3, 0.3, 0.3);
    gluOrtho2D(0, 1024, 512, 0);
}

/**
 * display - init window
 */
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw_map2D();
    draw_rays();
    draw_player();
    glutSwapBuffers();
}

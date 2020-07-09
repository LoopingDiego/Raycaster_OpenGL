#include "maze.h"
/**
 * draw_player - Draws player & look point
 */

void draw_player()
{
    player.x = 300;
    player.y = 300;
    player.dx = cos(player.angle) * 5;
    player.dy = sin(player.angle) * 5;

    glColor3f(0, 1, 0);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(player.x, player.y);
    glEnd();

    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(player.x, player.y);
    glVertex2i(player.x + player.dx * 5, player.y + player.dy * 5);
    glEnd();
}
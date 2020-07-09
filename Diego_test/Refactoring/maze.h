#ifndef _MAZE_H_
#define _MAZE_H_
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
/*-constants-----*/
#define PI 3.1415926535
#define PI_90 PI/2
#define PI_270 3*PI/2
#define WIDTH 1024
#define HEIGHT 512
#define DR 0.0174533

/*-player_struct--*/
typedef struct {
    float angle;
    float x;
    float y;
    float dx;
    float dy;
} Player;
Player player;
/*-functions-----*/
void window_init();
void display();
void draw_map2D();
void draw_player();
void buttons(unsigned char key, int x, int y);
float dist(float ax, float ay, float bx, float by, float ang);
void draw_rays();
#endif /* _MAZE_H_*/
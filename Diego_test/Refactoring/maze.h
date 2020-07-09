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
typedef struct entity {
    float angle;
    float x;
    float y;
    float dx;
    float dy;
} Player;
extern Player player;
/*-functions-----*/
void window_init();
void display();
void draw_player();

#endif /* _MAZE_H_*/
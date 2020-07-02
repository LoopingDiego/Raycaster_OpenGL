#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#define PI 3.1415926535
#define PI_90 PI/2
#define PI_270 3*PI/2
#define WIDTH 1024
#define HEIGHT 512
#define DR 0.0174533

float player_x, player_y, pdelta_x, pdelta_y, pangle; /* player's position */

void draw_player()
{
    glColor3f(0, 1, 0);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(player_x, player_y);
    glEnd();

    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(player_x, player_y);
    glVertex2i(player_x + pdelta_x * 5, player_y + pdelta_y * 5);
    glEnd();
}

void buttons(unsigned char key, int x, int y)
{
    if (key == 'a')
    {
        pangle -= 0.1;
        if (pangle < 0)
        {
            pangle += 2 * PI;
        }
        pdelta_x = cos(pangle) * 5;
        pdelta_y = sin(pangle) * 5;
    }
    if (key == 'd')
        {
        pangle += 0.1;
        if (pangle > 2 * PI)
        {
            pangle -= 2 * PI;
        }
        pdelta_x = cos(pangle) * 5;
        pdelta_y = sin(pangle) * 5;
    }
    if (key == 'w')
    {
        player_x += pdelta_x;
        player_y += pdelta_y;
    }
    if (key == 's')
    {
        player_x -= pdelta_x;
        player_y -= pdelta_y;
    }
    glutPostRedisplay();
}

/*===================*/
/* mapping           */
/*===================*/
int map_x = 8;
int map_y = 8;
int map_unit_size = 64;
int map[] =
{
1, 1, 1, 1, 1, 1, 1, 1,
1, 0, 0, 0, 0, 0, 0, 1,
1, 0, 1, 0, 0, 0, 0, 1,
1, 0, 0, 0, 0, 0, 0, 1,
1, 0, 0, 0, 0, 0, 0, 1,
1, 0, 0, 0, 0, 1, 0, 1,
1, 0, 0, 0, 0, 0, 0, 1,
1, 1, 1, 1, 1, 1, 1, 1,
};

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
        x_final = x_init * map_unit_size;
        y_final = y_init * map_unit_size;
        glBegin(GL_QUADS);
        glVertex2i(x_final + 1, y_final + 1);
        glVertex2i(x_final + 1, y_final + map_unit_size - 1);
        glVertex2i(x_final + map_unit_size - 1, y_final + map_unit_size - 1);
        glVertex2i(x_final + map_unit_size - 1, y_final + 1);
        glEnd();
        }
    }
}

float dist(float ax, float ay, float bx, float by, float ang)
{
    return ( sqrt((bx-ax) * (bx-ax) + (by-ay) * (by-ay)) ); /*pythagorean theorem */
}
void draw_rays()
{
    int ray, mx, my, mp, ray_lenght;
    float ray_x , ray_y, r_angle, x_offset, y_offset;

    r_angle = pangle - DR * 30;
    if(r_angle < 0)
    {
        r_angle += 2 * PI;
    }
    if (r_angle > 2 * PI)
    {
        r_angle -= 2 * PI;
    }
    for (ray = 0; ray < 360; ray++)
    {
        /*--horizontal lines--*/
        ray_lenght = 0;
        float disH = 1000000, hx = player_x, hy = player_y;
        float aTan = -1/tan(r_angle);
        if (r_angle > PI) /* look up */
        {
            ray_y = (((int)player_y >> 6)<< 6)-0.0001;
            ray_x = (player_y - ray_y) * aTan + player_x;
            y_offset = -64;
            x_offset = -y_offset * aTan;
        }
        if (r_angle < PI) /* look down */
        {
            ray_y = (((int)player_y >> 6)<< 6)+ 64;
            ray_x = (player_y - ray_y) * aTan + player_x;
            y_offset = 64;
            x_offset = -y_offset * aTan;
        }
        if (r_angle == 0 ||  r_angle == PI) /* look straight left or right */
        {
            ray_x = player_x;
            ray_y = player_y;
            ray_lenght = 8;
        }
        while (ray_lenght < 8)
        {
            mx = (int)(ray_x) >> 6;
            my = (int) (ray_y) >> 6;
            mp = my*map_x+mx;
            if (mp > 0 && mp < map_x * map_y && map[mp] == 1) /* wall collision*/
            {
                hx = ray_x;
                hy = ray_y;
                disH = dist(player_x, player_y, hx, hy, r_angle);
                ray_lenght = 8;
            }
            else
            {
                ray_x += x_offset;
                ray_y += y_offset;
                ray_lenght += 1;
            }
                        
        }
        /*--vertical lines--*/
        ray_lenght = 0;
        float disV = 1000000, vx = player_x, vy = player_y;
        float nTan = -tan(r_angle);
        if (r_angle > PI_90 && r_angle < PI_270) /* look left */
        {
            ray_x = (((int)player_x >> 6)<< 6)-0.0001;
            ray_y = (player_x - ray_x) * nTan + player_y;
            x_offset = -64;
            y_offset = -x_offset * nTan;
        }
        if (r_angle < PI_90 || r_angle > PI_270) /* look right */
        {
            ray_x = (((int)player_x >> 6)<< 6)+ 64;
            ray_y = (player_x - ray_x) * nTan + player_y;
            x_offset = 64;
            y_offset = -x_offset * nTan;
        }
        if (r_angle == 0 ||  r_angle == PI) /* look straight up or down */
        {
            ray_x = player_x;
            ray_y = player_y;
            ray_lenght = 8;
        }
        while (ray_lenght < 8)
        {
            mx = (int)(ray_x) >> 6;
            my = (int) (ray_y) >> 6;
            mp = my*map_x+mx;
            if (mp > 0 && mp < map_x * map_y && map[mp] == 1) /* wall collision*/
            {
                vx = ray_x;
                vy = ray_y;
                disV = dist(player_x, player_y, vx, vy, r_angle);
                ray_lenght = 8;
            }
            else
            {
                ray_x += x_offset;
                ray_y += y_offset;
                ray_lenght += 1;
            }
                        
        }
        if (disV < disH)
        {
            ray_x = vx;
            ray_y = vy;
        }
        if (disH < disV)
        {
            ray_x = hx;
            ray_y = hy;
        }
        glColor3f(1, 1, 0);
        glLineWidth(1);
        glBegin(GL_LINES);
        glVertex2i(player_x,player_y);
        glVertex2i(ray_x, ray_y);
        glEnd();
        r_angle += DR;
        if(r_angle < 0)
        {
            r_angle += 2 * PI;
        }
        if (r_angle > 2 * PI)
        {
            r_angle -= 2 * PI;
        }
    }
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw_map2D();
    draw_rays();
    draw_player();
    glutSwapBuffers();
}

void init()
{
    player_x = 300;
    player_y = 300;
    pdelta_x = cos(pangle) * 5;
    pdelta_y = sin(pangle) * 5;
    
    glClearColor(0.3, 0.3, 0.3, 0.3);
    gluOrtho2D(0, 1024, 512, 0);
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("The Maze Game");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(buttons);
    glutMainLoop();
}
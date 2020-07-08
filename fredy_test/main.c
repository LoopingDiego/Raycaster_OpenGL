#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

#define M_PI_3 3 * M_PI_2
#define DR 0.0174533 /* Degree in radians */

float px, py, pdy, pdx, pa;
int mapX = 8, mapY = 8, mapS = 64;
int map[] =
    {
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 1, 0, 0, 0, 0, 1,
        1, 0, 1, 0, 0, 0, 0, 1,
        1, 0, 1, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 1, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
    };

void drawPlayer(void)
{
    glColor3f(1, 1, 0);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(px, py);
    glEnd();

    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(px, py);
    glVertex2i(px + pdx * 5, py + pdy * 5);
    glEnd();
}

void draw_map2D(void)
{
    int x, y, xo, yo;

    for (y = 0; y < mapY; y++)
        for (x = 0; x < mapX; x++)
        {
            if (map[y * mapX + x] == 1)
                glColor3f(1, 1, 1); /* Map walls color */
            else
                glColor3f(0, 0, 0); /* Map floor color */
            xo = x * mapS;
            yo = y * mapS;
            glBegin(GL_QUADS);
            glVertex2i(xo, yo);
            glVertex2i(xo, yo + mapS);
            glVertex2i(xo + mapS, yo + mapS);
            glVertex2i(xo + mapS, yo);
            glEnd();
        }
}

float dist(float ax, float ay, float bx, float by, float ang)
{
    (void) ang;
    return ( sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)) ); /*pythagorean theorem */
}

void drawRays(void)
{
    int r, mx, my, mp, dof;
    float rx, ry, ra, xo, yo, aTan, nTan, disH, hx, hy, disV, vx, vy, disT, lineH, lineO, ca;

    ra = pa - DR * 30;
    if (ra < 0)
        ra += 2 * M_PI;
    if (ra > 2 * M_PI)
        ra -= 2 * M_PI;
    for (r = 0; r < 60; r++)
    {
        /* Check horizontal lines */
        dof = 0;
        disH = 1000000;
        hx = px;
        hy = py;
        aTan = -1 / tan(ra);
        /* look up */
        if (ra > M_PI)
        {
            ry = (((int)py >> 6) << 6) - 0.0001;
            rx = (py - ry) * aTan + px;
            yo = -64;
            xo = -yo * aTan;
        }
        /* look down */
        if (ra < M_PI)
        {
            ry = (((int)py >> 6) << 6) + 64;
            rx = (py - ry) * aTan + px;
            yo = 64;
            xo = -yo * aTan;
        }
        /* Look straigh left or rigth */
        if (ra == 0 || ra == M_PI)
        {
            rx = px;
            ry = py;
            dof = 8;
        }
        while (dof < 8)
        {
            mx = (int) (rx) >> 6;
            my = (int) (ry) >> 6;
            mp = my * mapX + mx;
            /* If a wall is found */
            if (mp > 0 && mp < mapX * mapY && map[mp] > 0)
            {
                hx = rx;
                hy = ry;
                disH = dist(px, py, hx, hy, ra);
                dof = 8;
            }
            /* Look up next line */
            else
            {
                rx += xo;
                ry += yo;
                dof +=1;
            }
        }

        /* Check vertical lines */
        dof = 0;
        disV = 1000000;
        vx = px;
        vy = py;
        nTan = -tan(ra);
        /* look left */
        if (ra > M_PI_2 && ra < M_PI_3)
        {
            rx = (((int)px >> 6) << 6) - 0.0001;
            ry = (px - rx) * nTan + py;
            xo = -64;
            yo = -xo * nTan;
        }
        /* look right */
        if (ra < M_PI_2 || ra > M_PI_3)
        {
            rx = (((int)px >> 6) << 6) + 64;
            ry = (px - rx) * nTan + py;
            xo = 64;
            yo = -xo * nTan;
        }
        /* Look straigh up or down */
        if (ra == 0 || ra == M_PI)
        {
            rx = px;
            ry = py;
            dof = 8;
        }
        while (dof < 8)
        {
            mx = (int) (rx) >> 6;
            my = (int) (ry) >> 6;
            mp = my * mapX + mx;
            /* If a wall is found */
            if (mp > 0 && mp < mapX * mapY && map[mp] > 0)
            {
                vx = rx;
                vy = ry;
                disV = dist(px, py, vx, vy, ra);
                dof = 8;
            }
            /* Look up next line */
            else
            {
                rx += xo;
                ry += yo;
                dof +=1;
            }
        }
        /* Vertical wall hit */
        if (disV < disH)
        {
            rx = vx;
            ry = vy;
            disT = disV;
            glColor3f(0.9, 0, 1);
        }
        /* Horizontal wall hit */
        if (disV > disH)
        {
            rx = hx;
            ry = hy;
            disT = disH;
            glColor3f(0.7, 0, 1);
        }
        glLineWidth(3);
        glBegin(GL_LINES);
        glVertex2i(px, py);
        glVertex2i(rx, ry);
        glEnd();

        /* Draw 3D Walls */
        /* Fix fisheye */
        ca = pa - ra;
        if (ca < 0)
            ca += 2 * M_PI;
        if (ca > 2 * M_PI)
            ca -= 2 * M_PI;
        disT = disT * cos(ca);
        /* Line height */
        lineH = (mapS * 320) / disT;
        if (lineH > 320)
            lineH = 320;
        /* Line Offset */
        lineO = 160 - lineH / 2;
        glLineWidth(8);
        glBegin(GL_LINES);
        glVertex2i(r * 8 + 530, lineO);
        glVertex2i(r * 8 + 530, lineH + lineO);
        glEnd();

        ra += DR;
        if (ra < 0)
            ra += 2 * M_PI;
        if (ra > 2 * M_PI)
            ra -= 2 * M_PI;
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw_map2D();
    drawRays();
    drawPlayer();
    glutSwapBuffers();
}

void buttons(unsigned char key, int x, int y)
{
    (void) x;
    (void) y;
    if (key == 'a')
    {
        pa -= 0.1;
        if (pa < 0)
            pa += 2 * M_PI;
        pdx = cos(pa) * 5;
        pdy = sin(pa) * 5;
    }
    if (key == 'd')
    {
        pa += 0.1;
        if (pa > 2 * M_PI)
            pa -= 2 * M_PI;
        pdx = cos(pa) * 5;
        pdy = sin(pa) * 5;
    }
    if (key == 'w')
    {
        px += pdx;
        py += pdy;
    }
    if (key == 's')
    {
        px -= pdx;
        py -= pdy;
    }
    glutPostRedisplay();
}

void init(void)
{
    glClearColor(0.3, 0.3, 0.3, 0);
    gluOrtho2D(0, 1024, 512, 0);
    px = 300; py = 300; pdx = cos(pa) * 5; pdy = sin(pa) * 5;
}

int main(int ac, char **av)
{
    glutInit(&ac, av);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1024, 512);
    glutCreateWindow("VIDEO TEST");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(buttons);
    glutMainLoop();
}

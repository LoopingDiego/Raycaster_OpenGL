#include "maze.h"
/**
 * dist - return hypothenusen
 * return: hipothenusen
 */
float dist(float ax, float ay, float bx, float by, float ang)
{
    return ( sqrt((bx-ax) * (bx-ax) + (by-ay) * (by-ay)) ); /*pythagorean theorem */
}
/**
 * draw_rays - implements ray casting
 */

void draw_rays()
{
    int ray, mx, my, mp, depth_field;
    float ray_x , ray_y, r_angle, x_offset, y_offset, disT;

    r_angle = player.angle - DR * 30;
    if(r_angle < 0)
    {
        r_angle += 2 * PI;
    }
    if (r_angle > 2 * PI)
    {
        r_angle -= 2 * PI;
    }
    for (ray = 0; ray < 60; ray++)
    {
        /*--horizontal lines--*/
        depth_field = 0;
        float disH = 1000000, hx = player.x, hy = player.y;
        float aTan = -1/tan(r_angle);
        if (r_angle > PI) /* look up */
        {
            ray_y = (((int)player.y >> 6)<< 6)-0.0001;
            ray_x = (player.y - ray_y) * aTan + player.x;
            y_offset = -64;
            x_offset = -y_offset * aTan;
        }
        if (r_angle < PI) /* look down */
        {
            ray_y = (((int)player.y >> 6)<< 6)+ 64;
            ray_x = (player.y - ray_y) * aTan + player.x;
            y_offset = 64;
            x_offset = -y_offset * aTan;
        }
        if (r_angle == 0 ||  r_angle == PI) /* look straight left or right */
        {
            ray_x = player.x;
            ray_y = player.y;
            depth_field = 8;
        }
        while (depth_field < 8)
        {
            mx = (int)(ray_x) >> 6;
            my = (int) (ray_y) >> 6;
            mp = my*map_x+mx;
            if (mp > 0 && mp < map_x * map_y && map[mp] == 1) /* wall collision*/
            {
                hx = ray_x;
                hy = ray_y;
                disH = dist(player.x, player.y, hx, hy, r_angle);
                depth_field = 8;
            }
            else
            {
                ray_x += x_offset;
                ray_y += y_offset;
                depth_field += 1;
            }
                        
        }
        /*--vertical lines--*/
        depth_field = 0;
        float disV = 1000000, vx = player.x, vy = player.y;
        float nTan = -tan(r_angle);
        if (r_angle > PI_90 && r_angle < PI_270) /* look left */
        {
            ray_x = (((int)player.x >> 6)<< 6)-0.0001;
            ray_y = (player.x - ray_x) * nTan + player.y;
            x_offset = -64;
            y_offset = -x_offset * nTan;
        }
        if (r_angle < PI_90 || r_angle > PI_270) /* look right */
        {
            ray_x = (((int)player.x >> 6)<< 6)+ 64;
            ray_y = (player.x - ray_x) * nTan + player.y;
            x_offset = 64;
            y_offset = -x_offset * nTan;
        }
        if (r_angle == 0 ||  r_angle == PI) /* look straight up or down */
        {
            ray_x = player.x;
            ray_y = player.y;
            depth_field = 8;
        }
        while (depth_field < 8)
        {
            mx = (int)(ray_x) >> 6;
            my = (int) (ray_y) >> 6;
            mp = my*map_x+mx;
            if (mp > 0 && mp < map_x * map_y && map[mp] == 1) /* wall collision*/
            {
                vx = ray_x;
                vy = ray_y;
                disV = dist(player.x, player.y, vx, vy, r_angle);
                depth_field = 8;
            }
            else
            {
                ray_x += x_offset;
                ray_y += y_offset;
                depth_field += 1;
            }
                        
        }
        if (disV < disH)
        {
            ray_x = vx;
            ray_y = vy;
            disT = disV;
            glColor3f(1, 1, 0);
        }
        if (disH < disV)
        {
            ray_x = hx;
            ray_y = hy;
            disT = disH;
            glColor3f(1, 1, 0.5);
        }
        glLineWidth(2);
        glBegin(GL_LINES);
        glVertex2i(player.x,player.y);
        glVertex2i(ray_x, ray_y);
        glEnd();
        /*---3D walls----*/
        float correction = player.angle - r_angle;
        if(r_angle < 0)
        {
            correction += 2 * PI;
        }
        if (correction> 2 * PI)
        {
            correction -= 2 * PI;
        }
        disT=disT*cos(correction);
        float lineH = (block_size * 320)/disT;
        if (lineH > 320)
        {
            lineH = 320;
        }
        
        float lineO = 160 - lineH/2;
        glLineWidth(9);
        glBegin(GL_LINES);
        glVertex2i(ray*7+530, lineO);
        glVertex2i(ray*7+530,lineH+lineO);
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
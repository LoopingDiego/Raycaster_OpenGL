#include "maze.h"
/**
 * main -maze project executable
 * @argc: argument counter
 * @argv: arguments
 */

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("The Maze Game");
	window_init();
    glutDisplayFunc(display);
//   glutKeyboardFunc(buttons);
	glutMainLoop();
}

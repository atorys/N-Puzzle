//
// Created by atory on 02.06.22.
//

#include<stdio.h>
#include<GL/glut.h>
#include<math.h>

int main(int ac, char **av) {

	glutInit(&ac, av);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(300, 300);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("test");
}
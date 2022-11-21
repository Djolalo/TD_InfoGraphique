#include <stdio.h>
#include <math.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "include/pointManaging.h"
#include "include/filling.h"

#if defined (_WIN32) || defined (WIN32)
#include <windows.h>
#endif

PointCloud points;

int height=500;
int width=500;
unsigned char lastKey;

void window_reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, 0 , height);
    glMatrixMode(GL_MODELVIEW);
}


void window_display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    if(points.tab_size>3){
        remplir(points);
    }
    glFlush();
}


void mouse_click(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON && state==GLUT_DOWN) {
        //Necessaire pour éviter tout y négatif
        y = -(y - (height));
        insererPoint(&points, x,y);
        glutPostRedisplay();
    }
}

void keyPressed (unsigned char key, int x, int y) {
    points.tab_size = 0;
}
int main(int argc, char** argv) {
    initPointCloud(&points);
    printf("Manuelle d'utilisation: trace des polygones de minimum 4 cotes. Il possible de continuer de tracer des points pour elargir le polygone.\n\
           \nAppuyer sur n'importe quel touche pour reinitialiser le polygone.");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(height, width);
    glutCreateWindow("Fixed Rectangle");
    glutDisplayFunc(window_display);
    glutReshapeFunc(window_reshape);
    glutKeyboardFunc(keyPressed);
    glutMouseFunc(mouse_click);
    glutMainLoop();
    return 0;
}
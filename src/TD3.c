#include <stdio.h>
#include <math.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "include/trace.h"
#include "include/clipping.h"
#include "include/pointManaging.h"

#if defined (_WIN32) || defined (WIN32)
#include <windows.h>
#endif

PointCloud nuage;

int height = 500;
int width = 500;
int click=0;
unsigned char lastKey;

void window_reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width/2, width/2,-height/2, height/2, -1.0 , 1.0);
    glMatrixMode(GL_MODELVIEW);
}


void window_display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    for(int i=0; i < nuage.tab_size && nuage.tab_size >=i; i+=2){
        bresenhamGeneral(-50,50,50,50);
        bresenhamGeneral(-50,-50,50,-50);
        bresenhamGeneral(50,50,50,-50);
        bresenhamGeneral(-50,50,-50,-50);
        if(nuage.tab_size>=i+2)
            cohen_sutherland(nuage.tabPos[i][0], nuage.tabPos[i][1], nuage.tabPos[i+1][0], nuage.tabPos[i+1][1], -50,-50,50,50,1);
    }
    glFlush();
}

void mouse_click(int button, int state, int x, int y){
    float x2= x-width/2;
    float y2= -(y-height/2); 
    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN) {
        insererPoint(&nuage, x2, y2);
        click++;
    }
    if(click%2==0)
            glutPostRedisplay();
}

int main(int argc, char** argv) {
    initPointCloud(&nuage);
    glutInit (&argc , argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE );
    glutInitWindowSize (height , width) ;
    glutCreateWindow("Fixed Rectangle") ;
    glColor3f(1.0, 1.0, 1.0);
    glutDisplayFunc(window_display);
    glutReshapeFunc(window_reshape);
    glutMouseFunc(mouse_click);
    glutMainLoop();
    return 0 ;
}
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include "include/pointManaging.h"
#include "include/geometry.h"
#if defined (_WIN32) || defined (WIN32)
#include <windows.h>
#endif

PointCloud nuage;
PointCloud copie;
PointCloud translater;

int height = 500;
int width = 500;
int click=0;
unsigned char lastKey='a';

void window_reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width/2, width/2, -height/2, height/2, -250.0 , 250.0);
    glMatrixMode(GL_MODELVIEW);
}

void render_scene() {
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    for(int i=0; i<nuage.tab_size;i++){
        glVertex2d(nuage.tabPos[i][0], nuage.tabPos[i][1]);
    }
    glEnd();
}

void window_display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    render_scene();
    glFlush();
}
void mouse_click(int button, int state, int x, int y){
    float x2= x-width/2;
    float y2= -(y-height/2); 
    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN) {
        if((lastKey=='m')||(lastKey=='r')!=(lastKey=='s')){
            insererPoint(&translater,x2,y2);
            click++;
        }
        else{
            insererPoint(&nuage, x2, y2);
            click++;
        }
    }
    if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
       switch (lastKey)
       {
       case 'm':
        insererPoint(&translater,x2,y2);
        translaterPolygone(&nuage, translater.tabPos[0][translater.tab_size-2]-translater.tabPos[0][translater.tab_size-1],translater.tabPos[1][translater.tab_size-2]-translater.tabPos[0][translater.tab_size-1]);
        click++;
        break;
       
        case 's':
        insererPoint(&translater,x2,y2);
        double xfactor= translater.tabPos[0][translater.tab_size-1]/translater.tabPos[0][translater.tab_size-2];
        double yfactor= translater.tabPos[1][translater.tab_size-1]/translater.tabPos[1][translater.tab_size-2];
        scalePolygone(&nuage,xfactor,yfactor);
        click++;
        break;

        case 'r':
        insererPoint(&translater,x2,y2);
        double norme=sqrt(pow(translater.tabPos[1][translater.tab_size-2]-translater.tabPos[1][translater.tab_size-1],2)+pow(translater.tabPos[0][translater.tab_size-2]-translater.tabPos[0][translater.tab_size-1],2));
        double cos=(translater.tabPos[0][translater.tab_size-2]-translater.tabPos[0][translater.tab_size-1])/norme;
        double sin=(translater.tabPos[1][translater.tab_size-2]-translater.tabPos[1][translater.tab_size-1])/norme; 
        rotatePolygone(&nuage, cos, sin);
        click++;
        break;
       } 
    }
    if(click>2){
        glutPostRedisplay();
    }
}

void keyboard_press(unsigned char key, int x, int y){
    lastKey=key;
}

int main(int argc, char** argv) {
    initPointCloud(&nuage);
    initPointCloud(&translater);
    glutInit (&argc , argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE );
    glutInitWindowSize (height , width) ;
    glutCreateWindow("Fixed Rectangle") ;
    glutDisplayFunc(window_display);
    glutReshapeFunc(window_reshape);
    glutMouseFunc(mouse_click);
    glutKeyboardFunc(keyboard_press);
    glutMainLoop();
    return 0 ;
}
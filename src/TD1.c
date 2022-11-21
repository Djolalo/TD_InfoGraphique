#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include  "include/pointManaging.h"
#define NBMAX 200
#if defined (_WIN32) || defined (WIN32)
#include <windows.h>
#endif


PointCloud nuage[NBMAX];
int i=0;
char lastKey='o';
void window_reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width/2, width/2, -height/2, height/2, -250.0 , 250.0);
    glMatrixMode(GL_MODELVIEW);
}

void render_scene() {
    glColor3f(1.0, 1.0, 1.0);
    if(lastKey=='p'){
        if(i==0){
            glBegin(GL_POLYGON);
            for(int j=0; j< nuage[i].tab_size; j++){
                glVertex2d(nuage[i].tabPos[j][0], nuage[i].tabPos[j][1]);
            }
            glEnd();
        }
        else if(nuage[i].tab_size>0){
            for(int z= 0;z<=i;z++){
                glBegin(GL_POLYGON);
                for(int j=0; j< nuage[z].tab_size; j++){
                glVertex2d(nuage[z].tabPos[j][0], nuage[z].tabPos[j][1]);
            }
            glEnd();
            }
        }
    }
    if(lastKey=='d'){
        if(i==0){
            glBegin(GL_LINES);
            for(int j=0; j< nuage[i].tab_size; j++){
                glVertex2d(nuage[i].tabPos[j][0], nuage[i].tabPos[j][1]);
            }
            glEnd();
        }
        else if(nuage[i].tab_size>0){
            for(int z= 0;z<=i;z++){
                glBegin(GL_LINES);
                for(int j=0; j< nuage[z].tab_size; j++){
                glVertex2d(nuage[z].tabPos[j][0], nuage[z].tabPos[j][1]);
            }
            glEnd();
            }
        }
    }
}

void window_display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    render_scene();
    glFlush();
}
void mouse_click(int button, int state, int x, int y){
    float x2= x-250;
    float y2= -(y-250);
    if(state==GLUT_DOWN && button ==GLUT_LEFT_BUTTON){
        insererPoint(&nuage[i], x2, y2);
    }
    else if(state==GLUT_DOWN && button ==GLUT_RIGHT_BUTTON){
        i++;
    }
    glutPostRedisplay();
}
/**
 * appuyer sur d permet de passer en mode traçage de droite, p traçage de polygones
 * appuyer sur c permet de remettre le compteur de polygones à zero.
*/
void keyPressed(unsigned char key, int x, int y){
    lastKey = key;
    if(key=='c'){
        i=0;
    }
}
int main(int argc, char** argv) {
    int height = 500;
    int width = 500;
    printf("Appuyer sur d permet de passer en mode traçage de droite, p traçage de polygones,appuyer sur c permet de remettre le compteur de polygones à zero.\n");
    for(int y=0; y<NBMAX;y++){
        initPointCloud(&nuage[y]);
    }
    glutInit (&argc , argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE );
    glutInitWindowSize (height , width) ;
    glutCreateWindow("Fixed Rectangle") ;
    glutDisplayFunc(window_display);
    glutReshapeFunc(window_reshape);
    glutKeyboardFunc(keyPressed);
    glutMouseFunc(mouse_click);
    glutMainLoop();
    return 0 ;
}
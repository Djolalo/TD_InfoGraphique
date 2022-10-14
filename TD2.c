#include <stdio.h>
#include <GL/glu.h>
#include <GL/glut.h>

#if defined (_WIN32) || defined (WIN32)
#include <windows.h>
#endif
#define MAX_POINTS_ON_FRAME 1000


typedef struct{
    GLfloat tabPos[MAX_POINTS_ON_FRAME][2];
    int tab_size;
}PointCloud;

PointCloud nuage;

int height = 500;
int width = 500;
int click=0;
int increments;
void initPointCloud (PointCloud *nuage){nuage->tab_size=0;}

void insererPoint(PointCloud *p, float x, float y){
    p->tabPos[p->tab_size][0]=x;
    p->tabPos[p->tab_size][1]=y;
    p->tab_size++;
}
void window_reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width/2, width/2,-height/2, height/2, -1.0 , 1.0);
    glMatrixMode(GL_MODELVIEW);
}
void draw_pixel(float x, float y){
    glBegin(GL_POINTS);
        glVertex2f(x,y);
    glEnd();
}

void bresenham(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2, int IncrY, int IncrX, float dx, float dy){
    float IncreE = 2*dy;
    float IncreNE= 2*(dy-dx);   
    float dp = 2*(dy -dx);
    float y = y1;
    for (float x=x1; x!=x2; x+=IncrX){
        (increments==1)?draw_pixel(x, y):draw_pixel(y,x);
        if(dp<=0){
            dp+=IncreE;
        }
        else{
            y+=IncrY;
            dp+=IncreNE;
        }
    }
}

void bresenhamGeneral(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2){
    float dy= y2-y1;
    float dx= x2-x1;
    float Incrx=(dx>0)? 1: -1;
    dx= (Incrx==-1)? -dx:dx;
    float Incry=(dy>0)? 1: -1;
    dy= (Incry==-1)? -dy:dy;
    (dx>=dy)? bresenham(x1,x2,y1,y2, Incry, Incrx, dx, dy), increments=1: bresenham(y1,y2,x1,x2, Incrx, Incry,dy, dx), increments=0;
}

void window_display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    for(int i=0; i < nuage.tab_size && nuage.tab_size >=i; i+=2){
        printf("%d %d\n Le trace se fera sur: %f\t%f\ten x, et %f\t%f\n", i, nuage.tab_size, nuage.tabPos[i][0], nuage.tabPos[i+1][0], nuage.tabPos[i][1], nuage.tabPos[i+1][1]);
        bresenhamGeneral(nuage.tabPos[i][0], nuage.tabPos[i+1][0], nuage.tabPos[i][1], nuage.tabPos[i+1][1]);
    }
    glFlush();
}
void mouse_click(int button, int state, int x, int y){
    float x2= x-250;
    float y2= -(y-250); 
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
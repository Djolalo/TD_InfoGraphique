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

void bresenham(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2, int IncrX,int IncrY, float dx, float dy, int inversion){
    float IncreE = 2*dy;
    float IncreNE= 2*(dy-dx);   
    float dp = 2*(dy -dx);
    float y = y1;
    for (float x=x1; x!=x2; x+=IncrX){
        (inversion==1)?draw_pixel(x, y) :draw_pixel(y,x);
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
    float Incry, Incrx;
    if(dx>0){
        Incrx= 1;
    }
    else{
        Incrx=-1;
        dx=-dx;
    }
    if(dy>0){
        Incry= 1;
    }
    else{
        dy=-dy;
        Incry=-1;
    }
    if(dx>=dy){
        bresenham(x1,x2,y1,y2,Incrx,Incry, dx, dy, 1);
    }    
    else{

        bresenham(y1,y2,x1,x2,Incry,Incrx,dy, dx, 0);
    }
}

void  draw_Circle(float x, float y){
    draw_pixel(x,y);
    draw_pixel(x,-y);
    draw_pixel(-x,y);
    draw_pixel(-x,-y);
    draw_pixel(y,x);
    draw_pixel(y,-x);
    draw_pixel(-y,x);
    draw_pixel(-y,-x);
}

void PointMilieuCercle(float r){
float x,y,d;
    x=0;
    y=r;
    d= 1.25-r;
    draw_pixel(x,y);
    draw_pixel(x,-y);
    while(y>x){
        if(d<0)
            d+=(2*x)+3;
        else{
            d+=(2*x)-(2*y)+5;
            y--;
        }
        x++;
        draw_Circle(x,y);
    }
}

void window_display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    for(int i=0; i < nuage.tab_size && nuage.tab_size >=i; i+=2){
        if(nuage.tab_size>=i+2)
            bresenhamGeneral(nuage.tabPos[i][0], nuage.tabPos[i+1][0], nuage.tabPos[i][1], nuage.tabPos[i+1][1]);
    }
    PointMilieuCercle(50);
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
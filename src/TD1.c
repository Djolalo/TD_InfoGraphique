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
    glOrtho(-width/2, width/2, -height/2, height/2, -250.0 , 250.0);
    glMatrixMode(GL_MODELVIEW);
}

void render_scene() {
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
        /*glVertex2d(-128, -128);
        glVertex2d(128, -128);
        glVertex2d(128, 128);
        glVertex2d(-128, 128);
    */
   for(int i=0; i< nuage.tab_size; i++){
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
    float x2= x-250;
    float y2= -(y-250);
    insererPoint(&nuage, x2, y2);
    glutPostRedisplay();
}
int main(int argc, char** argv) {
    int height = 500;
    int width = 500;
    initPointCloud(&nuage);
    glutInit (&argc , argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE );
    glutInitWindowSize (height , width) ;
    glutCreateWindow("Fixed Rectangle") ;
    glutDisplayFunc(window_display);
    glutReshapeFunc(window_reshape);
    glutMouseFunc(mouse_click);
    glutMainLoop();
    return 0 ;
}
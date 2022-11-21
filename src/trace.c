#include "include/trace.h"

void draw_pixel(float x, float y) {
    glBegin(GL_POINTS);
        glVertex2f(x, y);
    glEnd();
}

void bresenham(float x1, float x2, float y1, float y2, int IncrX,int IncrY, float dx, float dy, int inversion){
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

void bresenhamGeneral(float x1, float x2, float y1, float y2){
    /*
    On ne garde que la partie  entière des coordonées, pour éviter tout problèmme dans la bouclé incrémentale.
    */
    x1 = floorf(x1);
    x2 = floorf(x2);
    y1 = floorf(y1);
    y2 = floorf(y2);
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


#include "include/pointManaging.h"
#include "include/geometry.h"

void translaterPolygone(PointCloud *nuage, float dx, float dy){
    for(int i=0;  i<nuage->tab_size; i++){
        nuage->tabPos[i][0]+=dx;
        nuage->tabPos[i][1]+=dy;
    }
}

void scalePolygone(PointCloud *nuage, float deltax, float deltay){
    for(int i=0;  i<nuage->tab_size; i++){
        nuage->tabPos[i][0]*=deltax;
        nuage->tabPos[i][1]*=deltay;
    }
}

void rotatePolygone(PointCloud *nuage, double cos, double sin){
    for(int i=0;  i<nuage->tab_size; i++){
        nuage->tabPos[i][0]=nuage->tabPos[i][0]*cos-nuage->tabPos[i][1]*sin;
        nuage->tabPos[i][1]=nuage->tabPos[i][0]*sin-nuage->tabPos[i][1]*cos;
    }
}
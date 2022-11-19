#include "include/pointManaging.h"



void initPointCloud (PointCloud *nuage){nuage->tab_size=0;}

void insererPoint(PointCloud *p, float x, float y){
    p->tabPos[p->tab_size][0]=x;
    p->tabPos[p->tab_size][1]=y;
    p->tab_size++;
}

void afficheNuage(PointCloud p){
    for(int i=0; i<p.tab_size;i++){
        printf("X= %f, Y=%f", p.tabPos[i][0],p.tabPos[i][1]);
    }
}
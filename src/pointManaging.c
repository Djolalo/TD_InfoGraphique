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
float iemeAbcisse(int i, PointCloud p){
    return (p.tabPos[i][0]);
}

float iemeOrdonnee(int i, PointCloud p){
    return p.tabPos[i][1];
}
int tabSize(PointCloud p) {
    return p.tab_size;
}
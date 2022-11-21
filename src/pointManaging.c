#include "include/pointManaging.h"

void initPointCloud (PointCloud *nuage){nuage->tab_size=0;}

void insererPoint(PointCloud *p, float x, float y){
    p->tabPos[p->tab_size][0]=x;
    p->tabPos[p->tab_size][1]=y;
    p->tab_size++;
}

void afficheNuage(PointCloud p){
    for(int i=0; i<p.tab_size;i++){
        printf("X= %f, Y=%f\n", p.tabPos[i][0],p.tabPos[i][1]);
    }
}
float iemeAbcisse(int i, PointCloud p){
    return (p.tabPos[i][0]);
}

float iemeOrdonnee(int i, PointCloud p){
    return p.tabPos[i][1];
}
int taille(PointCloud p){
    return p.tab_size;
}


int sizeTab(PointCloud p) {
    int i=0;
    for (int j=0; j<p.tab_size;j++){
        if(i<p.tabPos[j][1]){
            i=p.tabPos[j][1];
        }
    }
    return i;
}
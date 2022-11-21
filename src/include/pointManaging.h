#ifndef pointManaging
#define pointManaging
#include <stdio.h>
#define MAX_POINTS_ON_FRAME 1000
typedef struct {
    float tabPos[MAX_POINTS_ON_FRAME][2];
    int tab_size;
}PointCloud;
void initPointCloud (PointCloud *nuage);
void insererPoint(PointCloud *p, float x, float y);
void afficheNuage(PointCloud p);
float iemeAbcisse(int i, PointCloud p);
float iemeOrdonnee(int i, PointCloud p);
int taille(PointCloud p);
int sizeTab(PointCloud p);
#endif
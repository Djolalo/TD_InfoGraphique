#ifndef pointManaging
#define pointManaging

#define MAX_POINTS_ON_FRAME 1000
typedef struct {
    float tabPos[MAX_POINTS_ON_FRAME][2];
    int tab_size;
}PointCloud;
void initPointCloud (PointCloud *nuage);
void insererPoint(PointCloud *p, float x, float y);

#endif
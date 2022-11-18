#ifndef geometry
#define geometry

void translaterPolygone(PointCloud *nuage, float dx, float dy);
void scalePolygone(PointCloud *nuage, float deltax, float deltay);
void rotatePolygone(PointCloud *nuage, double cos, double sin);
#endif
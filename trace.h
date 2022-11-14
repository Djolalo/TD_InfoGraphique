#ifndef trace
#define trace

void draw_pixel(float x, float y);
void bresenham(float x1, float x2, float y1, float y2, int IncrX,int IncrY, float dx, float dy, int inversion);
void bresenhamGeneral(float x1, float x2, float y1, float y2);

#endif
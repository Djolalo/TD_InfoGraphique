#ifndef clipping
#define clipping

#include <stdbool.h>
#include <math.h>

int calcule_code(float x, float y, float xmin, float ymin, float xmax, float ymax);
void cohen_sutherland(float xa, float ya, float xb, float yb, float xmin, float ymin, float xmax, float ymax, float attribut);

#endif
#include "include/filling.h"

typedef struct {
    float Ymax;
    float Xmin;
    float invM;
}donnees;

typedef struct cote{
    donnees data;
    struct cote* suivant;
}*LCA;


#ifndef filling
#define filling
#include "trace.h"
#include "pointManaging.h"
typedef int bool;
#define FALSE 0;
#define TRUE 1;

/**
 * Primitives de base non-relatives à des structures de données
*/
int Max(int a, int b);
int Min(int a, int b);
/*
Primitives de base pour le segment
*/

typedef struct {
    float Xmin;
    float dm;
    float Ymax;
}segment;


float xMin(segment s);
float yMax(segment s);
float im(segment s);
void drawLine(float xa, float y, float xb);
/**
 * Primitives de base relatives pour notre liste
*/
typedef struct cote *Liste;
Liste initListe();
Liste allocMemRemp(segment s);
Liste suivant(Liste l);
segment donnee(Liste l);
bool estVide(Liste l);
void inserTete(segment s, Liste *l);
Liste dernier(Liste l);
void inserQueue(segment n, Liste *l);
void freeCell(Liste *l);
void suppIndiceListe(Liste *l, int y);
void freeListe(Liste *l);
void freeTab(Liste *tab, int taille);
void inserEltListeTriee(segment elt, Liste *l);
Liste incrementSegment(Liste l);
void inserEltListeTrieeLCA(segment elt, Liste *l);
void initTabListe(Liste *tab, int taille) ;
void drawLineListe(Liste l, int y);
/**
 * Primitives de base pour la structure SI
*/

void creerSIVIDE(Liste *tab,int taille);
void creatSI(Liste *tab, PointCloud p);
void remplir(PointCloud p);
#endif
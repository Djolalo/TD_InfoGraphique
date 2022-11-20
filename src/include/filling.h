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
int max(int a, int b);
int min(int a, int b);
/*
Primitives de base pour le segment
*/

typedef struct {
    float xMin;
    float im;
    float yMax;
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
void libererCellule(Liste *l);
void viderListe(Liste *l);
void viderTab(Liste *tab, int taille);
Liste determinerAiListe(segment s, Liste *l);
void inserEltListeTriee(segment elt, Liste *l);
void incrementSegment(Liste *l);

/**
 * Primitives de base pour la structure SI
*/
typedef struct{
    Liste *tab;
    int taille;
}SI;
void creerSIVIDE(Liste *tab,int taille);
void creatSI(Liste *tab, PointCloud p);
void remplir(PointCloud p);
#endif
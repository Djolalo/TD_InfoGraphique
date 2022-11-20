#include "include/filling.h"

typedef struct cote{
    segment donnee;
    struct cote* suivant;
}*Liste;

/**
 * Primitives de base non-relatives à des structures de données
*/

int max(int a, int b){
    return (a>b)?a:b;
}
int min(int a, int b){
    return (a>b)?a:b;
}

/*
Primitives de base pour le segment
*/

float xMin(segment s){
    return s.xMin;
}
float yMax(segment s){
    return s.yMax;
}
float im(segment s){
    return s.im;
}
void drawLine(float xa, float y, float xb){
    while (xa<xb){
        draw_pixel(xa,y);
        xa++;
    }
}
void drawListe(Liste l, int indice){
    segment a,b;
    int nbsegments = 0;
    while(!estVide(suivant(l))) {
        if(nbsegments%2 == 0) {
            a = donnee(l);
            b = donnee(suivant(l));
            drawLine(a.xMin, b.xMin, indice);
        }
        l = suivant(l);
        nbsegments++;
    }
}
/**
 * Primitives de base relatives pour notre liste
*/
Liste initListe(){
    return NULL;
}

Liste allocMemRemp(segment s){
    Liste ret=(Liste) malloc(sizeof(Liste));
    ret->donnee= s;
    ret->suivant= initListe();
    return ret;
}
Liste suivant(Liste l){
    return l->suivant;
}

segment donnee(Liste l){
    return l->donnee;
}
bool estVide(Liste l){
    return l==NULL;
}
void inserTete(segment s, Liste *l) {
    Liste cel;
    cel = (Liste)malloc(sizeof(Liste));
    cel->donnee = s;
    cel->suivant = *l;
    *l = cel;
}
Liste dernier(Liste l){
    while(!estVide(suivant(l))){
        l=suivant(l);
    }
    return l;
}
void inserQueue(segment n, Liste *l) {
    if(estVide(*l)) {
        inserTete(n, l);
    } else {
        Liste der = dernier(*l);
        inserTete(n, &(der->suivant));
    }
}
void libererCellule(Liste *l) {
    Liste ll;
    ll = *l;
    *l = suivant(*l);
    free(ll);
}
void libererIemeCellule(Liste *l,int i){
    if(!estVide(*l)) {
        if(yMax(donnee(*l)) == i) {
            libererCellule(l);
            if(!estVide(*l)) {
                libererIemeCellule(l, i);
            }
        } else {
            libererIemeCellule(&((*l)->suivant), i);
        }
    }
}
void viderListe(Liste *l){
    while (!estVide(*l)){
        libererCellule(l);
    }
}
void viderTab(Liste *tab, int taille) {
    for(int i = 0; i < taille; i++) {
        viderListe(&tab[i]);
    }
}
Liste determinerAiListe(segment s, Liste *l){
    if(estVide(*l)){
        return NULL;
    }
    Liste as=suivant(*l);
    while(!estVide(as)&&((donnee((*l)).xMin >=s.xMin))){
        if((donnee(*l)).xMin >=s.xMin&&(donnee(*l)).im>s.im)
            return *l;
        *l=as;
        as=suivant(*l);
    }
    return(*l);
}

void inserEltListeTriee(segment s, Liste *l) {

    Liste ai=determinerAiListe(s, l);
    inserTete(s, &ai); 
}
void incrementSegment(Liste *l) {
    segment seg;
    while(!estVide(*l)) {
        seg = donnee(*l);
        seg.xMin += im(seg);
        (*l)->donnee= seg;
        *l = suivant(*l);
    }
}

/**
 * Primitives de base pour la structure SI
*/
void creerSIVIDE(Liste *tab,int taille){
    for(int i=0; i<taille;i++){
        tab[i]=initListe();
    }
}
void creatSI(Liste *tab, PointCloud p) {
int xMin,Ymax,y;
Liste l;
segment s;
float xa,xb,ya,yb,dm,dy,dx;
    for(int i = 0; i < tabSize(p); i++) {
        if(i==(tabSize(p) - 1)) {
            xa = iemeAbcisse(i,p);
            ya = iemeOrdonnee(i,p);
            xb = iemeAbcisse(0,p);
            yb = iemeOrdonnee(0,p);
        } else {
            xa = iemeAbcisse(i,p);
            ya = iemeOrdonnee(i,p);
            xb = iemeAbcisse(i+1, p);
            yb = iemeOrdonnee(i+1, p);
        }
        dx = xb - xa;
        dy = yb - ya;
        if(dy != 0) {
            segment seg;
            y = min(ya, yb);
            l = tab[y];
            if(ya > yb) {
                xMin = xb;
            } else {
                xMin = xa;
            }
            dm = dx/dy;
            Ymax = max(ya, yb);
            seg.im = dm;
            seg.xMin = xMin;
            seg.yMax = Ymax;
            inserEltListeTriee(seg, &l);
            tab[y] = l;
        }
    }
}

void remplir(PointCloud p){
    Liste tab[10000];
    int n = p.tab_size;
    creerSIVIDE(tab, n);
    creatSI(tab, p);
    Liste LCA = initListe();
    Liste Ltemp = initListe();
    Liste l;
    for(int y = 0; y <= n; y++) {
        l = tab[y];
        while(!estVide(l)) {
            inserEltListeTriee(donnee(l), &LCA);
            l = suivant(l);
        }
        libererIemeCellule(&LCA, y);
        if(!estVide(LCA)) {
            Ltemp = LCA;
            drawListe(Ltemp, y);
        }
        Ltemp = LCA;
        incrementSegment(&Ltemp);
    }
    viderTab(tab, n);
    viderListe(&LCA);
}

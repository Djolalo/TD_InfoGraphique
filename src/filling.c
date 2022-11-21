#include "include/filling.h"
#include <math.h>


/**
 * Primitives de base non-relatives à des structures de données
*/
typedef struct cote {
    segment donnee;
    struct cote *suivant;
}*Liste;
int Max(int a, int b) {
    if(a > b) {
        return a;
    } else {
        return b;
    }
}

int Min(int a, int b) {
    if(a < b) {
        return a;
    } else {
        return b;
    }
}

/*
Prdmitives de base pour le segment
*/

float Xmin(segment s){
    return s.Xmin;
}
float yMax(segment s){
    return s.Ymax;
}
float dm(segment s){
    return s.dm;
}
void drawLine(float xa, float xb,float y){
    while (xa<xb){
        draw_pixel(xa,y);
        xa++;
    }
}
void drawLineListe(Liste l, int y) {
    segment a,b;
    int nbsegments = 0;
    while(!estVide(suivant(l))) {
        if(nbsegments%2 == 0) {
            a = donnee(l);
            b = donnee(suivant(l));
            drawLine(a.Xmin, b.Xmin,y);
        }
        l = suivant(l);
        nbsegments++;
    }
}
/**
 * Prdmitives de base relatives pour notre liste
*/

Liste initListe() {
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
void freeCell(Liste *l) {
    Liste ll;
    ll = *l;
    *l = suivant(*l);
    free(ll);
}
/**
 * Supprime de la liste tous les éléments à l'ordonnée max y
*/
void nettoyerIndiceListe(Liste *l, int y) {
    if(!estVide(*l)) {
        if((donnee(*l).Ymax) == y) {
            freeCell(l);
            if(!estVide(*l)) {
                nettoyerIndiceListe(l, y);
            }
        } else {
            nettoyerIndiceListe(&((*l)->suivant), y);
        }
    }
}
void freeListe(Liste *l) {
    while(!estVide(*l)) {
        freeCell(l);
    }
}

void freeTab(Liste *tab, int n) {
    for(int i = 0; i < n; i++) {
        freeListe(&tab[i]);
    }
}
/**
 * Insertion de l'élément en fonction de l'ordonnée la plus haute dans un tableau de liste
*/
void inserEltListeTriee(segment elt, Liste *l) {
    if(estVide(*l) || donnee(*l).Ymax > elt.Ymax) {
        inserTete(elt, l);
    } else {
        inserEltListeTriee(elt, &((*l)->suivant));
    }
}
/**
 * Déplace l'abcisse pour qu'il suive le segment qu'il devra tracer 
*/
Liste incrementSegment(Liste l) {
    Liste res=l;
    segment seg;
    while(!estVide(l)) {
        seg = donnee(l);
        seg.Xmin += dm(seg);
        l->donnee= seg;
        l = suivant(l);
    }
    return res;
}
/**
 * Insere l'élément en foncition de l'abcisse cette fois-ci.
 * Si la cellule (cote) questionnée à la même abcisse, on et là où l'inverse de la pente est plus grand.
*/
void inserEltListeTrieeLCA(segment elt, Liste *l) {

    if(estVide(*l) || ((donnee(*l).Xmin >= elt.Xmin))) {
        if(!estVide(*l) && (donnee(*l).Xmin == elt.Xmin) && (donnee(*l).dm <= elt.dm)) {
            inserEltListeTrieeLCA(elt, &((*l)->suivant));
        } else {
            inserTete(elt, l);
        }
    } else {
        inserEltListeTrieeLCA(elt, &((*l)->suivant));
    }
}

/**
 * Initialise un tableau de listes à l'aide de la taille en paramètre
 * @param: tab :(Liste *), taille:int 
*/
void initTabListe(Liste *tab, int taille) {
    for(int i=0; i<taille;i++){
        tab[i]=initListe();
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

/**
 * Crée le tableau de listes de segment, nécessaire à l'affichage qui viendra plus tard
*/
void creatSI(Liste *tab, PointCloud p) {
int Xmin,yMax,y;
Liste l;
segment s;
float xa,xb,ya,yb,dm,dy,dx;
    for(int i = 0; i < taille(p); i++) {
        if(i==(taille(p) - 1)) {
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
        /**
         * Le tableau n'a pas d'indice négatif
        */
        if(dy != 0) {
            y = Min(ya, yb);
            l = tab[y];
            if(ya > yb) {
                Xmin = xb;
            } else {
                Xmin = xa;
            }
            dm = dx/dy;
            yMax = Max(ya, yb);
            s.dm = dm;
            s.Xmin = Xmin;
            s.Ymax = yMax;
            inserEltListeTriee(s, &l);
            tab[y] = l;
        }
    }
}

void remplir(PointCloud p){
    Liste tab[10000];
    int indice= sizeTab(p);
    initTabListe(tab, indice);
    creatSI(tab, p);
    Liste LCA = initListe();
    Liste Ltemp = initListe();
    Liste l, tetelca;
    for(int y = 0; y <= indice; y++) {
        l = tab[y];
        while(!estVide(l)) {
            inserEltListeTrieeLCA(donnee(l), &LCA);
            l = suivant(l);
        }
        nettoyerIndiceListe(&LCA, y);
        if(!estVide(LCA)) {
            Ltemp = LCA;
            drawLineListe(Ltemp, y);
        }
        Ltemp = LCA;
        Ltemp =incrementSegment(Ltemp);
    }
    freeTab(tab, indice);
    freeListe(&LCA);
}

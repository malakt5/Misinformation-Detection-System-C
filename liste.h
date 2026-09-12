#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED
#include "ELTARTICLE.h"
typedef struct structNoeud{
    ELEMENT info;
    struct structNoeud* suivant;
}structNoeud,*NOEUD;
typedef struct{
    NOEUD tete;
    int lg;
}laStruct,*LISTE;
NOEUD noeudCreer(ELEMENT);
void noeudDetruire(NOEUD);
LISTE listeCreer();
void listeDetruire(LISTE);
int estVide(LISTE);
int estSaturee(LISTE);
int listeTaille(LISTE);
ELEMENT recuperer(LISTE, int);
int inserer(LISTE, ELEMENT,int);
int supprimer(LISTE, int);
void listeAfficher(LISTE);
LISTE listeCopier(LISTE);
int listeComparer(LISTE, LISTE);


#endif

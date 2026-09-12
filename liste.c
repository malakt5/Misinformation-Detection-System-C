#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liste.h"
NOEUD noeudCreer(ELEMENT e){
    NOEUD n;
    n =(NOEUD)malloc(sizeof(structNoeud));
    if(!n)
    printf ("\nPlus d'espace");
    else{
        elementAffecter(&n->info, e);
        n->suivant = NULL;
    }
    return n;
}
void noeudDetruire(NOEUD n){
    elementDetruire(n->info);
    free(n);
}
LISTE listeCreer(){
    LISTE L;
    L=(LISTE)malloc(sizeof(laStruct));
    if(!L) printf("\nProbleme de memoire");
    else{
        L->tete=NULL;
        L->lg=0;
    }
    return L;
}
void listeDetruire(LISTE L){
    int i;
    NOEUD p,q;
    q=L->tete;
    for(i=1;i<=L->lg;i++){
        p=q;
        q=q->suivant;
        noeudDetruire(p);
    }
    free(L);
}
int estVide(LISTE L){
    return(L->tete==NULL);
}
int estSaturee(LISTE L){
    int saturee=1;
    NOEUD temp;
    temp=(NOEUD)malloc(sizeof(structNoeud));
    if(temp!=NULL){
        saturee=0;
        free(temp);
    }
    return saturee;
}
int listeTaille(LISTE L){
    return(L->lg);
}
ELEMENT recuperer(LISTE L, int pos){
    ELEMENT elt = elementCreer();

    if(estVide(L))
        printf("\nListe vide");
    else if(pos < 1 || pos > L->lg)
        printf("\nPosition invalide");
    else{
        NOEUD p = L->tete;
        int i;

        for(i = 1; i < pos; i++)p = p->suivant;

    elt = p->info;
    }

return elt;
}
int inserer(LISTE L, ELEMENT e,int pos){
    int i,succes=1;
    NOEUD n,p,q;
    if (estSaturee(L)){
        printf ("\nListe saturée");
        succes=0;
    }
    else{
        if ((pos < 1) || (pos > L->lg + 1)) {
            printf ("\nPosition invalide");
            succes=0;
        }
        else{
          n=noeudCreer(e);
          if(pos==1){
            n->suivant=L->tete;
            L->tete=n;
          }
          else{
            q=L->tete;
            for(i=1;i<pos;i++){
                p=q;
                q=q->suivant;
            }
            p->suivant=n;
            n->suivant=q;
          }
        (L->lg)++;
        }
    }
    return succes;
}
int supprimer(LISTE L, int pos){
    int i,succes=1;
    NOEUD p,q;
    if (estVide(L)){
        printf ("\nListe vide");
        succes=0;
    }
    else{
        if ((pos < 1) || (pos > L->lg )) {
            printf ("\nPosition invalide");
            succes=0;
        }
        else{
          q=L->tete;
          if(pos==1){
            L->tete=L->tete->suivant;
          }
          else{
            for(i=1;i<pos;i++){
                p=q;
                q=q->suivant;
            }
            p->suivant=q->suivant;
          }
          free(q);
          L->lg--;
        }
    }
    return succes;
}
void listeAfficher(LISTE L){
    NOEUD p;
    int i;
    p=L->tete;
    for(i=1;i<=L->lg;i++){
        elementAfficher(p->info);
        p=p->suivant;
    }

}
LISTE listeCopier(LISTE L){
    ELEMENT elt;
    int i;
    LISTE LR=listeCreer();
    for(i=1;i<=L->lg;i++){
        elt=elementCreer();
        elementCopier(&elt,recuperer(L,i));
        inserer(LR,elt,listeTaille(LR)+1);
    }
    return LR;
}
int listeComparer(LISTE L1, LISTE L2){
    int i=1,test=1;
    if(listeTaille(L1)!=listeTaille(L2)) test=0;
    else{
        while(i<=listeTaille(L1)&&test){
            if(elementComparer(recuperer(L1,i),recuperer(L2,i))!=0) test=0;
            else i++;
        }
    }
    return test;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ELTARTICLE.H"
ELEMENT elementCreer(){
    ELEMENT e=(ELEMENT)malloc(sizeof(articleStruct));
    if(e==NULL){
        printf("\nProbleme de memoire!");
    }
    e->id=0;
    strcpy(e->titre,"");
    strcpy(e->source,"");
    e->score_fiabilite=0;
    e->jour=0;
    e->mois=0;
    e->annee=0;
    e->heure=0;
    e->minute=0;
    return e;
}
void elementLire(ELEMENT *e){
    getchar();
    printf("titre: ");
    fgets((*e)->titre, 100, stdin);
    (*e)->titre[strcspn((*e)->titre, "\n")] = '\0';

    printf("source: ");
    fgets((*e)->source, 100, stdin);
    (*e)->source[strcspn((*e)->source, "\n")] = '\0';

    printf("score de fiabilite: ");
    scanf("%d", &((*e)->score_fiabilite));

    printf("jour: ");
    scanf("%d", &((*e)->jour));

    printf("mois: ");
    scanf("%d", &((*e)->mois));

    printf("annee: ");
    scanf("%d", &((*e)->annee));

    printf("heure: ");
    scanf("%d", &((*e)->heure));

    printf("minute: ");
    scanf("%d", &((*e)->minute));

    getchar();
}
void elementAfficher(ELEMENT e){
    if(e != NULL){
        printf("ID: %d\n", e->id);
        printf("Titre: %s\n", e->titre);
        printf("Source: %s\n", e->source);
        printf("Jour: %d\n", e->jour);
        printf("Mois: %d\n", e->mois);
        printf("Annee: %d\n", e->annee);
        printf("Heure: %d\n", e->heure);
        printf("Minute: %d\n", e->minute);
    }
}
void elementAffecter(ELEMENT *e1, ELEMENT e2){
    *e1=e2;
}
void elementCopier(ELEMENT *e1,ELEMENT e2){
    memcpy(*e1,e2,sizeof(articleStruct));
}
int elementComparer(ELEMENT e1,ELEMENT e2){
    return(e1->id-e2->id);
}
void elementDetruire(ELEMENT e){
    free(e);
}

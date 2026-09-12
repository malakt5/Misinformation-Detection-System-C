#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include "liste.h"
#include "fakesdb.h"
typedef struct {
    int V;
    ELEMENT *articles;
    LISTE *adjList;
    int *degre_in;
} *grapheReseau;
grapheReseau creerGraphe(int);
grapheReseau chargerGraphe(const char*);
void detruireGraphe(grapheReseau);
int ajouterArticle(grapheReseau,ELEMENT);
int supprimerArticle(grapheReseau,int);
int ajouterCitation(grapheReseau,int,int);
int supprimerCitation(grapheReseau,int,int);
void afficherGraphe(grapheReseau);
/*Interrogation du réseau*/
void articlesCites(grapheReseau,int);
void articlesCitants(grapheReseau,int);
void sourcesOriginales(grapheReseau);
void articlesIsoles(grapheReseau);
ELEMENT articlePlusCite(grapheReseau);
/*Analyse chronologique*/
int comparerDates(ELEMENT,ELEMENT);
void trierParDate(grapheReseau);
void premierCitant(grapheReseau,int);
void chainePropagation(grapheReseau,int);
/*Simulation de propagation*/
void simulerPropagation(grapheReseau, int);
void articlesAccessibles(grapheReseau, int);
/*Détection naïve de fausses informations*/
int analyserArticle(ELEMENT);
void articlesSuspectsCites(grapheReseau);
void articlesSuspectsCites(grapheReseau);
/*Bonus*/
void simulerSuppression(grapheReseau , int);
int neutraliserPropagation(grapheReseau ,int , int );
/*Plus*/
void sauvegarderGraphe(grapheReseau, const char*);
#endif

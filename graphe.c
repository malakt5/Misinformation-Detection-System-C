#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphe.h"
grapheReseau creerGraphe(int V){
    grapheReseau g;
    int i,j;

    g = (grapheReseau)malloc(sizeof(*g));
    if(!g){
        printf("\nProbleme de memoire");
        return g;
    }

    g->V = 0;
    g->articles = NULL;
    g->adjList = NULL;
    g->degre_in = NULL;

    if(V <= 0){
        return g;
    }

    ELEMENT *tmpArticles = (ELEMENT*)malloc(V * sizeof(ELEMENT));
    LISTE *tmpAdjList = (LISTE*)malloc(V * sizeof(LISTE));
    int *tmpDegre = (int*)malloc(V * sizeof(int));

    if(!tmpArticles || !tmpAdjList || !tmpDegre){
        printf("\nProbleme de memoire");
        free(tmpArticles);
        free(tmpAdjList);
        free(tmpDegre);
        return g;
    }

    for(i=0;i<V;i++){
        tmpAdjList[i] = listeCreer();
        if(!tmpAdjList[i]){
            printf("\nProbleme de memoire");
            for(j=0;j<i;j++) listeDetruire(tmpAdjList[j]);
            free(tmpAdjList);
            free(tmpArticles);
            free(tmpDegre);
            return g;
        }
    }

    for(i=0;i<V;i++) tmpDegre[i] = 0;

    g->articles = tmpArticles;
    g->adjList = tmpAdjList;
    g->degre_in = tmpDegre;
    g->V = V;

    return g;
}
grapheReseau chargerGraphe(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Erreur ouverture fichier\n");
        return NULL;
    }

    grapheReseau g = creerGraphe(0);
    char ligne[256];

    while (fgets(ligne, sizeof(ligne), f)) {

        if (ligne[0] == '#' || ligne[0] == '\n')
            continue;

        if (ligne[0] == 'A') {

            ELEMENT e = elementCreer();

            sscanf(ligne,"A %d \"%[^\"]\" %s %d %d %d %d %d %d",&e->id,e->titre,e->source,&e->score_fiabilite,&e->jour,&e->mois,&e->annee,&e->heure,&e->minute);
            ajouterArticle(g, e);
        }

        else if (ligne[0] == 'C') {
            int src, dest;
            sscanf(ligne, "C %d %d", &src, &dest);
            ajouterCitation(g, src, dest);
        }
    }

    fclose(f);
    return g;
}
void detruireGraphe(grapheReseau g){
    int i;
    for(i=0;i<g->V;i++)elementDetruire(g->articles[i]);
    free(g->articles);
    for(i=0;i<g->V;i++)listeDetruire(g->adjList[i]);
    free(g->adjList);
    free(g->degre_in);
    free(g);

}
int ajouterArticle(grapheReseau g, ELEMENT art){
    int res = 0;

    if(g != NULL && art != NULL){

        int id = g->V;

        ELEMENT *tmpArticles = realloc(g->articles, (g->V + 1) * sizeof(ELEMENT));
        LISTE *tmpAdjList = realloc(g->adjList, (g->V + 1) * sizeof(LISTE));
        int *tmpDegre = realloc(g->degre_in, (g->V + 1) * sizeof(int));

        if(tmpArticles != NULL && tmpAdjList != NULL && tmpDegre != NULL){

            g->articles = tmpArticles;
            g->adjList = tmpAdjList;
            g->degre_in = tmpDegre;

            g->articles[id] = art;
            g->articles[id]->id=id;
            g->adjList[id] = listeCreer();
            g->degre_in[id] = 0;

            g->V++;
            res = 1;
        }
        else{
            printf("\nErreur allocation mémoire");
        }
    }

    return res;
}
int supprimerArticle(grapheReseau g, int idArt){
    int succes = 1;
    int i;

    if(idArt < 0 || idArt >= g->V){
        printf("\nPosition invalide");
        succes = 0;
    }
    else{

        int i;
        for(i = 0; i < g->V; i++){
            if(i != idArt){
                supprimerCitation(g, i, idArt);
            }
        }
        elementDetruire(g->articles[idArt]);
        for(i = idArt; i < g->V - 1; i++){
            elementAffecter(&g->articles[i], g->articles[i+1]);
            g->adjList[i] = g->adjList[i+1];
            g->degre_in[i] = g->degre_in[i+1];
        }
        listeDetruire(g->adjList[idArt]);
        g->V--;
        for(i = 0; i < g->V; i++){
            g->articles[i]->id = i;
        }

    }

    return succes;
}
int ajouterCitation(grapheReseau g, int idSrc, int idDest){
    int succes=1;
    if(idSrc<0||idSrc>=g->V||idDest<0||idDest>=g->V){
        printf("\nPosition invalide");
        succes=0;
    }
    else{
        int i=1,trouve=0,taille=listeTaille(g->adjList[idSrc]);
        while(i<=taille&&!trouve){
            if(recuperer(g->adjList[idSrc],i)->id!=idDest) i++;
            else{
                trouve=1;
            }
        }

        if(trouve){
            printf("\nCitation existe deja");
            succes=0;
        }
        else{
            inserer(g->adjList[idSrc],g->articles[idDest],taille+1);
            g->degre_in[idDest]++;
        }
    }
    return succes;
}
int supprimerCitation(grapheReseau g, int idSrc, int idDest){
    int succes = 1;

    if(idSrc < 0 || idSrc >= g->V || idDest < 0 || idDest >= g->V){
        succes = 0;
    }
    else{

        int i = 1;
        int trouve = 0;
        LISTE L = g->adjList[idSrc];

        while(i <= L->lg && !trouve){

            ELEMENT e = recuperer(L, i);

            if(e->id == idDest){
                supprimer(L, i);
                g->degre_in[idDest]--;
                trouve = 1;
            }
            else{
                i++;
            }
        }

        if(!trouve){
            succes = 0;
        }
    }

    return succes;
}
void afficherGraphe(grapheReseau g) {
    int i, j;
    if(g != NULL) {
        for(i = 0; i < g->V; i++) {
            ELEMENT e = g->articles[i];
            if(e != NULL) {
                printf("%s (id:%d, source:%s, score:%d, %d/%d/%d %dh%d)\n",e->titre, e->id, e->source, e->score_fiabilite,e->jour, e->mois, e->annee, e->heure, e->minute);
            }

            LISTE cites = g->adjList[i];
            int taille = listeTaille(cites);

            for(j = 1; j <= taille; j++) {
                ELEMENT cible = recuperer(cites, j);

                if(cible != NULL) {
                    printf("--> %s\n", cible->titre);
                }
            }
        }
    }
}
void articlesCites(grapheReseau g,int idSrc){
    if(idSrc<0||idSrc>=g->V) printf("\nPosition invalide");
    else if(estVide(g->adjList[idSrc])) printf("\nAucune citation");
    else{
        int i;
        int taille=listeTaille(g->adjList[idSrc]);
        for(i=1;i<=taille;i++){
            printf("\n--> %s",recuperer(g->adjList[idSrc],i)->titre);
        }
    }
}
void articlesCitants(grapheReseau g,int idDest){
    if(idDest<0||idDest>=g->V) printf("\nPosition invalide");
    else{
        int i,j,trouve=0;
        for(i=0;i<g->V;i++){
            int taille=listeTaille(g->adjList[i]);
            for(j=1;j<=taille;j++){
                if(recuperer(g->adjList[i],j)->id==idDest){
                    printf("\n--> %s",g->articles[i]->titre);
                    trouve=1;
                }
            }
        }
        if(!trouve) printf("\nAucun article citant");
    }
}
void sourcesOriginales(grapheReseau g){
    int i,trouve=0;
    for(i=0;i<g->V;i++){
        if(listeTaille(g->adjList[i])==0){
            printf("\n--> %s",g->articles[i]->titre);
            trouve=1;
        }
    }
    if(!trouve) printf("\nAucune source originale");
}
void articlesIsoles(grapheReseau g){
    int i,k=0;
    for(i=0;i<g->V;i++){
        if(g->degre_in[i]==0){
            printf("\n--> %s (non cite par personne)",g->articles[i]->titre);
            k++;
        }
    }
    if(k==0) printf("\nAucun article isole");
}
ELEMENT articlePlusCite(grapheReseau g){
    int i, max = -1;
    int idxMax = -1;
    ELEMENT e = NULL;

    if(g != NULL && g->V > 0){

        for(i = 0; i < g->V; i++){
            if(g->degre_in[i] > max){
                max = g->degre_in[i];
                idxMax = i;
            }
        }

        if(idxMax != -1 && g->articles[idxMax] != NULL){
            e = elementCreer();
            if(e != NULL){
                elementAffecter(&e, g->articles[idxMax]);
            }
        }
    }

    return e;
}
/*Analyse chronologique*/
int comparerDates(ELEMENT art1, ELEMENT art2){
    int res;
    if(art1->annee!=art2->annee) res=art1->annee-art2->annee;
    else if(art1->mois!=art2->mois)res=art1->mois-art2->mois;
    else if(art1->jour!=art2->jour)res=art1->jour-art2->jour;
    else if(art1->heure!=art2->heure)res=art1->heure-art2->heure;
    else res=art1->minute-art2->minute;
    return res;
}
void trierParDate(grapheReseau g){
    int i,j,m;
    ELEMENT temp;
    for(i=0;i<g->V-1;i++){
        m=i;
        for(j=i+1;j<g->V;j++){
            if(comparerDates(g->articles[j],g->articles[m])<0)m=j;
        }
        temp=g->articles[m];
        g->articles[m]=g->articles[i];
        g->articles[i]=temp;
    }
    for(i=0;i<g->V;i++){
        printf("\n%d. %s(%02d/%02d/%d %02dh%02d)",i+1,g->articles[i]->titre,g->articles[i]->jour,g->articles[i]->mois,g->articles[i]->annee,g->articles[i]->heure,g->articles[i]->minute);
    }
}
void premierCitant(grapheReseau g, int idDest){
    if(idDest<0||idDest>=g->V) printf("\nPosition invalide");
    else{
        ELEMENT min;
        int i,j,trouve=0;
        for(i=0;i<g->V;i++){
            int taille=listeTaille(g->adjList[i]);
            for(j=1;j<=taille;j++){
                if(recuperer(g->adjList[i],j)->id==idDest){
                    if(!trouve) min=g->articles[i];
                    else if(comparerDates(g->articles[i],min)<0){
                        min=g->articles[i];
                    }
                    trouve=1;
                }
            }
        }
        if(!trouve) printf("\nAucun article citant");
        else printf("\n--> %s",min->titre);
    }
}
void chainePropagation(grapheReseau g, int idSrc){
    if(idSrc<0||idSrc>=g->V){
        printf("\nPosition invalide");
    }
    else{
        int i,j;
        ELEMENT tab[g->V];
        int n=0;
        tab[n++]=g->articles[idSrc];
        for(i=0;i<g->V;i++){
        int taille=listeTaille(g->adjList[i]);
        j=1;
        int trouve=0;
        while(j<=taille&&!trouve&&n<g->V){
            if(recuperer(g->adjList[i],j)->id==idSrc){
                tab[n++]=g->articles[i];
                trouve=1;
            }
            else j++;
        }
        }
        for(i=0;i<n-1;i++){
            for(j=i+1;j<n;j++){
                if(comparerDates(tab[j], tab[i]) < 0){
                    ELEMENT tmp=tab[i];
                    tab[i]=tab[j];
                    tab[j]=tmp;
                }
            }
        }
        printf("\n%s (%02d/%02d/%d %02dh%02d)",tab[0]->titre,tab[0]->jour,tab[0]->mois,tab[0]->annee,tab[0]->heure,tab[0]->minute);
        for(i = 1; i < n; i++){
            printf("\n--> cite par %s (%02d/%02d/%d %02dh%02d)",tab[i]->titre,tab[i]->jour,tab[i]->mois,tab[i]->annee,tab[i]->heure,tab[i]->minute);
        }
    }
}
/*Simulation de propagation*/
void simulerPropagation(grapheReseau g, int idSrc){
    if (idSrc < 0 || idSrc >= g->V) {
        printf("\nPosition invalide");
    }
    else{
        int i,j,nb=0;
        int visite[g->V];
        int niveau[g->V];
        for (i=0;i<g->V;i++) {
            visite[i]=0;
            niveau[i]=-1;
        }
        LISTE file=listeCreer();
        visite[idSrc]=1;
        niveau[idSrc]=0;
        int maxniv=0;
        inserer(file,g->articles[idSrc],listeTaille(file)+1);
        while (!estVide(file)) {
            ELEMENT u=recuperer(file,1);
            LISTE courant = g->adjList[u->id];
            int k=1;
            while (k<=listeTaille(courant)) {
                ELEMENT v = recuperer(courant,k);
                if (!visite[v->id]) {
                    visite[v->id] = 1;
                    niveau[v->id] = niveau[u->id] + 1;
                    if(niveau[v->id]>maxniv) maxniv=niveau[v->id];
                    inserer(file, v, listeTaille(file) + 1);
                }
                k++;
            }
            supprimer(file,1);
        }
        for(i=0;i<=maxniv;i++){
                printf("\nNiveau %d :",i);
                int first=1;
            for(j=0;j<g->V;j++){
                if(niveau[j]==i){
                    if(!first){
                            printf(",");
                        printf(" %s",g->articles[j]->titre);
                    }
                    else{
                        printf(" %s",g->articles[j]->titre);
                        first=0;
                    }

                    nb++;
                }
            }
        }
        printf("\n%d niveaux, %d articles atteints",maxniv+1,nb);
    }

}
void articlesAccessibles(grapheReseau g, int idSrc){
    if(idSrc<0||idSrc>=g->V){
        printf("\nPosition invalide");
    }
    else{
        int i;
        int visite[g->V];
        for (i=0;i<g->V;i++) {
            visite[i]=0;
        }
        LISTE file=listeCreer();
        visite[idSrc]=1;
        inserer(file,g->articles[idSrc],listeTaille(file)+1);
        while (!estVide(file)) {
            ELEMENT u=recuperer(file,1);
            LISTE courant = g->adjList[u->id];
            int k=1;
            while (k<=listeTaille(courant)) {
                ELEMENT v = recuperer(courant,k);
                if (!visite[v->id]) {
                    visite[v->id] = 1;
                    inserer(file, v, listeTaille(file) + 1);
                }
                k++;
            }
            supprimer(file,1);
        }
        for(i=0;i<g->V;i++){
             if(visite[i]==1)printf("\n%s",g->articles[i]->titre);

        }
    }
}
/*Détection naïve de fausses informations*/
int analyserArticle(ELEMENT art){
    int i=0,j,k;
    int nbf=0,nbs=0;
    char mot[100];
    char *sep = " _-.,;:!?()[]{}";
    int l=strlen(art->titre);

    for(k = 0; k < NB_FAKES; k++){
        int pos = 0, trouve = 0;

        while(art->titre[pos] != '\0' && !trouve){
            j = 0;

            while(art->titre[pos + j] != '\0' &&
                  BASE_FAKES[k][j] != '\0' &&
                  ((art->titre[pos + j] == BASE_FAKES[k][j] ||
                    art->titre[pos + j] == BASE_FAKES[k][j] + 32 ||
                    art->titre[pos + j] + 32 == BASE_FAKES[k][j]) ||
                   (art->titre[pos + j]=='_' && BASE_FAKES[k][j]==' '))){
                j++;
            }

            if(BASE_FAKES[k][j] == '\0'){
                trouve = 1;
                nbf++;
            }

            pos++;
        }
    }

    while(i < l){

        while(i < l && strchr(sep, art->titre[i]) != 0){
            i++;
        }

        if(i < l){
            j = 0;

            while(i < l && strchr(sep, art->titre[i]) == 0){
                if(j < 99){
                    mot[j++] = art->titre[i];
                }
                i++;
            }

            mot[j] = '\0';

            for(k = 0; k < NB_SUSPECTS; k++){
                int eq = 1;
                int x = 0;

                while(mot[x] != '\0' && MOTS_SUSPECTS[k][x] != '\0'){
                    char c1 = mot[x];
                    char c2 = MOTS_SUSPECTS[k][x];

                    if(c1 >= 'A' && c1 <= 'Z') c1 += 32;
                    if(c2 >= 'A' && c2 <= 'Z') c2 += 32;

                    if(c1 != c2){
                        eq = 0;
                    }

                    x++;
                }

                if(!(mot[x] == '\0' && MOTS_SUSPECTS[k][x] == '\0')){
                    eq = 0;
                }

                if(eq){
                    nbs++;
                }
            }
        }
    }

    int score_suspicion = nbf * 40 + nbs * 10;
    int score_fiabilite = 100 - score_suspicion;

    if(score_fiabilite < 0) score_fiabilite = 0;

    art->score_fiabilite = score_fiabilite;

    return score_suspicion;
}
void analyserReseau(grapheReseau g){
    int i;
    for(i=0;i<g->V;i++){
        analyserArticle(g->articles[i]);
        int score=g->articles[i]->score_fiabilite;
        if(score<40) printf ("\n[SUSPECT] %s (score: %d)",g->articles[i]->titre,score);
        else if (score>=40&&score<=69) printf ("\n[DOUTEUX] %s (score: %d)",g->articles[i]->titre, score);
        else printf ("\n[FIABLE] %s (score: %d)",g->articles[i]->titre,score);
    }
}
void articlesSuspectsCites(grapheReseau g){
    int i, j,suspect=0;
    int visite[g->V];
    for(i = 0; i < g->V; i++){
        visite[i] = 0;
    }
    for(i = 0; i < g->V; i++){
        int max = -1;

        for(j = 0; j < g->V; j++){
            if(!visite[j] &&g->articles[j]->score_fiabilite < 40 &&g->degre_in[j] > 0 &&g->degre_in[j] > max){
                suspect=1;
                max = g->degre_in[j];
            }
        }

        for(j = 0; j < g->V; j++){
            if(!visite[j] &&
               g->articles[j]->score_fiabilite < 40 &&
               g->degre_in[j] == max){

                printf("\n%s (score:%d, cite par %d articles)",
                       g->articles[j]->titre,
                       g->articles[j]->score_fiabilite,
                       g->degre_in[j]);
                visite[j] = 1;
            }
        }
    }
    if(!suspect) printf("\nAucun article suspect");
}
/*Bonus*/
void simulerSuppression(grapheReseau g, int idArt){
    if(idArt<0||idArt>=g->V) printf("\nPosition invalide");
    else{
        int i,j,k,t,trouve=0;
        printf("\nSuppression de %s",g->articles[idArt]->titre);

        printf("\n-Etait cite par:");
        int first=1,k1=0,k2=0;
        for(i=0;i<g->V;i++){
            int taille=listeTaille(g->adjList[i]);
            for(j=1;j<=taille;j++){
                if(recuperer(g->adjList[i],j)->id==idArt){
                    if(!first) printf(",");
                    printf(" %s",g->articles[i]->titre);
                    k1++;
                    first=0;
                    trouve=1;
                }
            }
        }
        if(!trouve) printf(" Aucun article citant");
        else printf(" (%d)",k1);
        printf("\nCitait:");
        if(estVide(g->adjList[idArt])) printf(" Aucune citation");
        else{
            int taille=listeTaille(g->adjList[idArt]);
            int premier=1;
            for(i=1;i<=taille;i++){
                if(!premier) printf(",");
                printf(" %s",recuperer(g->adjList[idArt],i)->titre);
                premier=0;
                k2++;
            }
            printf(" (%d)",k2);
        }

        printf("\n-Articles deconnectes :");

        int nb = 0;
        first = 1;

    for(i = 0; i < g->V; i++){
        if(i != idArt){
            int deg_sortant = 0;
            int deg_entrant = 0;
            int taille = listeTaille(g->adjList[i]);

            for(j = 1; j <= taille; j++){
                if(recuperer(g->adjList[i], j)->id != idArt){
                    deg_sortant = 1;
                }
            }

            for(k = 0; k < g->V; k++){
                if(k != idArt){
                    int taille2 = listeTaille(g->adjList[k]);

                    for(t = 1; t <= taille2; t++){
                        if(recuperer(g->adjList[k], t)->id == i){
                            deg_entrant = 1;
                        }
                    }
                }
            }

            if(deg_sortant == 0 && deg_entrant == 0){
                if(!first) printf(",");
                printf(" %s", g->articles[i]->titre);
                first = 0;
                nb++;
            }
        }
    }

    if(nb == 0) printf(" Aucun article deconnectes");
    }
}
int neutraliserPropagation(grapheReseau g, int idSrc, int idDest){
    int i;

    int supprime[g->V];
    for(i = 0; i < g->V; i++){
        supprime[i] = 0;
    }

    int compteur = 0;
    int existe = 1;

    while(existe){

        int visite[g->V];
        for(i = 0; i < g->V; i++){
            visite[i] = 0;
        }

        LISTE file = listeCreer();
        inserer(file, g->articles[idSrc], 1);
        visite[idSrc] = 1;

        existe = 0;

        int parent[g->V];
        for(i = 0; i < g->V; i++){
            parent[i] = -1;
        }

        while(!estVide(file)){
            ELEMENT u = recuperer(file, 1);
            supprimer(file, 1);

            if(u->id == idDest){
                existe = 1;
            }
            else{
                LISTE L = g->adjList[u->id];

                for(i = 1; i <= listeTaille(L); i++){
                    ELEMENT v = recuperer(L, i);

                    if(!visite[v->id] && !supprime[v->id]){
                        visite[v->id] = 1;
                        parent[v->id] = u->id;
                        inserer(file, v, listeTaille(file) + 1);
                    }
                }
            }
        }

        if(existe == 1){
            int courant = idDest;
            int stop = 0;

            while(parent[courant] != idSrc && stop == 0){
                if(parent[courant] == -1){
                    stop = 1;
                }
                else{
                    courant = parent[courant];
                }
            }

            if(stop == 0 && courant != idSrc && courant != idDest){
                supprime[courant] = 1;
                compteur++;
            }
            else{
                existe = 0;
            }
        }
    }

    return compteur;
}
/*Plus*/
void sauvegarderGraphe(grapheReseau g, const char* filename) {
    FILE* f = NULL;
    int i, ok = 1;
    NOEUD temp;

    if (g == NULL || g->V <= 0) {
        printf("Graphe vide ou NULL, fichier non modifie\n");
        ok = 0;
    }

    if (ok == 1) {
        f = fopen(filename, "w");
        if (f == NULL) {
            printf("Erreur ouverture fichier\n");
            ok = 0;
        }
    }

    if (ok == 1) {

        for (i = 0; i < g->V; i++) {
            if (g->articles[i] != NULL) {
                fprintf(f, "A %d \"%s\" %s %d %d %d %d %d %d\n",
                    g->articles[i]->id,
                    g->articles[i]->titre,
                    g->articles[i]->source,
                    g->articles[i]->score_fiabilite,
                    g->articles[i]->jour,
                    g->articles[i]->mois,
                    g->articles[i]->annee,
                    g->articles[i]->heure,
                    g->articles[i]->minute
                );
            }
        }

        fprintf(f, "\n");

        for (i = 0; i < g->V; i++) {
            if (g->adjList[i] != NULL) {
                temp = g->adjList[i]->tete;
                while (temp != NULL) {
                    if (temp->info != NULL) {
                        fprintf(f, "C %d %d\n", i, temp->info->id);
                    }
                    temp = temp->suivant;
                }
            }
        }

        printf("Sauvegarde reussie\n");
    }

    if (f != NULL) {
        fclose(f);
    }
}

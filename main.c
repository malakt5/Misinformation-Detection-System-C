#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"

void interface_menu(){
    system("cls");
    printf("\n=======================================================================================================================\n");
    printf("                                                 RESEAU D'INFORMATION\n");
    printf("\n=======================================================================================================================\n");
    printf("                                        1. Charger un reseau depuis un fichier                                           \n");
    printf("                                        2. Ajouter un article                                                            \n");
    printf("                                        3. Ajouter une citation                                                          \n");
    printf("                                        4. Supprimer un article                                                          \n");
    printf("                                        5. Supprimer une citation                                                        \n");
    printf("                                        6. Afficher le reseau                                                            \n");
    printf("                                        7. Articles cites par un article                                                 \n");
    printf("                                        8. Articles qui citent un article                                                \n");
    printf("                                        9. Sources originales / articles isoles                                          \n");
    printf("                                        10. Article le plus cite                                                         \n");
    printf("                                        11. Trier par date de publication                                                \n");
    printf("                                        12. Premier article citant                                                       \n");
    printf("                                        13. Chaine de propagation                                                        \n");
    printf("                                        14. Simuler la propagation (BFS)                                                 \n");
    printf("                                        15. Analyser les articles (fake news)                                            \n");
    printf("                                        16. Articles suspects les plus cites                                             \n");
    printf("                                        17. [BONUS] Simuler la suppression                                               \n");
    printf("                                        18. [BONUS] Neutraliser une propagation                                          \n");
    printf("                                        0. Quitter                                                                       \n");
    printf("\n=======================================================================================================================\n");

    int choix;
    grapheReseau g;
    g=creerGraphe(0);
    int quitter=0;
    do{
        printf("\n");
        printf("\nVeuillez choisir une option : ");
        scanf("%d",&choix);
        switch(choix){
            case 1:{
                if(g!=NULL) detruireGraphe(g);
                g=chargerGraphe("donnés.txt");
                if(g!=NULL &&g->V>0) printf("\nGraphe chargee avec succes");
                break;
            }
            case 2:{
                ELEMENT e=elementCreer();
                elementLire(&e);

                int ajoute;
                do{
                    printf("\n");
                    ajoute=ajouterArticle(g,e);
                }while(!ajoute);
                printf("\nArticle ajouote avec succes");
                break;
            }
           case 3:{
               int idSrc,idDes,ajoute;
               do{
                    printf("\n");
                    printf("\nDonner ID source: ");
                    scanf("%d",&idSrc);
                    printf("\nDonner ID destination: ");
                    scanf("%d",&idDes);
                    ajoute=ajouterCitation(g,idSrc,idDes);

               }while(!ajoute);
               printf("\nCitation ajoute avec succes");
               break;

           }
           case 4:{
               int id,supp=0;
               do{
                    printf("\n");
                    printf("\nDonner ID article a supprimer: ");
                    scanf("%d",&id);
                    supp=supprimerArticle(g,id);
               }while(!supp);
               printf("\nArticle supprime avec succes");
               break;
           }
          case 5:{
            int idSrc, idDes, supp = 0;

            do{
                printf("\n");
                printf("\nDonner ID source: ");
                scanf("%d", &idSrc);
                printf("\nDonner ID destination: ");
                scanf("%d", &idDes);

                if(idSrc < 0 || idSrc >= g->V || idDes < 0 || idDes >= g->V){
                    printf("\nPosition invalide");
                }
                else{
                    supp = supprimerCitation(g, idSrc, idDes);

                    if(!supp){
                        printf("\nCitation non trouvee");
                    }
                }

            }while(!supp);

            printf("\nCitation supprime avec succes");
            break;
        }
           case 6:{
               afficherGraphe(g);
               break;
           }
           case 7:{
                int id;
                do{
                    printf("\n");
                    printf("\nDonner ID article source: ");
                    scanf("%d",&id);
                    articlesCites(g,id);
                }while(id < 0 || id >= g->V);
                break;
           }
            case 8:{
                int id;
                do{
                    printf("\n");
                    printf("\nDonner ID article destination: ");
                    scanf("%d",&id);
                    articlesCitants(g,id);
                }while(id < 0 || id >= g->V);
                break;
            }
            case 9:{
                printf("\nLes sources originales: ");
                sourcesOriginales(g);
                printf("\n\nLes articles isoles: ");
                articlesIsoles(g);
                break;
            }
            case 10:{
                printf("\n");
                ELEMENT e = articlePlusCite(g);
                if(e == NULL){
                    printf("\nAucun article trouvé");
                }
                else{
                    printf("\nArticle le plus cite:\n");
                    printf("\n--> %s (cite par %d articles)",e->titre,g->degre_in[e->id]);
                    break;
                }
            }
            case 11:{
                trierParDate(g);
                break;
            }
            case 12:{
                int id;
                do{
                    printf("\n");
                    printf("\nDonner ID article destination: ");
                    scanf("%d",&id);
                    printf("\nPremier article citant: ");
                    premierCitant(g,id);
                }while(id < 0 || id >= g->V);
                break;
            }
            case 13:{
                int id;
                do{
                    printf("\n");
                    printf("\nDonner ID article source: ");
                    scanf("%d",&id);
                    chainePropagation(g,id);
                }while(id < 0 || id >= g->V);
                break;
            }
            case 14:{
                int id;
                do{
                    printf("\n");
                    printf("\nDonner ID article source: ");
                    scanf("%d",&id);
                    simulerPropagation(g,id);
                }while(id < 0 || id >= g->V);
                break;

            }
            case 15:{
                analyserReseau(g);
                break;
            }
            case 16:{
                articlesSuspectsCites(g);
                break;
            }
            case 17:{
                int id;
                do{
                    printf("\n");
                    printf("\nDonner ID article source: ");
                    scanf("%d",&id);
                    simulerSuppression(g,id);
                }while(id < 0 || id >= g->V);
                break;

            }
            case 18:{
                int idSrc,idDes;
                do{
                    printf("\n");
                    printf("\nDonner ID source: ");
                    scanf("%d", &idSrc);
                    printf("\nDonner ID destination: ");
                    scanf("%d", &idDes);
                    int k = neutraliserPropagation(g, idSrc, idDes);
                    if(k == 0){
                        printf("\nAucun article a supprimer");
                    }
                    else{
                        printf("\nArticle supprime : %d", k);
                    }

                }while(idSrc<0||idSrc>=g->V||idDes<0||idDes >= g->V);
                break;
            }
            case 0:{
                quitter=1;
                sauvegarderGraphe(g,"donnés.txt");
                system("cls");
                printf("||--------------------------------------------------------------------------------------------------------------||\n");
                printf("||--------------------------------------------------------------------------------------------------------------||\n");
                printf("||                                                   AU REVOIR!                                                 ||\n");
                printf("||--------------------------------------------------------------------------------------------------------------||\n");
                printf("||--------------------------------------------------------------------------------------------------------------||\n");
                quitter=1;
                break;
            }
        }

    }while(!quitter);
}

int main()
{
    interface_menu();
    return 0;
}

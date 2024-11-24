#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "game_play.h"
#include "sauvegarde.h"
#include "historique.h"
#define SIZE 20



int main() {
    int tab[SIZE][SIZE];
    int mode,modeblindage=1,nombredejoueurs,nombredejoueursblindage=1;
    int choixjoueur1,choixjoueur2;
    int corbarj1=1,corbar2j1=1,ab=1,abbb=1,blindage=1,abc=0,placement = 1;// blindage
    int ok=1,blindage2=1,az=1,lu=1,aw=1;// blindage
    int lig=0, col=0,a=1,nbarrierej1=10,choix,choix2,position,position2;
    int ligposition=1,colposition=0,test;//Pion1
    int ligposition2=17,colposition2=0,nbarrierej2=10;//Pion 2
    int ligposition3=0,colposition3=1,nbarrierej3=5;//Pion 3
    int ligposition4=0,colposition4=17,nbarrierej4=5;//Pion 3
    int  max = 2,joueur1,k=0; // max du tirage au sort
    int nbcoupsj1=1,nbcoupsj2=1,coups1,coups2,nbcoupsj3=1,nbcoupsj4,coups3,coups4; // coups spécial
    int numero_de_joueur=2;
    srand(time(NULL));
    char pseudo1[20],pseudo2[20],pseudo3[20],pseudo4[20],joueurstart[20],joueursecond[20]="b",joueurtroisieme[20]="c",joueurquatrieme[20]="d"; // enregistrement des nom
    char legende[30][30];
    int pionj1=63,pionj2=63,pionj3=63,pionj4=63,pionBot=64;
    int choix_coups_bot=0;

    char  bot1[10]= "jojo" ; // BOT
    int cote=1; // amelioration de la probabilité
    int nombredetour=0;

    char nom_du_fichier[20]= "classement.txt"; // historique
    int resultat=1;

    //// SAUVEGARDE ////
    char nom_du_fichier_sauvegarde[100];
    int sauvegarde=0;
    int saut=0;


    plateau(tab); // Afficher le damier initial
    create_historique(nom_du_fichier); // création du fichier classement sur le pc
    //system("cls");
    printf("\n");
    Menu(&mode);
    if(mode==1 || mode ==2) {
        sauvegarde=1;
    }
    while(sauvegarde==1) {
        if (mode==1) { //lancer une partie
            if(saut==0) {
                while(nombredejoueursblindage==1) {
                    printf("Combien de joueurs ? \n");
                    scanf("%d",&nombredejoueurs);
                    if (nombredejoueurs>=1 && nombredejoueurs<=4) {
                        nombredejoueursblindage=0;
                    }
                }
            }
            if(nombredejoueurs==1) {
                if (saut==0) {
                    choix_nom_ordre(pseudo1,pseudo2,pseudo3,pseudo4,joueurstart,joueursecond,joueurtroisieme,joueurquatrieme,bot1,nombredejoueurs,&joueur1,nom_du_fichier);
                }
                if(joueur1==1) {
                    if (saut==0) {
                        printf("%s doit  choisir son pion\n",joueurstart);
                        choix_pion(&pionj1);
                        printf("%s doit  placer son pion sur la 1 er ligne\n",joueurstart);
                        placement_du_pion(tab,&ligposition,&colposition,pionj1,numero_de_joueur,nombredejoueurs, joueurstart,nbarrierej1,pionBot);
                        printf("\n");
                        printf("%s place son pion",joueursecond);
                        Sleep(1000);
                        printf("\n");

                        /////////// BOT ///////////
                        placement_du_pion_bot(tab,ligposition2,&colposition2,pionBot,nombredejoueurs, joueurstart,nbarrierej1,pionj1);
                        /////////// BOT ///////////
                    }

                    while(a==1) {

                        blindage=1;
                        ab=1;

                        if (nombredetour>1) {
                            while(blindage2==1) {
                                printf("Voulez enregistrer la partie et quitter 1. ?\n");
                                printf("2. continuer\n");
                                scanf("%d",&abc);
                                if(abc==1 || abc==2) {
                                    blindage2=0;
                                }
                            }

                            if (abc==1) {
                                recherche_sauvegarde(nom_du_fichier_sauvegarde);
                                plateau_sauvegarde(tab,nom_du_fichier_sauvegarde,joueurstart,pionj1,nbarrierej1,joueursecond,pionj2,nbarrierej2,joueurtroisieme,pionj3,nbarrierej3,joueurquatrieme,pionj4,nbarrierej4,mode,nombredejoueurs,ligposition,colposition,ligposition2,colposition2,ligposition3,colposition3,ligposition4,colposition4,1);
                                return 0;
                            }

                        }
                        while(ab==1) {
                            printf("%s que voulez faire ? 1. attendre 2. placer une barriere 3.deplacer un pion 4.Coup speciale\n",joueurstart);
                            scanf("%d", &choixjoueur1);
                            if (choixjoueur1>=1 && choixjoueur1<=4) {
                                ab=0;
                            }
                        }
                        switch (choixjoueur1) {
                            case 1:
                                coups1=0;
                            break;
                            case 2:
                            if (nbarrierej1==0) {
                                printf("Vous ne pouvez pas placer de barrière\n");
                            }
                            else if (nbarrierej1>0 && nbarrierej1<=10) {
                                placer_barriere(tab,&lig,&col,&coups1,nombredejoueurs,bot1,nbarrierej2,pionBot);
                                nbarrierej1--;
                            }

                            break;

                            case 3:
                                while (blindage==1) {
                                    printf("Voulez-vous aller en haut  ou en bas ou a droite ou a gauche\n");
                                    scanf("%d",&position);
                                    if (position==1) {
                                        haut(tab,&ligposition,&colposition,&coups1,pionj1,nombredejoueurs,bot1,nbarrierej2,pionBot,&blindage);
                                    }
                                    if (position==2) {
                                        bas(tab,&ligposition,&colposition,&coups1,pionj1,nombredejoueurs,bot1,nbarrierej2,pionBot,&blindage);
                                    }
                                    if (position==3) {
                                        droite(tab,&ligposition,&colposition,&coups1,pionj1,nombredejoueurs,bot1,nbarrierej2,pionBot,&blindage);

                                    }
                                    if (position==4) {
                                        gauche(tab,&ligposition,&colposition,&coups1,pionj1,nombredejoueurs,bot1,nbarrierej2,pionBot,&blindage);
                                    }
                                    else if (position>=5 ||position==0) {
                                        printf("ERREUR\n");
                                    }
                                }
                            break;
                            case 4 :
                                if (nbcoupsj1==1) {
                                    coupspecial(tab,&nbcoupsj1,&ligposition2,&colposition2,&coups2,&lig,&col,pionj2,nombredejoueurs,bot1,nbarrierej2,pionBot);
                                    nbcoupsj1=0;
                                }
                                else if (nbcoupsj1==0) {
                                    printf("Vous n'avez plus de coup special\n");
                                }
                            break;
                        }
                        if (ligposition==17) {
                            printf("%s a gagné la partie\n",joueurstart);
                            sauvegarde_historique(nom_du_fichier,joueurstart,1,1);
                            a=0;
                            return 0;
                        }
                        printf("\n");
                        printf("%s joue",joueursecond);

                        Sleep(1000);
                        printf("\n");
                        choix_coups_bot=1;
                        /////////// BOT ///////////

                        choix_bot(tab,&choix,ligposition2,colposition2,nbcoupsj2,nbarrierej2,choix_coups_bot,cote,nombredetour);
                        if (choix==4 && ligposition2==17) {
                            choix=3;
                        }
                        if (choix ==1) {
                            coupspecial_bot(tab,coups1,lig,col,&ligposition,&colposition,pionj1,nombredejoueurs,joueurstart,nbarrierej1,pionj1);
                            printf("\n %s utilise son coups special\n ",joueursecond);
                            nbcoupsj2=0;;
                        }
                        if (choix ==2) {
                            placer_barriere_bot(tab,&lig,&col,&coups2,nombredejoueurs,joueurstart,nbarrierej1,pionj1);
                            nbarrierej2--;
                        }
                        if (choix ==3) { // en haut
                            haut_bot(tab,&ligposition2,&colposition2,&coups2,64,nombredejoueurs,joueurstart,nbarrierej1,pionBot);

                        }if (choix ==4) { // bas
                            bas_bot(tab,&ligposition2,&colposition2,&coups2,64,nombredejoueurs,joueurstart,nbarrierej1,pionBot);

                        }
                        if (choix ==5) { // droite
                            droite_bot(tab,&ligposition2,&colposition2,&coups2,64,nombredejoueurs,joueurstart,nbarrierej1,pionBot);

                        }
                        if (choix ==6) { // gauche
                            gauche_bot(tab,&ligposition2,&colposition2,&coups2,64,nombredejoueurs,joueurstart,nbarrierej1,pionBot);
                        }
                        if (ligposition2==1) {
                            printf("%s a gagné la partie\n",joueursecond);
                            sauvegarde_historique(nom_du_fichier,joueurstart,-1,1);
                            a=0;
                        }
                        nombredetour++;

                        /////////// BOT ///////////
                    }

                }
                if(joueur1==2) {
                    if (saut==0) {
                        /////////// BOT ///////////
                        printf("%s place son pion\n",joueurstart);
                        Sleep(1000);
                        placement_du_pion_bot(tab,ligposition,&colposition,pionBot,nombredejoueurs, joueursecond,nbarrierej2,pionj2);
                        printf("\n");
                        /////////// BOT ///////////

                        printf(" %s doit  choisir son pion\n",joueursecond);
                        choix_pion(&pionj1);
                        printf("%s doit  placer son pion sur la 17 ligne\n",joueursecond);
                        placement_du_pion(tab,&ligposition2,&colposition2,pionj1,numero_de_joueur,nombredejoueurs,joueursecond,nbarrierej2,pionj1);
                    }

                    while(a==1) {
                        blindage=1;
                        ab=1;
                        /////////// BOT ///////////
                        choix_bot(tab,&choix,ligposition,colposition,nbcoupsj1,nbarrierej1,choix_coups_bot,cote,nombredetour);
                        if (choix==4 && ligposition==17) {
                            choix=3;
                        }
                        if (choix ==1) {
                            coupspecial_bot(tab,coups2,lig,col,&ligposition2,&colposition2,pionj1,nombredejoueurs,joueursecond,nbarrierej2,pionj1);
                            printf("\n %s utilise son coups special\n ",joueurstart);
                            nbcoupsj1=0;;
                        }
                        if (choix ==2) {
                            placer_barriere_bot(tab,&lig,&col,&coups1,nombredejoueurs,joueursecond,nbarrierej2,pionj1);
                            nbarrierej1--;
                        }
                        if (choix ==3) { // en haut
                            haut_bot(tab,&ligposition,&colposition,&coups1,64,nombredejoueurs,joueursecond,nbarrierej2,pionj1);


                        }if (choix ==4) { // bas
                            bas_bot(tab,&ligposition,&colposition,&coups1,64,nombredejoueurs,joueursecond,nbarrierej2,pionj1);

                        }
                        if (choix ==5) { // droite
                            droite_bot(tab,&ligposition,&colposition,&coups1,64,nombredejoueurs,joueursecond,nbarrierej2,pionj1);

                        }
                        if (choix ==6) { // gauche
                            gauche_bot(tab,&ligposition,&colposition,&coups1,64,nombredejoueurs,joueursecond,nbarrierej2,pionj1);
                        }
                        if (ligposition==17) {
                            printf("%s a gagné la partie\n",joueurstart);
                            sauvegarde_historique(nom_du_fichier,joueursecond,-1,1);
                            a=0;
                        }
                        printf("\n \n");
                        /////////// BOT ///////////

                        if (nombredetour>1) {
                            while (ok==1) {
                                printf("Voulez enregistrer la partie et quitter 1. ?\n");
                                printf("2. continuer\n");
                                scanf("%d", &abc);
                                if(abc==1 || abc==2) {
                                    ok=0;
                                }
                            }
                            if (abc == 1) {
                                recherche_sauvegarde(nom_du_fichier_sauvegarde);
                                plateau_sauvegarde(tab,nom_du_fichier_sauvegarde,joueurstart,pionj1,nbarrierej1,joueursecond,pionj2,nbarrierej2,joueurtroisieme,pionj3,nbarrierej3,joueurquatrieme,pionj4,nbarrierej4,mode,nombredejoueurs,ligposition ,colposition,ligposition2 ,colposition2,ligposition3 ,colposition3,ligposition4 ,colposition4,2);
                                return 0;
                            }
                        }

                        while (ab == 1) {
                            printf(
                                "%s que voulez faire ? 1. attendre 2. placer une barriere 3.deplacer un pion 4.Coup speciale\n",
                                joueursecond);
                            scanf("%d", &choixjoueur1);
                            if (choixjoueur1>=1 && choixjoueur1<=4) {
                                ab=0;
                            }
                        }
                        switch (choixjoueur1) {
                            case 1:
                                coups2=0;
                            break;
                            case 2:
                                if (nbarrierej2==0) {
                                    printf("Vous ne pouvez pas placer de barrière\n");
                                }
                                else if (nbarrierej2>0 && nbarrierej2<=10) {
                                    placer_barriere(tab,&lig,&col,&coups2,nombredejoueurs,joueurstart,nbarrierej2,pionBot);
                                    nbarrierej2--;
                                }
                            break;

                            case 3:
                                while (blindage==1) {
                                    printf("Voulez-vous aller en haut  ou en bas ou à droite ou à gauche\n");
                                    scanf("%d",&position);
                                    if (position==1) {
                                        haut(tab,&ligposition2,&colposition2,&coups2,pionj1,nombredejoueurs,joueurstart,nbarrierej1,pionBot,&blindage);

                                    }
                                    if (position==2) {
                                        bas(tab,&ligposition2,&colposition2,&coups2,pionj1,nombredejoueurs,joueurstart,nbarrierej1,pionBot,&blindage);

                                    }
                                    if (position==3) {
                                        droite(tab,&ligposition2,&colposition2,&coups2,pionj1,nombredejoueurs,joueurstart,nbarrierej1,pionBot,&blindage);


                                    }
                                    if (position==4) {
                                        gauche(tab,&ligposition2,&colposition2,&coups2,pionj1,nombredejoueurs,joueurstart,nbarrierej1,pionBot,&blindage);

                                    }
                                    else if (position>=5 || position==0) {
                                        printf("ERREUR\n");
                                    }
                                }
                            break;
                            case 4 :
                                if (nbcoupsj2==1) {
                                    coupspecial(tab,&nbcoupsj2,&ligposition,&colposition,&coups1,&lig,&col,64,nombredejoueurs,joueurstart,nbarrierej1,pionBot);
                                    nbcoupsj2=0;
                                }
                                else if (nbcoupsj2==0) {
                                    printf("Vous n'avez plus de coup special\n");
                                }
                            break;
                        }
                        if (ligposition2==1) {
                            printf("%s a gagne la partie\n",joueursecond);
                            sauvegarde_historique(nom_du_fichier,joueursecond,1,1);
                            a=0;
                            return 0;
                        }
                        choix_coups_bot=1;
                        nombredetour++;
                        printf("\n");


                    }
                }


            }

            if (nombredejoueurs==2) {
                if (saut==0) {
                    choix_nom_ordre(pseudo1,pseudo2,pseudo3,pseudo4,joueurstart,joueursecond,joueurtroisieme,joueurquatrieme,bot1,nombredejoueurs,&joueur1,nom_du_fichier);
                    printf("\n");


                    printf("%s doit  choisir son pion\n",joueurstart);
                    choix_pion(&pionj1);
                    printf("%s doit  placer son pion sur la 1 er ligne\n",joueurstart);
                    placement_du_pion(tab,&ligposition,&colposition,pionj1,numero_de_joueur,nombredejoueurs,joueursecond,nbarrierej2,pionj2);

                    printf("%s doit  choisir son pion\n",joueursecond);
                    choix_pion(&pionj2);
                    printf("%s doit  placer son pion sur la 1 er ligne\n",joueursecond);
                    placement_du_pion(tab,&ligposition2,&colposition2,pionj2,numero_de_joueur,nombredejoueurs,joueurstart,nbarrierej1,pionj1);
                }
                while (a==1) {
                    Color(15,0);
                    ab=1;
                    if (nombredetour>1) {
                        while (az==1) {
                            printf("Voulez enregistrer la partie et quitter 1. ?\n");
                            printf("2. continuer\n");
                            scanf("%d",&abc);
                            if(abc==1 || abc==2) {
                                az=0;
                            }
                        }
                        if (abc==1) {
                            recherche_sauvegarde(nom_du_fichier_sauvegarde);
                            plateau_sauvegarde(tab,nom_du_fichier_sauvegarde,joueurstart,pionj1,nbarrierej1,joueursecond,pionj2,nbarrierej2,joueurtroisieme,pionj3,nbarrierej3,joueurquatrieme,pionj4,nbarrierej4,mode,nombredejoueurs,ligposition,colposition,ligposition2,colposition2,ligposition3,colposition3,ligposition4,colposition4,0);
                            return 0;
                        }

                    }
                    while(ab==1) {
                        printf("%s que voulez faire ? 1. attendre 2. placer une barriere 3.deplacer un pion 4.Coup speciale\n",joueurstart);
                        scanf("%d", &choixjoueur1);
                        if (choixjoueur1>=1 && choixjoueur1<=4) {
                            ab=0;
                        }
                    }

                    switch (choixjoueur1) {
                        case 1:
                            coups1=0;
                        break;
                        case 2:
                            if (nbarrierej1==0) {
                                printf("Vous ne pouvez pas placer de barrière\n");
                            }
                            else if (nbarrierej1>0 && nbarrierej1<=10) {
                                placer_barriere(tab,&lig,&col,&coups1,nombredejoueurs,joueursecond,nbarrierej2,pionj2);
                                nbarrierej1--;
                            }
                        break;

                        case 3:
                            blindage=1;
                        while (blindage==1) {
                            printf("Voulez-vous aller en haut  ou en bas ou à droite ou à gauche\n");
                            scanf("%d",&position);
                            if (position==1) {
                                haut(tab,&ligposition,&colposition,&coups1,pionj1,nombredejoueurs,joueursecond,nbarrierej2,pionj2,&blindage);
                            }
                            if (position==2) {
                                bas(tab,&ligposition,&colposition,&coups1,pionj1,nombredejoueurs,joueursecond,nbarrierej2,pionj2,&blindage);
                            }
                            if (position==3) {
                                droite(tab,&ligposition,&colposition,&coups1,pionj1,nombredejoueurs,joueursecond,nbarrierej2,pionj2,&blindage);

                            }
                            if (position==4) {
                                gauche(tab,&ligposition,&colposition,&coups1,pionj1,nombredejoueurs,joueursecond,nbarrierej2,pionj2,&blindage);
                            }
                            else if (position==0 || position>=5) {
                                printf("ERREUR\n");
                            }
                        }
                        break;
                        case 4 :
                            if (nbcoupsj1==1) {
                                coupspecial(tab,&nbcoupsj1,&ligposition2,&colposition2,&coups2,&lig,&col,pionj2,nombredejoueurs,joueursecond,nbarrierej2,pionj2);
                                nbcoupsj1=0;
                            }
                            else if (nbcoupsj1==0) {
                                printf("Vous n'avez plus de coup special\n");
                            }
                        break;
                    }
                    if (ligposition==17) {
                        printf("%s a gagné la partie\n",joueurstart);
                        sauvegarde_historique(nom_du_fichier,joueurstart,1,1);
                        sauvegarde_historique(nom_du_fichier,joueursecond,-1,1);
                        a=0;
                    }
                    // TOUR DU JOUEUR 2
                    Color(15,0);
                    abbb=1;
                    while(abbb==1) {
                        printf("%s que voulez faire ? 1. attendre 2. placer une barriere 3.bouger un pion 4. coups special\n",joueursecond);
                        scanf("%d", &choixjoueur2);
                        if (choixjoueur2>=1 && choixjoueur2<=4) {
                            abbb=0;
                        }
                    }
                    switch (choixjoueur2) {
                        case 1:
                            coups2=0;
                        break;
                        case 2:
                            if (nbarrierej2==0) {
                                printf("Vous ne pouvez pas placer de barrière\n");
                            }
                            else if (nbarrierej2>0 && nbarrierej2<=10) {
                                placer_barriere(tab,&lig,&col,&coups2,nombredejoueurs,joueurstart,nbarrierej1,pionj1);
                                nbarrierej2--;
                            }
                        break;
                        case 3:
                            blindage=1;
                        while (blindage==1) {
                            printf("Voulez-vous aller en haut  ou en bas ou a droite ou a gauche\n");
                            scanf("%d",&position);
                            if (position==1) {
                                haut(tab,&ligposition2,&colposition2,&coups2,pionj2,nombredejoueurs,joueurstart,nbarrierej1,pionj1,&blindage);
                            }
                            if (position==2) {
                                bas(tab,&ligposition2,&colposition2,&coups2,pionj2,nombredejoueurs,joueurstart,nbarrierej1,pionj1,&blindage);

                            }
                            if (position==3) {
                                droite(tab,&ligposition2,&colposition2,&coups2,pionj2,nombredejoueurs,joueurstart,nbarrierej1,pionj1,&blindage);
                            }
                            if (position==4) { // gauche
                                gauche(tab,&ligposition2,&colposition2,&coups2,pionj2,nombredejoueurs,joueurstart,nbarrierej1,pionj1,&blindage);

                            }
                            else if (position==0 || position>=5) {
                                printf("ERREUR\n");
                            }
                        }
                        break;
                        case 4:
                            if (nbcoupsj2==1) {
                                coupspecial(tab,&nbcoupsj2,&ligposition,&colposition,&coups1,&lig,&col,pionj1,nombredejoueurs,joueurstart,nbarrierej1,pionj1);
                                nbcoupsj2=0;
                            }
                            else if (nbcoupsj2==0) {
                                printf("Vous n'avez plus de coups special\n");
                            }
                        break;

                    }
                    if (ligposition2==1) {
                        printf("\n");
                        printf("%s a gagnéz la partie",joueursecond);
                        sauvegarde_historique(nom_du_fichier,joueursecond,1,1);
                        sauvegarde_historique(nom_du_fichier,joueurstart,-1,1);
                        a=0;
                    }
                    nombredetour++;

                }

            }
            if (nombredejoueurs==3) {
                if (saut==0) {
                    nbarrierej1=5;
                    nbarrierej2=5;
                    choix_nom_ordre(pseudo1,pseudo2,pseudo3,pseudo4,joueurstart,joueursecond,joueurtroisieme,joueurquatrieme,bot1,nombredejoueurs,&joueur1,nom_du_fichier);
                    printf("\n");

                    printf("%s doit  choisir son pion\n",joueurstart);
                    choix_pion(&pionj1);
                    printf("%s doit  placer son pion sur la 1 er ligne\n",joueurstart);
                    placement_du_pion(tab,&ligposition,&colposition,pionj1,numero_de_joueur,nombredejoueurs,joueursecond,nbarrierej2,pionj2);

                    printf("%s doit  choisir son pion\n",joueursecond);
                    choix_pion(&pionj2);
                    printf("%s doit  placer son pion sur la 1 er ligne\n",joueursecond);
                    placement_du_pion(tab,&ligposition2,&colposition2,pionj2,numero_de_joueur,nombredejoueurs,joueurtroisieme,nbarrierej3,pionj3);

                    numero_de_joueur=4;

                    printf("%s doit  choisir son pion\n",joueurtroisieme);
                    choix_pion(&pionj3);
                    printf("%s doit  placer son pion sur la 1 er ligne\n",joueurtroisieme);
                    placement_du_pion(tab,&ligposition3,&colposition3,pionj3,numero_de_joueur,nombredejoueurs,joueurquatrieme,nbarrierej4,pionBot);

                    printf("%s place son pion",bot1);
                    Sleep(1000);
                    printf("\n");

                    /////////// BOT ///////////
                    colposition4=17;
                    placement_du_pion_bot_3(tab,&ligposition4,colposition4,pionBot,nombredejoueurs,joueurstart,nbarrierej1,pionj1);
                    /////////// BOT ///////////
                }



                /////////// Tour du joueur 1 ///////
                while (a==1) {
                    Color(15,0);
                    ab=1;
                    if (nombredetour>1) {
                        while(lu==1) {
                            printf("1.Voulez enregistrer la partie et quitter ?\n");
                            printf("2. continuer\n");
                            scanf("%d",&abc);
                            if(abc==1 || abc==3) {
                                lu=0;
                            }
                        }
                        if (abc==1) {
                            recherche_sauvegarde(nom_du_fichier_sauvegarde);
                            plateau_sauvegarde(tab,nom_du_fichier_sauvegarde,joueurstart,pionj1,nbarrierej1,joueursecond,pionj2,nbarrierej2,joueurtroisieme,pionj3,nbarrierej3,joueurquatrieme,pionj4,nbarrierej4,mode,nombredejoueurs,ligposition,colposition,ligposition2,colposition2,ligposition3,colposition3,ligposition4,colposition4,1);
                            return 0;
                        }

                    }
                    while(ab==1) {
                        printf("%s que voulez faire ? 1. attendre 2. placer une barriere 3.deplacer un pion 4.Coup speciale\n",joueurstart);
                        scanf("%d", &choixjoueur1);
                        if (choixjoueur1>=1 && choixjoueur1<=4) {
                            ab=0;
                        }
                    }

                    switch (choixjoueur1) {
                        case 1:
                            coups1=0;
                        break;
                        case 2:
                            if (nbarrierej1==0) {
                                printf("Vous ne pouvez pas placer de barrière\n");
                            }
                            else if (nbarrierej1>0 && nbarrierej1<=10) {
                                placer_barriere(tab,&lig,&col,&coups1,nombredejoueurs,joueursecond,nbarrierej2,pionj2);
                                nbarrierej1--;
                            }
                        break;

                        case 3:
                            blindage=1;
                        while (blindage==1) {
                            printf("Voulez-vous aller en haut  ou en bas ou à droite ou à gauche\n");
                            scanf("%d",&position);
                            if (position==1) {
                                haut(tab,&ligposition,&colposition,&coups1,pionj1,nombredejoueurs,joueursecond,nbarrierej2,pionj2,&blindage);
                            }
                            if (position==2) {
                                bas(tab,&ligposition,&colposition,&coups1,pionj1,nombredejoueurs,joueursecond,nbarrierej2,pionj2,&blindage);
                            }
                            if (position==3) {
                                droite(tab,&ligposition,&colposition,&coups1,pionj1,nombredejoueurs,joueursecond,nbarrierej2,pionj2,&blindage);

                            }
                            if (position==4) {
                                gauche(tab,&ligposition,&colposition,&coups1,pionj1,nombredejoueurs,joueursecond,nbarrierej2,pionj2,&blindage);
                            }
                            else if (position==0 || position>=5) {
                                printf("ERREUR\n");
                            }
                        }
                        break;
                        case 4 :
                            if (nbcoupsj1==1) {
                                coupspecial(tab,&nbcoupsj1,&ligposition4,&colposition4,&coups4,&lig,&col,pionBot,nombredejoueurs,joueursecond,nbarrierej2,pionj2);
                                nbcoupsj1=0;
                            }
                            else if (nbcoupsj1==0) {
                                printf("Vous n'avez plus de coup special\n");
                            }
                        break;
                    }
                    if (ligposition==17) {
                        printf("%s a gagné la partie\n",joueurstart);
                        sauvegarde_historique(nom_du_fichier,joueursecond,-1,1);
                        sauvegarde_historique(nom_du_fichier,joueurstart,1,1);
                        sauvegarde_historique(nom_du_fichier,joueurtroisieme,-1,1);
                        a=0;
                    }
                    //////// TOUR DU JOUEUR 2 //////////
                    Color(15,0);
                    abbb=1;
                    while(abbb==1) {
                        printf("%s que voulez faire ? 1. attendre 2. placer une barriere 3.bouger un pion 4. coups special\n",joueursecond);
                        scanf("%d", &choixjoueur2);
                        if (choixjoueur2>=1 && choixjoueur2<=4) {
                            abbb=0;
                        }
                    }
                    switch (choixjoueur2) {
                        case 1:
                            coups2=0;
                        break;
                        case 2:
                            if (nbarrierej2==0) {
                                printf("Vous ne pouvez pas placer de barrière\n");
                            }
                            else if (nbarrierej2>0 && nbarrierej2<=10) {
                                placer_barriere(tab,&lig,&col,&coups2,nombredejoueurs,joueurtroisieme,nbarrierej3,pionj3);
                                nbarrierej2--;
                            }
                        break;
                        case 3:
                            blindage=1;
                        while (blindage==1) {
                            printf("Voulez-vous aller en haut  ou en bas ou a droite ou a gauche\n");
                            scanf("%d",&position);
                            if (position==1) {
                                haut(tab,&ligposition2,&colposition2,&coups2,pionj2,nombredejoueurs,joueurtroisieme,nbarrierej3,pionj3,&blindage);
                            }
                            if (position==2) {
                                bas(tab,&ligposition2,&colposition2,&coups2,pionj2,nombredejoueurs,joueurtroisieme,nbarrierej3,pionj3,&blindage);
                            }
                            if (position==3) {
                                droite(tab,&ligposition2,&colposition2,&coups2,pionj2,nombredejoueurs,joueurtroisieme,nbarrierej3,pionj3,&blindage);
                            }
                            if (position==4) { // gauche
                                gauche(tab,&ligposition2,&colposition2,&coups2,pionj2,nombredejoueurs,joueurtroisieme,nbarrierej3,pionj3,&blindage);

                            }
                            else if (position==0 || position>=5) {
                                printf("ERREUR\n");
                            }
                        }
                        break;
                        case 4:
                            if (nbcoupsj2==1) {
                                coupspecial(tab,&nbcoupsj2,&ligposition,&colposition,&coups1,&lig,&col,pionj1,nombredejoueurs,joueurtroisieme,nbarrierej3,pionj3);
                                nbcoupsj2=0;
                            }
                            else if (nbcoupsj2==0) {
                                printf("Vous n'avez plus de coups special\n");
                            }
                        break;

                    }
                    if (ligposition2==1) {
                        printf("\n");
                        printf("%s a gagnéz la partie",joueursecond);
                        sauvegarde_historique(nom_du_fichier,joueursecond,1,1);
                        sauvegarde_historique(nom_du_fichier,joueurstart,-1,1);
                        sauvegarde_historique(nom_du_fichier,joueurtroisieme,-1,1);
                        a=0;
                    }

                    ///// TOUR du joueur 3 /////

                    ab=1;
                    while(ab==1) {
                        printf("%s que voulez faire ? 1. attendre 2. placer une barriere 3.deplacer un pion 4.Coup speciale\n",joueurtroisieme);
                        scanf("%d", &choixjoueur1);
                        if (choixjoueur1>=1 && choixjoueur1<=4) {
                            ab=0;
                        }
                    }

                    switch (choixjoueur1) {
                        case 1:
                            coups3=0;
                        break;
                        case 2:
                            if (nbarrierej3==0) {
                                printf("Vous ne pouvez pas placer de barrière\n");
                            }
                            else if (nbarrierej3>0 && nbarrierej3<=5) {
                                placer_barriere(tab,&lig,&col,&coups3,nombredejoueurs,joueurquatrieme,nbarrierej4,pionBot);
                                nbarrierej3--;
                            }
                        break;

                        case 3:
                            blindage=1;
                        while (blindage==1) {
                            printf("Voulez-vous aller en haut  ou en bas ou à droite ou à gauche\n");
                            scanf("%d",&position);
                            if (position==1) {
                                haut(tab,&ligposition3,&colposition3,&coups3,pionj3,nombredejoueurs,joueurquatrieme,nbarrierej4,pionBot,&blindage);
                            }
                            if (position==2) {
                                bas(tab,&ligposition3,&colposition3,&coups3,pionj3,nombredejoueurs,joueurquatrieme,nbarrierej4,pionBot,&blindage);
                            }
                            if (position==3) {
                                droite(tab,&ligposition3,&colposition3,&coups3,pionj3,nombredejoueurs,joueurquatrieme,nbarrierej4,pionBot,&blindage);

                            }
                            if (position==4) {
                                gauche(tab,&ligposition3,&colposition3,&coups3,pionj3,nombredejoueurs,joueurquatrieme,nbarrierej4,pionBot,&blindage);
                            }
                            else if (position==0 || position>=5) {
                                printf("ERREUR\n");
                            }
                        }
                        break;
                        case 4 :
                            if (nbcoupsj3==1) {
                                coupspecial(tab,&nbcoupsj3,&ligposition2,&colposition2,&coups2,&lig,&col,pionj2,nombredejoueurs,joueurquatrieme,nbarrierej4,pionBot);
                                nbcoupsj3=0;
                            }
                            else if (nbcoupsj3==0) {
                                printf("Vous n'avez plus de coup special\n");
                            }
                        break;
                    }

                    if (colposition3==17) {
                        printf("\n");
                        printf("%s a gagné la partie", joueurtroisieme);
                        sauvegarde_historique(nom_du_fichier,joueursecond,-1,1);
                        sauvegarde_historique(nom_du_fichier,joueurstart,-1,1);
                        sauvegarde_historique(nom_du_fichier,joueurtroisieme,1,1);
                        a = 0;
                    }

                    /////////// BOT ///////////
                    printf("\n%s joue ",joueurquatrieme);
                    Sleep(1000);
                    cote=2;
                    choix_bot(tab,&choix,ligposition4,colposition4,nbcoupsj4,nbarrierej4,choix_coups_bot,cote,nombredetour);
                    if (choix==4 && ligposition==17) {
                        choix=3;
                    }
                    if (choix ==1) {
                        coupspecial_bot(tab,coups3,lig,col,&ligposition3,&colposition3,pionj3,nombredejoueurs,joueurstart,nbarrierej1,pionj1);
                        printf("\n %s utilise son coups special\n",joueurquatrieme);
                        nbcoupsj4=0;;
                    }
                    if (choix ==2) {
                        placer_barriere_bot(tab,&lig,&col,&coups4,nombredejoueurs,joueurstart,nbarrierej1,pionj1);
                        printf("\n %s place du barriere ",joueurquatrieme);
                        nbarrierej4--;
                    }
                    if (choix ==3) { // en haut
                        haut_bot(tab,&ligposition4,&colposition4,&coups4,64,nombredejoueurs,joueurstart,nbarrierej1,pionj1);
                        printf("\n %s se deplace en haut ",joueurquatrieme);


                    }if (choix ==4) { // bas
                        bas_bot(tab,&ligposition4,&colposition4,&coups4,64,nombredejoueurs,joueurstart,nbarrierej1,pionj1);
                        printf("\n %s se deplace en bas ",joueurquatrieme);

                    }
                    if (choix ==5) { // droite
                        droite_bot(tab,&ligposition4,&colposition4,&coups4,64,nombredejoueurs,joueurstart,nbarrierej1,pionj1);
                        printf("\n %s se deplace a droite ",joueurquatrieme);

                    }
                    if (choix ==6) { // gauche
                        gauche_bot(tab,&ligposition4,&colposition4,&coups4,64,nombredejoueurs,joueurstart,nbarrierej1,pionj1);
                        printf("\n %s se deplace a gauche ",joueurquatrieme);
                    }
                    if (colposition==1) {
                        printf("%s a gagné la partie\n",joueurquatrieme);
                        sauvegarde_historique(nom_du_fichier,joueursecond,-1,1);
                        sauvegarde_historique(nom_du_fichier,joueurstart,-1,1);
                        sauvegarde_historique(nom_du_fichier,joueurtroisieme,-1,1);
                        a=0;
                    }
                    printf("\n \n");
                    /////////// BOT ///////////
                    nombredetour++;

                }
            }
            else if (nombredejoueurs==4) {
                if (saut==0) {
                    nbarrierej1=5;
                    nbarrierej2=5;
                    choix_nom_ordre(pseudo1,pseudo2,pseudo3,pseudo4,joueurstart,joueursecond,joueurtroisieme,joueurquatrieme,bot1,nombredejoueurs,&joueur1,nom_du_fichier);
                    printf("\n");


                    printf("%s doit  choisir son pion\n",joueurstart);
                    choix_pion(&pionj1);
                    printf("%s doit  placer son pion sur la 1 er ligne\n",joueurstart);
                    placement_du_pion(tab,&ligposition,&colposition,pionj1,numero_de_joueur,nombredejoueurs,joueursecond,nbarrierej2,pionj2);


                    printf("%s doit  choisir son pion\n",joueursecond);
                    choix_pion(&pionj2);
                    printf("%s doit  placer son pion sur la 1 er ligne\n",joueursecond);
                    placement_du_pion(tab,&ligposition2,&colposition2,pionj2,numero_de_joueur,nombredejoueurs,joueurtroisieme,nbarrierej3,pionj3);

                    numero_de_joueur=4;

                    printf("%s doit  choisir son pion\n",joueurtroisieme);
                    choix_pion(&pionj3);
                    printf("%s doit  placer son pion sur la 1 er ligne\n",joueurtroisieme);
                    placement_du_pion(tab,&ligposition3,&colposition3,pionj3,numero_de_joueur,nombredejoueurs,joueurquatrieme,nbarrierej4,pionj4);

                    printf("%s doit  choisir son pion\n",joueurquatrieme);
                    choix_pion(&pionj4);
                    printf("%s doit  placer son pion sur la 1 er ligne\n",joueurquatrieme);
                    placement_du_pion(tab,&ligposition4,&colposition4,pionj4,numero_de_joueur,nombredejoueurs,joueurstart,nbarrierej1,pionj1);
                }

                while (a==1) {
                    Color(15,0);
                    ab=1;
                    if (nombredetour>1) {
                        while(aw==1) {
                            printf("Voulez enregistrer la partie et quitter 1. ?\n");
                            printf("2. continuer\n");
                            scanf("%d",&abc);
                            if(abc==1 || abc==2) {
                                aw=0;
                            }
                        }
                        if (abc==1) {
                            recherche_sauvegarde(nom_du_fichier_sauvegarde);
                            plateau_sauvegarde(tab,nom_du_fichier_sauvegarde,joueurstart,pionj1,nbarrierej1,joueursecond,pionj2,nbarrierej2,joueurtroisieme,pionj3,nbarrierej3,joueurquatrieme,pionj4,nbarrierej4,mode,nombredejoueurs,ligposition,colposition,ligposition2,colposition2,ligposition3,colposition3,ligposition4,colposition4,1);
                            return 0;
                        }

                    }
                    while(ab==1) {
                        printf("%s que voulez faire ? 1. attendre 2. placer une barriere 3.deplacer un pion 4.Coup speciale\n",joueurstart);
                        scanf("%d", &choixjoueur1);
                        if (choixjoueur1>=1 && choixjoueur1<=4) {
                            ab=0;
                        }
                    }

                    switch (choixjoueur1) {
                        case 1:
                            coups1=0;
                        break;
                        case 2:
                            if (nbarrierej1==0) {
                                printf("Vous ne pouvez pas placer de barrière\n");
                            }
                            else if (nbarrierej1>0 && nbarrierej1<=10) {
                                placer_barriere(tab,&lig,&col,&coups1,nombredejoueurs,joueursecond,nbarrierej2,pionj2);
                                nbarrierej1--;
                            }

                        break;

                        case 3:
                            blindage=1;
                        while (blindage==1) {
                            printf("Voulez-vous aller en haut  ou en bas ou a droite ou a gauche\n");
                            scanf("%d",&position);
                            if (position==1) {
                                haut(tab,&ligposition,&colposition,&coups1,pionj1,nombredejoueurs,joueursecond,nbarrierej2,pionj2,&blindage);
                            }
                            if (position==2) {
                                bas(tab,&ligposition,&colposition,&coups1,pionj1,nombredejoueurs,joueursecond,nbarrierej2,pionj2,&blindage);
                            }
                            if (position==3) {
                                droite(tab,&ligposition,&colposition,&coups1,pionj1,nombredejoueurs,joueursecond,nbarrierej2,pionj2,&blindage);

                            }
                            if (position==4) {
                                gauche(tab,&ligposition,&colposition,&coups1,pionj1,nombredejoueurs,joueursecond,nbarrierej2,pionj2,&blindage);
                            }
                            else if (position==0 || position>=5) {
                                printf("ERREUR\n");
                            }
                        }
                        break;
                        case 4 :
                            if (nbcoupsj1==1) {
                                coupspecial(tab,&nbcoupsj1,&ligposition4,&colposition4,&coups1,&lig,&col,pionj4,nombredejoueurs,joueursecond,nbarrierej2,pionj2);
                                nbcoupsj1=0;
                            }
                            else if (nbcoupsj1==0) {
                                printf("Vous n'avez plus de coup special\n");
                            }
                        break;
                    }
                    if (ligposition==17) {
                        printf("%s a gagné la partie\n",joueurstart);
                        sauvegarde_historique(nom_du_fichier,joueursecond,-1,1);
                        sauvegarde_historique(nom_du_fichier,joueurstart,1,1);
                        sauvegarde_historique(nom_du_fichier,joueurtroisieme,-1,1);
                        sauvegarde_historique(nom_du_fichier,joueurquatrieme,-1,1);
                        a=0;
                    }
                    // TOUR DU JOUEUR 2
                    Color(15,0);
                    abbb=1;
                    while(abbb==1) {
                        printf("%s que voulez faire ? 1. attendre 2. placer une barriere 3.bouger un pion 4. coups special\n",joueursecond);
                        scanf("%d", &choixjoueur2);
                        if (choixjoueur2>=1 && choixjoueur2<=4) {
                            abbb=0;
                        }
                    }
                    switch (choixjoueur2) {
                        case 1:
                            coups2=0;
                        break;
                        case 2:
                            if (nbarrierej2==0) {
                                printf("Vous ne pouvez pas placer de barrière\n");
                            }
                            else if (nbarrierej2>0 && nbarrierej2<=10) {
                                placer_barriere(tab,&lig,&col,&coups2,nombredejoueurs,joueurtroisieme,nbarrierej3,pionj3);
                                nbarrierej2--;
                            }
                        break;
                        case 3:
                            blindage=1;
                        while (blindage==1) {
                            printf("Voulez-vous aller en haut  ou en bas ou a droite ou a gauche\n");
                            scanf("%d",&position);
                            if (position==1) {
                                haut(tab,&ligposition2,&colposition2,&coups2,pionj2,nombredejoueurs,joueurtroisieme,nbarrierej3,pionj3,&blindage);
                            }
                            if (position==2) {
                                bas(tab,&ligposition2,&colposition2,&coups2,pionj2,nombredejoueurs,joueurtroisieme,nbarrierej3,pionj3,&blindage);
                            }
                            if (position==3) {
                                droite(tab,&ligposition2,&colposition2,&coups2,pionj2,nombredejoueurs,joueurtroisieme,nbarrierej3,pionj3,&blindage);
                            }
                            if (position==4) { // gauche
                                gauche(tab,&ligposition2,&colposition2,&coups2,pionj2,nombredejoueurs,joueurtroisieme,nbarrierej3,pionj3,&blindage);

                            }
                            else if (position==0 || position>=5) {
                                printf("ERREUR\n");
                            }
                        }
                        break;
                        case 4:
                            if (nbcoupsj2==1) {
                                coupspecial(tab,&nbcoupsj2,&ligposition,&colposition,&coups2,&lig,&col,pionj1,nombredejoueurs,joueurtroisieme,nbarrierej3,pionj3);
                                nbcoupsj2=0;
                            }
                            else if (nbcoupsj2==0) {
                                printf("Vous n'avez plus de coups special\n");
                            }
                        break;

                    }
                    if (ligposition2==1) {
                        printf("\n");
                        printf("%s a gagnéz la partie",joueursecond);
                        sauvegarde_historique(nom_du_fichier,joueursecond,1,1);
                        sauvegarde_historique(nom_du_fichier,joueurstart,-1,1);
                        sauvegarde_historique(nom_du_fichier,joueurtroisieme,-1,1);
                        sauvegarde_historique(nom_du_fichier,joueurquatrieme,-1,1);
                        a=0;
                    }

                    ///// TOUR du joueur 3 /////

                    ab=1;
                    while(ab==1) {
                        printf("%s que voulez faire ? 1. attendre 2. placer une barriere 3.deplacer un pion 4.Coup speciale\n",joueurtroisieme);
                        scanf("%d", &choixjoueur1);
                        if (choixjoueur1>=1 && choixjoueur1<=4) {
                            ab=0;
                        }
                    }

                    switch (choixjoueur1) {
                        case 1:
                            coups3=0;
                        break;
                        case 2:
                            if (nbarrierej3==0) {
                                printf("Vous ne pouvez pas placer de barrière\n");
                            }
                            else if (nbarrierej3>0 && nbarrierej3<=5) {
                                placer_barriere(tab,&lig,&col,&coups3,nombredejoueurs,joueurquatrieme,nbarrierej4,pionj4);
                                nbarrierej3--;
                            }

                        break;

                        case 3:
                            blindage=1;
                        while (blindage==1) {
                            printf("Voulez-vous aller en haut  ou en bas ou a droite ou a gauche\n");
                            scanf("%d",&position);
                            if (position==1) {
                                haut(tab,&ligposition3,&colposition3,&coups3,pionj3,nombredejoueurs,joueurquatrieme,nbarrierej4,pionj4,&blindage);
                            }
                            if (position==2) {
                                bas(tab,&ligposition3,&colposition3,&coups3,pionj3,nombredejoueurs,joueurquatrieme,nbarrierej4,pionj4,&blindage);
                            }
                            if (position==3) {
                                droite(tab,&ligposition3,&colposition3,&coups3,pionj3,nombredejoueurs,joueurquatrieme,nbarrierej4,pionj4,&blindage);

                            }
                            if (position==4) {
                                gauche(tab,&ligposition3,&colposition3,&coups3,pionj3,nombredejoueurs,joueurquatrieme,nbarrierej4,pionj4,&blindage);
                            }
                            else if (position==0 || position>=5) {
                                printf("ERREUR\n");
                            }
                        }
                        break;
                        case 4 :
                            if (nbcoupsj3==1) {
                                coupspecial(tab,&nbcoupsj3,&ligposition2,&colposition2,&coups2,&lig,&col,pionj2,nombredejoueurs,joueurquatrieme,nbarrierej4,pionj4);
                                nbcoupsj3=0;

                            }
                            else if (nbcoupsj3==0) {
                                printf("Vous n'avez plus de coup special\n");
                            }
                        break;
                    }

                    if (colposition3==17) {
                        printf("\n");
                        printf("%s a gagné la partie", joueurtroisieme);
                        sauvegarde_historique(nom_du_fichier,joueursecond,-1,1);
                        sauvegarde_historique(nom_du_fichier,joueurstart,-1,1);
                        sauvegarde_historique(nom_du_fichier,joueurtroisieme,1,1);
                        sauvegarde_historique(nom_du_fichier,joueurquatrieme,-1,1);
                        a = 0;
                    }


                    ///// TOUR du joueur 4 /////

                    ab=1;
                    while(ab==1) {
                        printf("%s que voulez faire ? 1. attendre 2. placer une barriere 3.deplacer un pion 4.Coup speciale\n",joueurquatrieme);
                        scanf("%d", &choixjoueur1);
                        if (choixjoueur1>=1 && choixjoueur1<=4) {
                            if (nbcoupsj4!=0 && choixjoueur1) {
                                ab=0;
                            }
                            else if (nbcoupsj4==0 && choixjoueur1) {
                                ab=1;
                            }
                        }
                    }

                    switch (choixjoueur1) {
                        case 1:
                            coups4=0;
                        break;
                        case 2:
                            if (nbarrierej4==0) {
                                printf("Vous ne pouvez pas placer de barrière\n");
                            }
                            else if (nbarrierej4>0 && nbarrierej4<=5) {
                                placer_barriere(tab,&lig,&col,&coups4,nombredejoueurs,joueurstart,nbarrierej1,pionj1);
                                nbarrierej4--;
                            }

                        break;

                        case 3:
                            blindage=1;
                        while (blindage==1) {
                            printf("Voulez-vous aller en haut  ou en bas ou à droite ou à gauche\n");
                            scanf("%d",&position);
                            if (position==1) {
                                haut(tab,&ligposition4,&colposition4,&coups4,pionj4,nombredejoueurs,joueurstart,nbarrierej1,pionj1,&blindage);
                            }
                            if (position==2) {
                                bas(tab,&ligposition4,&colposition4,&coups4,pionj4,nombredejoueurs,joueurstart,nbarrierej1,pionj1,&blindage);
                            }
                            if (position==3) {
                                droite(tab,&ligposition4,&colposition4,&coups4,pionj4,nombredejoueurs,joueurstart,nbarrierej1,pionj1,&blindage);

                            }
                            if (position==4) {
                                gauche(tab,&ligposition4,&colposition4,&coups4,pionj4,nombredejoueurs,joueurstart,nbarrierej1,pionj1,&blindage);
                            }
                            else if (position==0 || position>=5) {
                                printf("ERREUR\n");
                            }
                        }
                        break;
                        case 4 :
                            if (nbcoupsj4==1) {
                                coupspecial(tab,&nbcoupsj4,&ligposition4,&colposition4,&coups4,&lig,&col,pionj4,nombredejoueurs,joueurstart,nbarrierej1,pionj1);
                                nbcoupsj4=0;
                            }
                            else if (nbcoupsj4==0) {
                                printf("Vous n'avez plus de coup special\n");
                            }
                        break;
                    }

                    if (colposition4==1) {
                        printf("\n");
                        printf("%s a gagné la partie", joueurquatrieme);
                        sauvegarde_historique(nom_du_fichier,joueursecond,-1,1);
                        sauvegarde_historique(nom_du_fichier,joueurstart,-1,1);
                        sauvegarde_historique(nom_du_fichier,joueurtroisieme,-1,1);
                        sauvegarde_historique(nom_du_fichier,joueurquatrieme,1,1);
                        a = 0;
                    }
                    nombredetour++;
                }
            }
        }

        if(mode==2){
            printf("Nom du fichier");
            scanf("%s",nom_du_fichier_sauvegarde);
            strcat(nom_du_fichier_sauvegarde,".txt");
            plateau(tab);
            lire_plateau_sauvegarde(nom_du_fichier_sauvegarde, tab , joueurstart,&pionj1,&nbarrierej1,joueursecond,&pionj2,&nbarrierej2,joueurtroisieme,&pionj3,&nbarrierej3,joueurquatrieme,&pionj4,&nbarrierej4,&mode,&nombredejoueurs,&ligposition,&colposition,&ligposition2,&colposition2,&ligposition3,&colposition3,&ligposition4,&colposition4,&joueur1);
            printf("%d %d %d",mode,nombredejoueurs,joueur1);
            sauvegarde=1;
            saut=1;
        }
    }
if(mode==3){
    afficher_classment(nom_du_fichier);
    Sleep(100000);

}
if(mode==4) {
    printf("L objectif est d atteindre le premier la rangee opposee avec son pion.\n");
    printf("Il se joue a 2 ou 4 pions et chaque joueur place son pion au centre de sa rangee de depart.\n\n");
    printf("DEROULEMENT DU JEU :\n");
    printf("Le jeu se joue a tour de role. Lors de son tour, un joueur peut effectuer une seule action parmi les suivantes :\n");
    printf("-DEPLACER SON PION (HAUT, BAS, GAUCHE, DROITE).\n");
    printf("-PLACER UNE BARRIERE :\n");
    printf("Le joueur place une barriere sur deux bords consecutifs entre les cases, formant une ligne droite horizontale ou verticale.\n");
    printf("Une barrière ne peut pas bloquer completement le chemin d'un joueur vers son objectif. Il doit toujours rester un chemin accessible.\n\n");
    printf("FIN DE LA PARTIE :\n");
    printf("Le premier joueur qui atteint la rangee opposee avec son pion gagne la partie.\n");
    printf("Le gagnant gagne 5 points et le perdant perd 3 ponts\n\n");
    printf("STRATEGIE:");
    printf("Combinez deplacement et placement de barrieres pour ralentir vos adversaires tout en progressant vers votre objectif.\n");
    printf("SOYEZ ATTENTIF\n\n");
    printf("Amusez-vous bien !");


}
else if (mode==5) {

}
} // fin du main
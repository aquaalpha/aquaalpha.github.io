//
// Created by jugue on 30/10/2024.
//

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include "game_play.h"
#include "sauvegarde.h"
#include "historique.h"
#define SIZE 18

void Color(int couleurDuTexte, int couleurDeFond) {
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDeFond * 16 + couleurDuTexte);
}

void Menu(int *mode) {
    int modeblindage=1;
    while(modeblindage==1) {
        printf("Bonjour, que voulez-vous faire ? \n");
        printf("1. Lancer une nouvelle partie  ? \n");
        printf("2. reprendre une partie  ? \n");
        printf("3. Classement ? \n");
        printf("4. Règle du jeux \n");
        printf("5. Quitter \n");
        scanf("%d", mode);
        if (*mode >= 1 && *mode<=5) {
            modeblindage=0;
        }
    }
}

void plateau(int tab[SIZE][SIZE]) {
    int a=1,b=1;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j <=SIZE; j++) {
            if (i==0 && i<=17) {
                tab[i][j]=0;
            }
            if ( i!=0 && j!=0 && i<=17) {
                if (i%2 == 0) {
                    tab[i][j] = 0; // Ligne paire remplie de 0
                } else {
                    tab[i][j] = j % 2; // Ligne impaire avec alternance de 1 et 0
                }
            }
        }
    }
for (int i = 0; i < 25; i++) {
    for (int j = 0; j < SIZE; j++) {
        if (i==0 && j%2!=0 && a<10) {
            tab[i][j]=a;
            a++;
        }
    }
}
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i%2!=0 && j==0 && b<10) {
                tab[i][j]=b;
                b++;
            }
        }
    }
    for (int i = 0; i <SIZE; i++) {
        for (int j = 0; j <= SIZE; j++) {

                if (j==0 && i%2!=0) {
                    Color(15,0);
                    printf("   %d  ",tab[i][j]);
                }
                if(i == 0 && j==1) {                       // espace au debut de la 1er ligne pour permettre l'alignement
                    Color(15,0);
                    printf("     ",tab[i][j]);
                }
                 if(i%2==0 && j==0 && i>0) {                       // espace au debut de la 1er ligne pour permettre l'alignement
                   Color(15,0);
                     printf("      ",tab[i][j]);
                 }
                if(i==0 && j%2==1 && tab[0][1]==1) {
                    Color(15,0);
                    printf("  %d   ",tab[i][j]);
                }
                if (tab[i][j] == 0 && i!=0 && j!=0) {
                    Color(0,0);
                    printf("   ",tab[i][j]);
                }
                else if (i!=0 && j!=0){      // légendes
                    if (i==2 && j==18){
                        Color(4,0);
                        printf("          Nombre de joueurs");
                    }
                    if (i==4 && j==18){
                        Color(4,0);
                        printf("          Tour de :");
                    }
                    if (i==6 && j==18){
                        Color(4,0);
                        printf("          Score :");
                    }
                    if (i==8 && j==18){
                        Color(4,0);
                        printf("          Pion :");
                    }
                    if (i==10 && j==18){
                        Color(4,0);
                        printf("          Mur restant :");
                    }
                    else if (j!=18){
                        Color(0,15);
                        printf("   ",tab[i][j]);
                    }
                }
        }
        printf("\n");
    }
    Color(15,0);

}

void plateau_repair(int tab[SIZE][SIZE],int ligne,int colonne,int valeur) {
    int a=1;
    tab[ligne][colonne]=valeur;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j <= SIZE; j++) {
            if (i==0 && j%2!=0 && j>=3) {
                tab[i][j] = a;
                Color(15,0);
                printf(" %d ",tab[i][j]);
                a++;
            }
            if (i==0 && j==17) {
                Color(15,0);
                tab[i][j] = 9;
                printf("    %d",tab[i][j]);
            }
            if(tab[i][j] == 98 && i%2!=0 ) {
                Color(15,0);
                printf(" %c ",tab[i][j]);
            }
            if(tab[i][j] == 98 && i%2==0) {
                Color(15,0);
                printf("    %c  ",tab[i][j]);
            }
            if(tab[i][j] == 64 || tab[i][j] == 35 || tab[i][j] == 36 || tab[i][j] == 38) {
                Color(4,15);
                printf(" %c ",tab[i][j]);
            }
            if ((j==0 && i%2!=0) || tab[i][j] == 0) {
                Color(15,0);
                printf("   ",tab[i][j]); //
            }
            if (j==0  && i!=0&& tab[i][j] !=0) {
                printf("%d  ",tab[i][j]);
                Color(15,0);
            }
            if (i==2 && j==18) {
                Color(4,0);
                printf("          ");
                Color(0,15);
            }
            if (i==4 && j==18){
                Color(4,0);
                printf("          ");
                Color(0,15);
            }
            if (i==6 && j==18){
                Color(4,0);
                printf("          Score :");
                Color(0,15);
            }
            if (i==8 && j==18){
                Color(4,0);
                printf("         ");
                Color(0,15);
            }
            if (i==10 && j==18){
                Color(4,0);
                printf("          ");
                Color(0,15);
            }
            else if (tab[i][j] == 1 && i!=0 && j!=0) {
                Color(0,15);
                printf("   ",tab[i][j]);

            }

        }
        printf("\n");
    }
    Color(15,0);

}

void modifierCase(int tab[SIZE][SIZE], int ligne, int colonne, int nouvelleValeur, int nombre_de_joueurs, char TOUR[20], int pion,int barriere) {
    int a=1;
    int score;
    lire_score(&score, TOUR);
    tab[ligne][colonne] = nouvelleValeur;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j <= SIZE; j++) {
            if (i==0 && j%2!=0 && j>=3) {
                tab[i][j] = a;
                Color(15,0);
                printf(" %d ",tab[i][j]);
                a++;
            }
            if(i%2==0 && j==0 && i>0) {                       // espace au debut de la 1er ligne pour permettre l'alignement
                Color(15,0);
                printf("   ",tab[i][j]);
            }
            if (i==0 && j==17) {
                Color(15,0);
                tab[i][j] = 9;
                printf("    %d",tab[i][j]);
            }
            if(tab[i][j] == 98 && i%2!=0 ) {
                Color(15,0);
                printf(" %c ",tab[i][j]);
            }
            if(tab[i][j] == 98 && i%2==0) {
                Color(15,0);
                printf(" %c ",tab[i][j]);
            }
            if(tab[i][j] == 64 || tab[i][j] == 35 || tab[i][j] == 36 || tab[i][j] == 38) {
                Color(4,15);
                printf(" %c ",tab[i][j]);
            }
            if ((j==0 && i%2!=0) || tab[i][j] == 0) {
                Color(15,0);
                printf("   ",tab[i][j]); //
            }
            if (j==0  && i!=0&& tab[i][j] !=0) {
                printf("%d  ",tab[i][j]);
                Color(15,0);
            }
            if (i==2 && j==18) {
                Color(4,0);
                printf("   Nombre de joueurs :%d",nombre_de_joueurs);
                Color(0,15);
            }
            if (i==4 && j==18){
                Color(4,0);
                printf("   Tour de : %s",TOUR);
                Color(0,15);
            }
            if (i==6 && j==18){
                Color(4,0);
                printf("   Score :%d", score);
                Color(0,15);
            }
            if (i==8 && j==18){
                Color(4,0);
                printf("   Pion : %c",pion);
                Color(0,15);
            }
            if (i==10 && j==18){
                Color(4,0);
                printf("   Mur restant : %d",barriere);
                Color(0,15);
            }
            else if (tab[i][j] == 1 && i!=0 && j!=0) {
                Color(0,15);
                printf("   ",tab[i][j]);

            }

        }
        printf("\n");
    }
    Color(15,0);
}

void haut(int tab[SIZE][SIZE],int *ligposition,int *colposition,int *coups1,int pion,int nombre_de_joueurs, char TOUR[20],int barriere,int pion2 , int *blindage) { // &ligposition
            int position2,test,test2;
            test= *ligposition-1;
            test2= *colposition;
            if(tab[*ligposition-1][*colposition]==98 || *ligposition==1) {
                printf ("vous ne pouvez pas aller en haut\n");
                *blindage=1;
            }
            if (tab[test][*colposition]==0 && *ligposition!=1 && tab[*ligposition-2][*colposition]==1) {
                tab[*ligposition][*colposition]=1;
                *ligposition=*ligposition-2;
                tab[*ligposition][*colposition]=pion;
                modifierCase(tab, *ligposition, *colposition, pion,nombre_de_joueurs, TOUR,pion2,barriere);
                *coups1=4;
                *blindage=0;
            }
            if (tab[*ligposition-2][*colposition]!=1 && tab[*ligposition-4][*colposition]==1 && tab[*ligposition-3][*colposition]==0 && tab[*ligposition-1][*colposition]!=98 && *ligposition>3) {
                tab[*ligposition][*colposition]=1;
                *ligposition=*ligposition-4;
                tab[*ligposition][*colposition]=pion;
                modifierCase(tab, *ligposition, *colposition, pion,nombre_de_joueurs, TOUR,pion2,barriere);
                *coups1=10;
                *blindage=0;
            }
}
void haut_bot(int tab[SIZE][SIZE],int *ligposition,int *colposition,int *coups1,int pion,int nombre_de_joueurs, char TOUR[20],int barriere,int pion2) { // &ligposition
    int position2,test,test2;
    test= *ligposition-1;
    test2= *colposition;
    if(tab[*ligposition-1][*colposition]==98 || *ligposition==1) {
        //printf ("vous ne pouvez pas aller en haut\n");
    }
    if (tab[test][*colposition]==0 && *ligposition!=1 && tab[*ligposition-2][*colposition]==1) {
        tab[*ligposition][*colposition]=1;
        *ligposition=*ligposition-2;
        tab[*ligposition][*colposition]=pion;
        modifierCase(tab, *ligposition, *colposition, pion,nombre_de_joueurs, TOUR,pion2,barriere);
        *coups1=4;
    }
    if (tab[*ligposition-2][*colposition]!=1 && tab[*ligposition-4][*colposition]==1 && tab[*ligposition-3][*colposition]==0 && tab[*ligposition-1][*colposition]!=98 && *ligposition>3) {
        tab[*ligposition][*colposition]=1;
        *ligposition=*ligposition-4;
        tab[*ligposition][*colposition]=pion;
        modifierCase(tab, *ligposition, *colposition, pion,nombre_de_joueurs, TOUR,pion2,barriere);
        *coups1=10;
    }
}

void bas(int tab[SIZE][SIZE],int *ligposition,int *colposition, int *coups1,int pion,int nombre_de_joueurs, char TOUR[20],int barriere,int pion2,int *blindage ) {


    if (tab[*ligposition+1][*colposition]==0 && *ligposition!=17 && tab[*ligposition+2][*colposition]==1) {
        tab[*ligposition][*colposition]=1;
        *ligposition=*ligposition+2;
        tab[*ligposition][*colposition]=pion;
        modifierCase(tab, *ligposition, *colposition, pion,nombre_de_joueurs, TOUR,pion2,barriere);
        *coups1=3;
        *blindage=0;
    }
    if (tab[*ligposition+2][*colposition]!=1 && *ligposition<15 && tab[*ligposition+4][*colposition]==1 && tab[*ligposition+3][*colposition]==0) {
        tab[*ligposition][*colposition]=1;
        *ligposition=*ligposition+4;
        tab[*ligposition][*colposition]=pion;
        modifierCase(tab, *ligposition, *colposition, pion,nombre_de_joueurs, TOUR,pion2,barriere);
        *coups1=11;
        *blindage=0;
    }
    else if (tab[*ligposition+1][*colposition]==98 || *ligposition==17 || ( tab[*ligposition+2][*colposition]!=1 && tab[*ligposition+2][*colposition]==98) ) {
        printf("Vous ne pouvez pas aller en bas\n");
        *blindage=1;
    }
}

void bas_bot(int tab[SIZE][SIZE],int *ligposition,int *colposition, int *coups1,int pion,int nombre_de_joueurs, char TOUR[20],int barriere,int pion2 ) {


    if (tab[*ligposition+1][*colposition]==0 && *ligposition!=17 && tab[*ligposition+2][*colposition]==1) {
        tab[*ligposition][*colposition]=1;
        *ligposition=*ligposition+2;
        tab[*ligposition][*colposition]=pion;
        modifierCase(tab, *ligposition, *colposition, pion,nombre_de_joueurs, TOUR,pion2,barriere);
        *coups1=3;
    }
    if (tab[*ligposition+2][*colposition]!=1 && *ligposition<15 && tab[*ligposition+4][*colposition]==1 && tab[*ligposition+3][*colposition]==0) {
        tab[*ligposition][*colposition]=1;
        *ligposition=*ligposition+4;
        tab[*ligposition][*colposition]=pion;
        modifierCase(tab, *ligposition, *colposition, pion,nombre_de_joueurs, TOUR,pion2,barriere);
        *coups1=11;
    }
    else{ //if (tab[*ligposition+1][*colposition]==98 || *ligposition==17 || ( tab[*ligposition+2][*colposition]!=1 && tab[*ligposition+2][*colposition]==98) ) {
        //printf("Vous ne pouvez pas aller en bas\n");
    }
}

void droite(int tab[SIZE][SIZE], int *ligposition,int *colposition, int *coups1,int pion,int nombre_de_joueurs, char TOUR[20],int barriere,int pion2,int *blindage ) {
    if (*colposition<17 && *colposition>=1  && tab[*ligposition][*colposition+1]==0) {
        tab[*ligposition][*colposition]=1;
        *colposition=*colposition+2;
        tab[*ligposition][*colposition]=pion;
        modifierCase(tab, *ligposition, *colposition, pion,nombre_de_joueurs, TOUR,pion2,barriere);
        *coups1=5;
        *blindage=0;
    }
    if (tab[*ligposition][*colposition+1]==98 || *colposition==17){
        printf("Vous ne pouvez pas aller a droite\n");
        *blindage=1;
    }
    if (tab[*ligposition][*colposition+2]!=1 && *colposition<15 && tab[*ligposition][*colposition+4]==1 && tab[*ligposition][*colposition+3]==0) {
        tab[*ligposition][*colposition]=1;
        *ligposition=*ligposition+4;
        tab[*ligposition][*colposition]=pion;
        modifierCase(tab, *ligposition, *colposition, pion,nombre_de_joueurs, TOUR,pion2,barriere);
        *coups1=12;
        *blindage=0;
    }
    else {
        printf("Vous ne pouvez pas aller a droite\n");
    }
}
void droite_bot(int tab[SIZE][SIZE], int *ligposition,int *colposition, int *coups1,int pion,int nombre_de_joueurs, char TOUR[20],int barriere,int pion2 ) {
    if (*colposition<17 && *colposition>=1  && tab[*ligposition][*colposition+1]==0 && tab[*ligposition][*colposition+2]==1 ) {
        tab[*ligposition][*colposition]=1;
        *colposition=*colposition+2;
        tab[*ligposition][*colposition]=pion;
        modifierCase(tab, *ligposition, *colposition, pion,nombre_de_joueurs, TOUR,pion2,barriere);
        *coups1=5;
    }
    if ((tab[*ligposition][*colposition+2]!=1 && tab[*ligposition][*colposition+1]!=0) || *colposition==17){
        //printf("Vous ne pouvez pas aller a droite\n");
    }
    if (tab[*ligposition][*colposition+2]!=1 && *colposition<15 && tab[*ligposition][*colposition+4]==1 && tab[*ligposition][*colposition+3]==0) {
        tab[*ligposition][*colposition]=1;
        *ligposition=*ligposition+4;
        tab[*ligposition][*colposition]=pion;
        modifierCase(tab, *ligposition, *colposition, pion,nombre_de_joueurs, TOUR,pion2,barriere);
        *coups1=12;
    }
    else{
        //printf("Vous ne pouvez pas aller a droite\n");
    }
}

void gauche(int tab[SIZE][SIZE], int *ligposition,int *colposition, int *coups1,int pion,int nombre_de_joueurs, char TOUR[20],int barriere,int pion2, int *blindage) {
    if (*colposition>1 && *colposition<=17  && tab[*ligposition][*colposition-1]==0 && tab[*ligposition][*colposition-2]==1) {
        tab[*ligposition][*colposition]=1;
        *colposition=*colposition-2;
        tab[*ligposition][*colposition]=pion;
        modifierCase(tab, *ligposition, *colposition, pion,nombre_de_joueurs, TOUR,pion2,barriere);
        *coups1=6;
        *blindage=0;
    }
    if (tab[*ligposition][*colposition-1]==98 || *colposition==1){
        printf("Vous ne pouvez pas aller a droite\n");
        *blindage=1;
    }
    if (tab[*ligposition][*colposition-2]!=1 && *colposition>3 && tab[*ligposition][*colposition-4]==1 && tab[*ligposition][*colposition-3]==0) {
        tab[*ligposition][*colposition]=1;
        *ligposition=*ligposition-4;
        tab[*ligposition][*colposition]=pion;
        modifierCase(tab, *ligposition, *colposition, pion,nombre_de_joueurs, TOUR,pion2,barriere);
        *coups1=13;
        *blindage=0;
    }
    else{
        //printf("Vous ne pouvez pas aller a gauche\n");
    }
}

void gauche_bot(int tab[SIZE][SIZE], int *ligposition,int *colposition, int *coups1,int pion,int nombre_de_joueurs, char TOUR[20],int barriere,int pion2) {
    if (*colposition>1 && *colposition<=17  && tab[*ligposition][*colposition-1]==0 && tab[*ligposition][*colposition-2]==1) {
        tab[*ligposition][*colposition]=1;
        *colposition=*colposition-2;
        tab[*ligposition][*colposition]=pion;
        modifierCase(tab, *ligposition, *colposition, pion,nombre_de_joueurs, TOUR,pion2,barriere);
        *coups1=6;
    }
    if ((tab[*ligposition][*colposition-2]!=1 &&  tab[*ligposition][*colposition-1]!=0) || *colposition==1){
        //printf("Vous ne pouvez pas aller a droite\n");
    }
    if (tab[*ligposition][*colposition-2]!=1 && *colposition>3 && tab[*ligposition][*colposition-4]==1 && tab[*ligposition][*colposition-3]==0) {
        tab[*ligposition][*colposition]=1;
        *ligposition=*ligposition-4;
        tab[*ligposition][*colposition]=pion;
        modifierCase(tab, *ligposition, *colposition, pion,nombre_de_joueurs, TOUR,pion2,barriere);
        *coups1=13;
    }
    else{
        //printf("Vous ne pouvez pas aller a gauche\n");
    }
}

void coupspecial(int tab[SIZE][SIZE],int *nbcoups,int *ligposition, int *colposition,int *coups2,int *lig,int *col,int pion,int nombre_de_joueurs, char TOUR[20],int barriere,int pion2) {
    if (*coups2==0) {
        printf("Vous ne pouvez pas encore utiliser\n");
    }
    if(*coups2==1) {
        modifierCase(tab, *lig, *col, 98,nombre_de_joueurs, TOUR,pion2,barriere );
        *nbcoups--;
    }
                            if (*coups2==2) {
                                modifierCase(tab, *lig, *col, 0 ,nombre_de_joueurs, TOUR,pion2,barriere);
                                *nbcoups--;
                            }
                            if (*coups2==3) {
                                tab[*ligposition][*colposition]=1;
                                *ligposition=*ligposition-2;
                                //tab[*ligposition][*colposition]=35;
                                modifierCase(tab, *ligposition, *colposition, pion,nombre_de_joueurs, TOUR,pion2,barriere );
                                *nbcoups--;
                            }
                            if (*coups2==4) {
                                tab[*ligposition][*colposition]=1;
                                *ligposition=*ligposition+2;
                                //tab[*ligposition][*colposition]=35;
                                modifierCase(tab, *ligposition, *colposition, pion,nombre_de_joueurs, TOUR,pion2,barriere );
                                *nbcoups--;
                            }
                            if (*coups2==5) {
                                tab[*ligposition][*colposition]=1;
                                *colposition=*colposition-2;
                                //tab[*ligposition][*colposition]=35;
                                modifierCase(tab, *ligposition, *colposition, pion,nombre_de_joueurs, TOUR,pion2,barriere );
                                *nbcoups--;
                            }
                            if (*coups2==6) {
                                tab[*ligposition][*colposition]=1;
                                *colposition=*colposition+2;
                                //tab[*ligposition][*colposition]=35;
                                modifierCase(tab, *ligposition, *colposition, pion ,nombre_de_joueurs, TOUR,pion2,barriere);
                                *nbcoups--;
                            }
                            if (*coups2==10) {
                                tab[*ligposition][*colposition]=1;
                                *ligposition=*ligposition-4;
                                //tab[*ligposition][*colposition]=35;
                                modifierCase(tab, *ligposition, *colposition, pion,nombre_de_joueurs, TOUR,pion2,barriere );
                                *nbcoups--;
                            }


}

void placement_du_pion(int tab[SIZE][SIZE], int *ligposition,int *colposition,int pion,int nombredejoueur,int nombre_de_joueurs, char TOUR[20],int barriere,int pion2) {
    int col,lig,placement = 1;

    if(nombredejoueur>0 && nombredejoueur<=2) {
        while (placement == 1) {
            printf("colonne?\n");
            scanf("%d",&col);
            if (col>=1 && col<18 && col%2==1) {
                placement = 0;
                modifierCase(tab, *ligposition, col, pion,nombre_de_joueurs,TOUR,pion2,barriere);
                *colposition=col;

            }
            else {
                printf("Mauvaise coordonnee\n");
            }
        }
    }
    else if(nombredejoueur>2 && nombredejoueur<=4) {
        while (placement == 1) {
            printf("ligne?\n");
            scanf("%d",&lig);
            if (lig>=1 && lig<18 && lig%2==1) {
                placement = 0;
                modifierCase(tab, lig, *colposition, pion,nombre_de_joueurs, TOUR,pion2,barriere);
                *ligposition=lig;

            }
            else {
                printf("Mauvaise coordonnee\n");
            }
        }
    }

}

void choix_pion(int *pion) {
    int choix;
    int a=1;
    while(a==1) {
        printf("Choisi ton pion");
        printf(" 35 : # ; 36 : $; 38  : &; 64 : @ ");
        scanf("%d",&choix);
        if(choix==35 || choix==36 || choix==38 || choix==64) {
            a=0;
            *pion=choix;
        }
    }
}

void barriere(int tab[SIZE][SIZE],int *coups1,int *lig,int *col,int nombre_de_joueurs, char TOUR[20],int barriere,int pion) {
    int a=1,lig2, col2;
    while(a==1) {
        printf("coordonnee de la ligne puis colonnesss\n");
        scanf("%d %d",&lig2,&col2);
        if(tab[lig2][col2]==98) {
            modifierCase(tab, lig2, col2, 0,nombre_de_joueurs, TOUR,pion,barriere);
            //ab=ab-1;
            a=0;
            *coups1=1;
            *lig=lig2;
            *col=col2;

        }
        else if(tab[lig2][col2]!=98) printf("mauvaise coordonnee\n");
    }
}

void placer_barriere(int tab[SIZE][SIZE],int *lig,int *col,int *coups1,int nombre_de_joueurs, char TOUR[20],int barriere,int pion) {
    int a=1,col2,lig2;
    while(a==1) {
        printf("coordonnee de la ligne puis colonnesss\n");
        scanf("%d %d",&lig2,&col2);
        if(lig2%2==0 && col2%2!=0) {
            modifierCase(tab, lig2, col2, 98,nombre_de_joueurs, TOUR,pion,barriere);
            *lig=lig2;
            *col=col2;
            *coups1=2;
            a=0;
        }
        if(lig2%2!=0 && col2%2==0) {
            a=0;
            modifierCase(tab, lig2, col2, 98,nombre_de_joueurs, TOUR,pion,barriere);
            *lig=lig2;
            *col=col2;
            *coups1=2;
            a=0;
        }
        else if (lig2%2==0 && col2%2==0) printf("mauvaise coordonnee\n");
    }


}

void placement_du_pion_bot(int tab[SIZE][SIZE],int ligposition,int *colposition2,int pion,int nombre_de_joueurs, char TOUR[20],int barriere,int pion2) {
    int col;
    srand(time(NULL));
    col=2 * (rand() % 9) + 1;
    *colposition2=col;
    modifierCase(tab, ligposition, col, pion,nombre_de_joueurs, TOUR,pion2,barriere);

}

void placement_du_pion_bot_3(int tab[SIZE][SIZE],int *ligposition,int colposition,int pion,int nombre_de_joueurs, char TOUR[20],int barriere,int pion2) {
    int lig;
    srand(time(NULL));
    lig=2 * (rand() % 9) + 1;
    *ligposition=lig;
    modifierCase(tab, lig, colposition, pion2,nombre_de_joueurs, TOUR,pion,barriere);

}

void choix_bot(int tab[SIZE][SIZE],int *choix,int ligposition,int colposition,int nbcoupspe,int nbarriere,int choix_coups_bot,int cote,int nombredetour) {
    srand(time(NULL));
    int a;
    a = (rand() % 8) + 1;
    while(1) {
        if (cote == 1 && (a == 7 || a == 8 || a== 3)) {
            if (ligposition == 1 && (a == 3 || a == 7 || a == 8)) {
                a = (rand() % 7) + 4;
                continue;
            }
            if (a == 7 || a == 8) {
                a = (rand() % 8) + 1;
                continue;
            }
        }
        if (nombredetour==1 && a== 1) {
            a = (rand() % 8) + 1;
            continue;

        }
        if (cote == 2 && (a == 7 || a == 8 || a == 5)) {
            if (colposition >= 1 && colposition < 17) {
                a = (rand() % 8) + 1;
                continue;
            } else if (colposition == 17) {
                a =(rand() % 8) + 1;
                continue;
            }
        }
        if (nbcoupspe == 0 && a == 1) {
            a = (rand() % 8) + 2;
            continue;
        }
        if (nbarriere == 0 && a == 2) {
            a = (rand() % 8) + 3;
            continue;
        }
        if (tab[ligposition + 1][colposition] == 98 && a == 3) {
            a = (rand() % 8) + 1;
            continue;
        }
        if (ligposition == 17 && a== 4) {
            a = (rand() % 8) + 1;
            continue;
        }
        if (nbcoupspe ==0 ) {
            if (nbarriere ==0) {
                if (tab[ligposition + 1][colposition] != 98 && ligposition<17) {
                    a=5;

                }
                if (tab[ligposition - 1][colposition] != 98 && ligposition>1) {
                    a=4;

                }
                if (tab[ligposition][colposition+1] != 98 && colposition<17) {
                    a=5;

                }
                else if (tab[ligposition][colposition-1] != 98 && colposition>1) {
                    a=6;
                }
            }
            else {
                a=2;
            }
        }
        *choix=a;
        break;
    }
}

void placer_barriere_bot(int tab[SIZE][SIZE],int *lig,int *col,int *coups1,int nombre_de_joueurs, char TOUR[20],int barriere,int pion) {
    srand(time(NULL));
    int col2,lig2;
    lig2=rand()%17+1;
    if (lig2%2==0) {
        col2=2*(rand()%9)+1;
        modifierCase(tab, lig2, col2, 98,nombre_de_joueurs, TOUR,pion,barriere);
        *lig=lig2;
        *col=col2;
        *coups1=2;
    }
    else if (lig2%2!=0) {
        col2=2*(rand()%8+1);
        modifierCase(tab, lig2, col2, 98,nombre_de_joueurs, TOUR,pion,barriere);
        *lig=lig2;
        *col=col2;
        *coups1=2;
    }

}

void coupspecial_bot(int tab[SIZE][SIZE],int coups1,int lig,int col,int *ligposition,int * colposition, int pion,int nombre_de_joueurs, char TOUR[20],int barriere,int pion2) {
    if (coups1==2) {
        modifierCase(tab, lig, col, 0 ,nombre_de_joueurs, TOUR,pion2,barriere);
    }
    if (coups1==3) { // bas
        tab[*ligposition][*colposition]=1;
        *ligposition=*ligposition-2;
        //tab[*ligposition][*colposition]=35;
        modifierCase(tab, *ligposition, *colposition, pion,nombre_de_joueurs, TOUR,pion2,barriere );
    }
    if (coups1==4) {
        tab[*ligposition][*colposition]=1;
        *ligposition=*ligposition+2;
        //tab[*ligposition][*colposition]=35;
        modifierCase(tab, *ligposition, *colposition, pion,nombre_de_joueurs, TOUR,pion2,barriere );
    }
    if (coups1==5) {
        tab[*ligposition][*colposition]=1;
        *colposition=*colposition-2;
        //tab[*ligposition][*colposition]=35;
        modifierCase(tab, *ligposition, *colposition, pion,nombre_de_joueurs, TOUR,pion2,barriere );
    }
    if (coups1==6) {
        tab[*ligposition][*colposition]=1;
        *colposition=*colposition+2;
        //tab[*ligposition][*colposition]=35;
        modifierCase(tab, *ligposition, *colposition, pion,nombre_de_joueurs, TOUR,pion2,barriere );
    }
    if (coups1==10) { // bas
        tab[*ligposition][*colposition]=1;
        *ligposition=*ligposition-4;
        //tab[*ligposition][*colposition]=35;
        modifierCase(tab, *ligposition, *colposition, pion,nombre_de_joueurs, TOUR,pion2,barriere );
    }
    if (coups1==11) { // bas
        tab[*ligposition][*colposition]=1;
        *ligposition=*ligposition+4;
        //tab[*ligposition][*colposition]=35;
        modifierCase(tab, *ligposition, *colposition, pion,nombre_de_joueurs, TOUR,pion2,barriere );
    }
    if (coups1==12) {
        tab[*ligposition][*colposition]=1;
        *colposition=*colposition-4;
        //tab[*ligposition][*colposition]=35;
        modifierCase(tab, *ligposition, *colposition, pion,nombre_de_joueurs, TOUR,pion2,barriere );
    }
    if (coups1==12) {
        tab[*ligposition][*colposition]=1;
        *colposition=*colposition+4;
        //tab[*ligposition][*colposition]=35;
        modifierCase(tab, *ligposition, *colposition, pion,nombre_de_joueurs, TOUR,pion2,barriere );
    }

}
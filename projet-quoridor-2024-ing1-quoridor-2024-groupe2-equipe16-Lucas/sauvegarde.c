//
// Created by jugue on 30/10/2024.
//

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "sauvegarde.h"
#include <string.h>

#include "game_play.h"
#define SIZE 100

void enregistreur_de_peuso(const char *chaine, const char *nom_fichier) {
    FILE *file = fopen(nom_fichier, "w");
    if (file == NULL) {
        printf("Erreur\n");
        return ;
    }

    fprintf(file, "%s", chaine);
    fclose(file);
}

void modif(char nom_du_fichier[10],char nom_joueur[20]) {
    FILE *f = fopen(nom_du_fichier, "a");
    fprintf(f, "\n%s 0",nom_joueur);
    fclose(f);

}

void modifier_score(char nom_fichier[20],char nom_joueur[20], int resultat) {
    FILE *f = fopen(nom_fichier, "r");
    char donnees[SIZE][SIZE];
    int lignes = 0;
    char temp_nom[SIZE];
    int temp_score;
    if (f) {
        while (fgets(donnees[lignes], SIZE, f) != NULL && lignes < SIZE) {
            donnees[lignes][strcspn(donnees[lignes], "\n")] = 0;
            if (sscanf(donnees[lignes], "%s %d", temp_nom, &temp_score) == 2) {
                if (strcmp(temp_nom, nom_joueur) == 0) {
                    if (resultat==1 && temp_score>=0) {
                        temp_score += 5;
                        sprintf(donnees[lignes], "%s %d", temp_nom,temp_score);
                    }
                    if (temp_score>3 && resultat==-1) {
                        temp_score -= 3;
                        sprintf(donnees[lignes], "%s %d", temp_nom,temp_score);
                    }
                    else if (temp_score<3 && temp_score>=0 && resultat==-1) {
                        temp_score = 0;
                        sprintf(donnees[lignes], "%s %d", temp_nom,temp_score);
                    }

                }
            }
            lignes++;
        }

        fclose(f);
    }
    else {
        printf("ERREUR");
    }
    FILE *fichier = fopen(nom_fichier, "w");

    if (fichier) {
        for (int i = 0; i < lignes; i++) {
            fprintf(f, "%s\n", donnees[i]);
        }
        fclose(f);
    }
    else {
        printf("Erreur : impossible d'ouvrir le fichier (2)");
    }
}

void sauvegarde_historique(char nom_du_fichier[10], char nom_joueur[20],int resultat,int start) {
    char donnee[SIZE];
    int res = 0;
    int existe = 0;
    FILE *f = fopen(nom_du_fichier, "r");
    if (f) {
        while (fscanf(f, "%s", donnee) == 1) {
            res = strcmp(nom_joueur, donnee);
            if (res == 0) {
                existe = 1;
                if (start!=0) {
                    modifier_score(nom_du_fichier, nom_joueur,resultat);
                    printf("%d\n", resultat);
                }
                break;
            }
        }
        fclose(f);
        if (!existe) {
            modif(nom_du_fichier, nom_joueur);
        }
    } else {
        printf("Erreur : impossible d'ouvrir le fichier (1) \n");
    }
}

void create_historique(char nom_du_fichier[20]) {
    FILE *f = fopen(nom_du_fichier, "r");
    if (f == NULL) {
        FILE *fichier = fopen(nom_du_fichier, "a");
        if (fichier == NULL) {
            printf("Erreur lors de la création du fichier.\n");
            return;
        }
        printf("Création d'un fichier classement\n");
        fclose(fichier);
    }
    fclose(f);

}

void recherche_sauvegarde(char nom_du_fichier_sauvegarde[100]) {
    int a=1;
    while (a==1) {
        printf("donner un nom à votre sauvegarde");
        scanf("%s", nom_du_fichier_sauvegarde);
        strcat(nom_du_fichier_sauvegarde, ".txt");
        FILE *f = fopen(nom_du_fichier_sauvegarde, "r");
        if (f) {
            printf("Nom deja utilise, reessaye");
        }
        else  if (f==NULL) {
            a=0;
            FILE *fichier = fopen(nom_du_fichier_sauvegarde, "a");
            fclose(fichier);
            fclose(f);
        }
    }

}

void choix_nom_ordre(char pseudo1[20],char pseudo2[20],char pseudo3[20],char pseudo4[20],char joueurstart[20],char joueursecond[20],char joueurtroisieme[20],char joueurquatrieme[20],char bot1[20], int nombredejoueur, int *joueur1,char nom_du_fichier[20]) {
    int joueur2,joueur3;
    int a=1,b=1,c=1,v=1; // blindage
    //int taille;
    srand(time(NULL));
    if (nombredejoueur == 1) {
        *joueur1= rand()%2 +1 ;
        while (a==1){
            printf("Vous devez entrer votre nom de maximun 18 \n");
            printf("Entrez un pseudo : \n");
            getchar();
            fgets(pseudo1, 20, stdin);
            pseudo1[strlen(pseudo1)-1] = '\0';
            size_t taille = strlen(pseudo1);
            if (taille>18) {
                printf("Vous devez entrer votre nom de maximun 18\n");
                printf("Entrez un pseudo : \n");
                fgets(pseudo1, 20, stdin);

            }
            else if (taille<18) {
                a=0;
                enregistreur_de_peuso(pseudo1, "pseudojoueur1.txt");
            }
        }
        printf("\n");
        if (*joueur1==1) {
            snprintf(joueurstart, 20, "%s", pseudo1);
            snprintf(joueursecond, 20, "%s", bot1);

            printf("le joueur 1 est : %s \n ",joueurstart);
            printf("le joueur 2 est : %s \n ",joueursecond);
            sauvegarde_historique(nom_du_fichier,joueurstart,0,0);
            sauvegarde_historique(nom_du_fichier,joueursecond,0,0);
        }
        else if (*joueur1==2) {
            snprintf(joueurstart, 20, "%s", bot1);
            snprintf(joueursecond, 20, "%s", pseudo1);

            printf("le joueur 1 est : %s \n ",joueurstart);
            printf("le joueur 2 est : %s \n ",joueursecond);
            sauvegarde_historique(nom_du_fichier,joueurstart,0,0);
            sauvegarde_historique(nom_du_fichier,joueursecond,0,0);
        }
    }
    if (nombredejoueur == 2) {
        *joueur1= rand()%2 +1 ;
        while (a==1) {
            printf("Un premier joueur doit entrer son nom\n");
            printf("Entrez un pseudo : \n");
            getchar();
            fgets(pseudo1, 20, stdin);
            pseudo1[strlen(pseudo1)-1] = '\0';
            size_t taille = strlen(pseudo1);
            if (taille>18) {
                printf("Un premier joueur doit entrer son nom de maximun 18 caracteres\n");
                printf("Entrez un pseudo : \n");
                getchar();
                fgets(pseudo1, 20, stdin);

            }
            else if (taille<18) {
                a=0;
                enregistreur_de_peuso(pseudo1, "pseudojoueur1.txt");
            }
        }
        while (b==1) {
            printf("Un deuxieme joueur doit entrer son nom\n");
            printf("Entrez un pseudo : \n");
            fgets(pseudo2, 20, stdin);
            pseudo2[strlen(pseudo2)-1] = '\0';
            size_t taille = strlen(pseudo2);
            if (taille>18) {
                printf("Un deuxieme joueur doit entrer son nom de maximun 18 caracteres\n");
                printf("Entrez un pseudo : \n");
                fgets(pseudo1, 20, stdin);

            }
            else if (taille<18) {
                b=0;
                enregistreur_de_peuso(pseudo1, "pseudojoueur2.txt");
            }
        }
        if (*joueur1==1) {
            snprintf(joueurstart, 20, "%s", pseudo1);
            snprintf(joueursecond, 20, "%s", pseudo2);

            printf("le joueur 1 est : %s \n ",joueurstart);
            printf("le joueur 2 est : %s \n ",joueursecond);
            sauvegarde_historique(nom_du_fichier,joueurstart,0,0);
            sauvegarde_historique(nom_du_fichier,joueursecond,0,0);
        }
        else if (*joueur1==2) {
            snprintf(joueurstart, 20, "%s", pseudo2);
            snprintf(joueursecond, 20, "%s", pseudo1);

            printf("le joueur 1 est : %s \n ",joueurstart);
            printf("le joueur 2 est : %s \n ",joueursecond);
            sauvegarde_historique(nom_du_fichier,joueurstart,0,0);
            sauvegarde_historique(nom_du_fichier,joueursecond,0,0);
        }

    }
    if (nombredejoueur==3) {
        printf("Un premier joueur doit entrer son nom\n");
        printf("Entrez un pseudo : \n");
        getchar();
        fgets(pseudo1, 20, stdin);
        pseudo1[strlen(pseudo1)-1] = '\0';
        enregistreur_de_peuso(pseudo1, "pseudojoueur1.txt");
        printf("Un deuxieme joueur doit entrer son nom\n");
        printf("Entrez un pseudo : \n");
        fgets(pseudo2, 20, stdin);
        pseudo2[strlen(pseudo2)-1] = '\0';
        enregistreur_de_peuso(pseudo2, "pseudojoueur2.txt");
        printf("Un troisieme joueur doit entrer son nom\n");
        printf("Entrez un pseudo : \n");
        fgets(pseudo3, 20, stdin);
        pseudo3[strlen(pseudo3)-1] = '\0';
        enregistreur_de_peuso(pseudo3, "pseudojoueur3.txt");
        snprintf(joueurquatrieme, 20, "%s", bot1);

        *joueur1= rand()%3 +1 ;
        if (*joueur1==1) {
            snprintf(joueurstart, 20, "%s", pseudo1);
            joueur2=rand()%2 +1 ;
            if (joueur2==1) {
                snprintf(joueursecond, 20, "%s", pseudo2);
                snprintf(joueurtroisieme, 20, "%s", pseudo3);
                snprintf(joueurquatrieme, 20, "%s", bot1);
            }
            else if (joueur2==2) {
                snprintf(joueursecond, 20, "%s", pseudo3);
                snprintf(joueurtroisieme, 20, "%s", pseudo2);
                snprintf(joueurquatrieme, 20, "%s", bot1);
            }
        }
        if (*joueur1==2) {
            snprintf(joueurstart, 20, "%s", pseudo2);
            joueur2=rand()%2 +1 ;
            if (joueur2==1) {
                snprintf(joueursecond, 20, "%s", pseudo1);
                snprintf(joueurtroisieme, 20, "%s", pseudo3);
                snprintf(joueurquatrieme, 20, "%s", bot1);
            }
            else if (joueur2==2) {
                snprintf(joueursecond, 20, "%s", pseudo3);
                snprintf(joueurtroisieme, 20, "%s", pseudo1);
                snprintf(joueurquatrieme, 20, "%s", bot1);
            }

        }
        else if (*joueur1==3) {
            snprintf(joueurstart, 20, "%s", pseudo3);
            joueur2=rand()%2 +1 ;
            if (joueur2==1) {
                snprintf(joueursecond, 20, "%s", pseudo1);
                snprintf(joueurtroisieme, 20, "%s", pseudo2);
                snprintf(joueurquatrieme, 20, "%s", bot1);
            }
            else if (joueur2==2) {
                snprintf(joueursecond, 20, "%s", pseudo2);
                snprintf(joueurtroisieme, 20, "%s", pseudo1);
                snprintf(joueurquatrieme, 20, "%s", bot1);
            }

        }
        printf("le joueur 1 est : %s \n ",joueurstart);
        printf("le joueur 2 est : %s \n ",joueursecond);
        printf("le joueur 3 est %s\n",joueurtroisieme);
        printf("le joueur 4 est %s\n",joueurquatrieme);
        sauvegarde_historique(nom_du_fichier,joueurstart,0,0);
        sauvegarde_historique(nom_du_fichier,joueursecond,0,0);
        sauvegarde_historique(nom_du_fichier,joueurtroisieme,0,0);

    }
    if (nombredejoueur == 4) {
        *joueur1= rand()%4 +1 ;
        printf("Un premier joueur doit entrer son nom\n");
        printf("Entrez un pseudo : \n");
        getchar();
        fgets(pseudo1, 20, stdin);
        pseudo1[strlen(pseudo1)-1] = '\0';
        enregistreur_de_peuso(pseudo1, "pseudojoueur1.txt");
        printf("Un deuxieme joueur doit entrer son nom\n");
        printf("Entrez un pseudo : \n");
        fgets(pseudo2, 20, stdin);
        pseudo2[strlen(pseudo2)-1] = '\0';
        enregistreur_de_peuso(pseudo2, "pseudojoueur2.txt");

        printf("Un troisième joueur doit entrer son nom\n");
        printf("Entrez un pseudo : \n");
        fgets(pseudo3, 20, stdin);
        pseudo3[strlen(pseudo3)-1] = '\0';
        enregistreur_de_peuso(pseudo3, "pseudojoueur3.txt");
        printf("Un quatrième joueur doit entrer son nom\n");
        printf("Entrez un pseudo : \n");
        fgets(pseudo4, 20, stdin);
        pseudo4[strlen(pseudo4)-1] = '\0';
        enregistreur_de_peuso(pseudo4, "pseudojoueur4.txt");

        if (*joueur1==1) {

            snprintf(joueurstart, 20, "%s", pseudo1);
            joueur2= rand()%3 +1 ;
            if (joueur2==1) {
                snprintf(joueursecond, 20, "%s", pseudo2);
                joueur3= rand()%2 +1 ;
                if (joueur3==1) {
                    snprintf(joueurtroisieme, 20, "%s", pseudo3);
                    snprintf(joueurquatrieme, 20, "%s", pseudo4);
                }
                else if (joueur3==2) {
                    snprintf(joueurtroisieme, 20, "%s", pseudo3);
                    snprintf(joueurquatrieme, 20, "%s", pseudo4);
                }
            }
            if (joueur2==2) {
                snprintf(joueursecond, 20, "%s", pseudo3);
                joueur3= rand()%2 +1 ;
                if (joueur3==1) {
                    snprintf(joueurtroisieme, 20, "%s", pseudo2);
                    snprintf(joueurquatrieme, 20, "%s", pseudo4);
                }
                else if (joueur3==2) {
                    snprintf(joueurtroisieme, 20, "%s", pseudo4);
                    snprintf(joueurquatrieme, 20, "%s", pseudo2);
                }
            }
            else if (joueur2==3) {
                snprintf(joueursecond, 20, "%s", pseudo4);
                joueur3= rand()%2 +1 ;
                if (joueur3==1) {
                    snprintf(joueurtroisieme, 20, "%s", pseudo2);
                    snprintf(joueurquatrieme, 20, "%s", pseudo3);
                }
                else if (joueur3==2) {
                    snprintf(joueurtroisieme, 20, "%s", pseudo3);
                    snprintf(joueurquatrieme, 20, "%s", pseudo2);
                }
            }

            printf("le joueur 1 est : %s \n ",joueurstart);
            printf("le joueur 2 est : %s \n ",joueursecond);
            printf("le joueur 3 est %s\n",joueurtroisieme);
            printf("le joueur 4 est %s\n",joueurquatrieme);
            sauvegarde_historique(nom_du_fichier,joueurstart,0,0);
            sauvegarde_historique(nom_du_fichier,joueursecond,0,0);
            sauvegarde_historique(nom_du_fichier,joueurtroisieme,0,0);
            sauvegarde_historique(nom_du_fichier,joueurquatrieme,0,0);
        }
        if (*joueur1==2) {
            snprintf(joueurstart, 20, "%s", pseudo2);
            joueur2= rand()%3 +1 ;
            if (joueur2==1) {
                snprintf(joueursecond, 20, "%s", pseudo3);
                joueur3= rand()%2 +1 ;
                if (joueur3==1) {
                    snprintf(joueurtroisieme, 20, "%s", pseudo1);
                    snprintf(joueurquatrieme, 20, "%s", pseudo4);
                }
                else if (joueur3==2) {
                    snprintf(joueurtroisieme, 20, "%s", pseudo4);
                    snprintf(joueurquatrieme, 20, "%s", pseudo1);
                }
            }
            if (joueur2==2) {
                snprintf(joueursecond, 20, "%s", pseudo1);
                joueur3= rand()%2 +1 ;
                if (joueur3==1) {
                    snprintf(joueurtroisieme, 20, "%s", pseudo3);
                    snprintf(joueurquatrieme, 20, "%s", pseudo4);
                }
                else if (joueur3==2) {
                    snprintf(joueurtroisieme, 20, "%s", pseudo4);
                    snprintf(joueurquatrieme, 20, "%s", pseudo3);
                }
            }
            else if (joueur2==3) {
                snprintf(joueursecond, 20, "%s", pseudo4);
                joueur3= rand()%2 +1 ;
                if (joueur3==1) {
                    snprintf(joueurtroisieme, 20, "%s", pseudo1);
                    snprintf(joueurquatrieme, 20, "%s", pseudo3);
                }
                else if (joueur3==2) {
                    snprintf(joueurtroisieme, 20, "%s", pseudo3);
                    snprintf(joueurquatrieme, 20, "%s", pseudo1);
                }
            }


            printf("le joueur 1 est : %s \n ",joueurstart);
            printf("le joueur 2 est : %s \n ",joueursecond);
            printf("le joueur 3 est %s\n",joueurtroisieme);
            printf("le joueur 4 est %s\n",joueurquatrieme);
            sauvegarde_historique(nom_du_fichier,joueurstart,0,0);
            sauvegarde_historique(nom_du_fichier,joueursecond,0,0);
            sauvegarde_historique(nom_du_fichier,joueurtroisieme,0,0);
            sauvegarde_historique(nom_du_fichier,joueurquatrieme,0,0);
        }

        if (*joueur1==3) {
            snprintf(joueurstart, 20, "%s", pseudo3);
            joueur2= rand()%3 +1 ;
            if (joueur2==1) {
                snprintf(joueursecond, 20, "%s", pseudo1);
                joueur3= rand()%2 +1 ;
                if (joueur3==1) {
                    snprintf(joueurtroisieme, 20, "%s", pseudo2);
                    snprintf(joueurquatrieme, 20, "%s", pseudo4);
                }
                else if (joueur3==2) {
                    snprintf(joueurtroisieme, 20, "%s", pseudo4);
                    snprintf(joueurquatrieme, 20, "%s", pseudo2);
                }
            }
            if (joueur2==2) {
                snprintf(joueursecond, 20, "%s", pseudo2);
                joueur3= rand()%2 +1 ;
                if (joueur3==1) {
                    snprintf(joueurtroisieme, 20, "%s", pseudo1);
                    snprintf(joueurquatrieme, 20, "%s", pseudo4);
                }
                else if (joueur3==2) {
                    snprintf(joueurtroisieme, 20, "%s", pseudo4);
                    snprintf(joueurquatrieme, 20, "%s", pseudo1);
                }
            }
            else if (joueur2==3) {
                snprintf(joueursecond, 20, "%s", pseudo4);
                joueur3= rand()%2 +1 ;
                if (joueur3==1) {
                    snprintf(joueurtroisieme, 20, "%s", pseudo1);
                    snprintf(joueurquatrieme, 20, "%s", pseudo2);
                }
                else if (joueur3==2) {
                    snprintf(joueurtroisieme, 20, "%s", pseudo2);
                    snprintf(joueurquatrieme, 20, "%s", pseudo1);
                }
            }

            printf("le joueur 1 est : %s \n ",joueurstart);
            printf("le joueur 2 est : %s \n ",joueursecond);
            printf("le joueur 3 est %s\n",joueurtroisieme);
            printf("le joueur 4 est %s\n",joueurquatrieme);
            sauvegarde_historique(nom_du_fichier,joueurstart,0,0);
            sauvegarde_historique(nom_du_fichier,joueursecond,0,0);
            sauvegarde_historique(nom_du_fichier,joueurtroisieme,0,0);
            sauvegarde_historique(nom_du_fichier,joueurquatrieme,0,0);
        }
        else if (*joueur1==4) {
            snprintf(joueurstart, 20, "%s", pseudo4);
            joueur2= rand()%3 +1 ;
            if (joueur2==1) {
                snprintf(joueursecond, 20, "%s", pseudo3);
                joueur3= rand()%2 +1 ;
                if (joueur3==1) {
                    snprintf(joueurtroisieme, 20, "%s", pseudo1);
                    snprintf(joueurquatrieme, 20, "%s", pseudo2);
                }
                else if (joueur3==2) {
                    snprintf(joueurtroisieme, 20, "%s", pseudo2);
                    snprintf(joueurquatrieme, 20, "%s", pseudo1);
                }
            }
            if (joueur2==2) {
                snprintf(joueursecond, 20, "%s", pseudo1);
                joueur3= rand()%2 +1 ;
                if (joueur3==1) {
                    snprintf(joueurtroisieme, 20, "%s", pseudo3);
                    snprintf(joueurquatrieme, 20, "%s", pseudo2);
                }
                else if (joueur3==2) {
                    snprintf(joueurtroisieme, 20, "%s", pseudo2);
                    snprintf(joueurquatrieme, 20, "%s", pseudo3);
                }
            }
            else if (joueur2==3) {
                snprintf(joueursecond, 20, "%s", pseudo2);
                joueur3= rand()%2 +1 ;
                if (joueur3==1) {
                    snprintf(joueurtroisieme, 20, "%s", pseudo1);
                    snprintf(joueurquatrieme, 20, "%s", pseudo3);
                }
                else if (joueur3==2) {
                    snprintf(joueurtroisieme, 20, "%s", pseudo3);
                    snprintf(joueurquatrieme, 20, "%s", pseudo1);
                }
            }

            printf("le joueur 1 est : %s \n ",joueurstart);
            printf("le joueur 2 est : %s \n ",joueursecond);
            printf("le joueur 3 est %s \n",joueurtroisieme);
            printf("le joueur 4 est %s \n",joueurquatrieme);
            sauvegarde_historique(nom_du_fichier,joueurstart,0,0);
            sauvegarde_historique(nom_du_fichier,joueursecond,0,0);
            sauvegarde_historique(nom_du_fichier,joueurtroisieme,0,0);
            sauvegarde_historique(nom_du_fichier,joueurquatrieme,0,0);
        }

    }

}

void plateau_sauvegarde(int tab[18][18],char nom_du_fichier[30],char joueurstart[20],int pionj1,int nbarrierej1,char joueursecond[20],int pionj2,int nbarrierej2,char joueurtroisieme[20],int pionj3,int nbarrierej3,char joueurquatrieme[20],int pionj4,int nbarrierej4,int mode,int nombredejoueur,int ligposition ,int colposition,int ligposition2 ,int colposition2,int ligposition3 ,int colposition3,int  ligposition4 ,int colposition4,int joueur1) {
    FILE *f=fopen(nom_du_fichier,"w");
    if(f) {
        for(int i=0;i<19;i++) {
            for(int j=0;j<=30;j++) {
                if(tab[i][j]==98 || tab[i][j]==64 || tab[i][j]==35 || tab[i][j]==36 || tab[i][j]==38 || tab[i][j]==39) {
                    fprintf(f,"%d %d %d\n",tab[i][j],i,j);
                }
                if (i==18 && j==18) {
                    fprintf(f,"%s %d %d %d %d %s %d %d %d %d %s %d %d %d %d %s %d %d %d %d %d %d %d\n",joueurstart,pionj1,nbarrierej1,ligposition,colposition,joueursecond,pionj2,nbarrierej2,ligposition2,colposition2,joueurtroisieme,pionj3,nbarrierej3,ligposition3,colposition3,joueurquatrieme,pionj4,nbarrierej4,ligposition4,colposition4,mode,nombredejoueur,joueur1);
                }
            }
        }
    }
    fclose(f);
}

void lire_plateau_sauvegarde(char nom_du_fichier[30],int tab[18][18], char joueurstart[20],int *pionj1,int *nbarrierej1,char joueursecond[20],int *pionj2,int *nbarrierej2,char joueurtroisieme[20],int *pionj3,int *nbarrierej3,char joueurquatrieme[20],int *pionj4,int *nbarrierej4,int *mode,int *nombredejoueurs,int *ligposition ,int *colposition,int *ligposition2 ,int *colposition2,int *ligposition3 ,int *colposition3,int  *ligposition4 ,int *colposition4,int joueur1) {
    int valeur,i,j;
    FILE *f=fopen(nom_du_fichier,"r");
    if (f) {
        while(fscanf(f,"%d %d %d",&valeur,&i,&j)==3) {
            tab[i][j]=valeur;
            plateau_repair(tab,i,j,valeur);
        }
        while(fscanf(f,"%s %d %d %d %d %s %d %d %d %d %s %d %d %d %d %s %d %d %d %d %d %d %d",joueurstart,pionj1,nbarrierej1,ligposition,colposition,joueursecond,pionj2,nbarrierej2,ligposition2,colposition2,joueurtroisieme,pionj3,nbarrierej3,ligposition3,colposition3,joueurquatrieme,pionj4,nbarrierej4,ligposition4,colposition4,mode,nombredejoueurs,joueur1)==23) {

        }
    }
    else if (f==NULL) {
        printf("fichier inexsistant\n");
    }
}


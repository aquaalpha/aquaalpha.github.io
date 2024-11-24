//
// Created by jugue on 31/10/2024.
//

#include "historique.h"
#include <string.h>
#include <stdio.h>

void afficher_classment(char nom_du_fichier[20]) {
    char historique[300];
    FILE *fichier = fopen(nom_du_fichier, "r");
    if(fichier) {
        while(fscanf(fichier, "%s", historique) == 1) {
            printf("%s\n", historique);
        }
        fclose(fichier);
    }

}

void lire_score(int *score ,char nom_du_joueur[20]) {
    int a;
    char nom_du_fichier[20] = "classement.txt";
    char pseudos[20];
    FILE *fichier = fopen(nom_du_fichier, "r");
    if(fichier) {
        while(fscanf(fichier, "%s %d", pseudos ,&a) ==2) {
            if (strcmp(pseudos, nom_du_joueur) == 0) {
                *score=a;
                fclose(fichier);
                return;
            }
        }
        fclose(fichier);
    }
    fclose(fichier);
    *score = 0;  // Score par défaut si le joueur n'est pas trouvé
}




#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nom[50];
    char numero[20];
} Contact;

// Prototypes des fonctions
void rechercheContact(Contact *annuaire, int compte, const char *numero);
void supprimerContact(Contact *annuaire, int *compte, const char *numero);
void modificationContact(Contact *annuaire, int compte);
void ajouterContact(Contact **annuaire, int *taille, int *compte, const char *nom, const char *numero);
void afficherAnnuaire(Contact *annuaire, int compte);
char *strcpy(char *dest, const char *src);


// Fonctions
void afficherAnnuaire(Contact *annuaire, int compte) {
    printf("\nAnnuaire:\n");
    for (int i = 0; i < compte; i++) {
        printf("Contact %d: %s - %s\n", i + 1, annuaire[i].nom, annuaire[i].numero);
    }
}
void ajouterContact(Contact **annuaire, int *taille, int *compte, const char *nom, const char *numero) {
    // Vérifier si l'annuaire est plein
    if (*compte >= *taille) {
        // Augmenter la taille de l'annuaire
        *taille *= 2;
        Contact *nouveau_annuaire = realloc(*annuaire, (*taille) * sizeof(Contact));
        if (!nouveau_annuaire) {
            perror("Erreur de reallocation");
            exit(EXIT_FAILURE);
        }
        *annuaire = nouveau_annuaire;
    }
    // Ajouter le nouveau contact
    strcpy((*annuaire)[*compte].nom, nom);
    strcpy((*annuaire)[*compte].numero, numero);
    (*compte)++;
}

void modificationContact(Contact *annuaire, int compte) {
    printf("Entrez le numero du contact a modifier: ");
    char numero[20];
    scanf("%s", numero);
    for (int i = 0; i < compte; i++) {
        if (strcmp(annuaire[i].numero, numero) == 0) {
            printf("Entrez le nouveau nom: ");
            scanf("%s", annuaire[i].nom);
            printf("Entrez le nouveau numero: ");
            scanf("%s", annuaire[i].numero);
            return;
        }
    }
}

void supprimerContact(Contact *annuaire, int *compte, const char *numero) {
    for (int i = 0; i < *compte; i++) {
        if (strcmp(annuaire[i].numero, numero) == 0) {
            for (int j = i; j < *compte - 1; j++) {
                annuaire[j] = annuaire[j + 1];
            }
            (*compte)--;
            return;
        }
    }
    printf("Contact introuvable!\n");
}


void rechercheContact(Contact *annuaire, int compte, const char *numero) {
    for (int i = 0; i < compte; i++) {
        if (strcmp(annuaire[i].numero, numero) == 0) {
            printf("Contact %d: %s - %s\n", i + 1, annuaire[i].nom, annuaire[i].numero);
            return;
        }
    }
    printf("Contact introuvable!\n");
}



int main() {
    int choix;
    int taille = 10; // Taille initiale de l'annuaire
    int compte = 0; // Nombre actuel de contacts dans l'annuaire
    Contact *annuaire = NULL; // Pointeur vers le tableau de contacts
    char nom[50];
    char numero[20];

    // Allocation initiale
    annuaire = (Contact *)malloc(taille * sizeof(Contact));
    if (!annuaire) {
        perror("Erreur d'allocation initiale");
        exit(EXIT_FAILURE);
    }


    printf("1. Ajouter un contact!\n");
    printf("2. Modifier un contact!\n");
    printf("3. Supprimer un contact!\n");
    printf("4. Afficher un contact!\n");
    printf("5. Rechercher un contact!\n");
    printf("6. Quitter!\n");




    do{
        printf("Entrez votre choix: ");
        scanf("%d", &choix);

        switch(choix){

            case 1:
            printf("Entrez le nom du contact: ");
            scanf("%s", nom);
            printf("Entrez le numero du contact: ");
            scanf("%s", numero);
            ajouterContact(&annuaire, &taille, &compte, nom, numero);
            break;
            case 2:
            modificationContact(annuaire, compte);
            break;
            case 3:
            printf("Entrez le numero du contact a supprimer: ");
            char numero[20];
            scanf("%s", numero);
            supprimerContact(annuaire, &compte, numero);
            break;
            case 4:
            afficherAnnuaire(annuaire, compte);
            break;
            case 5:
            printf("Entrez le numero du contact a rechercher: ");
            scanf("%s", numero);
            rechercheContact(annuaire, compte, numero);
            break;
            case 6:
            printf("Au revoir!\n");
            break;
            default:
            printf("Choix invalide!\n");
        }
        }       while (choix != 6);

    // Libération de la mémoire
    free(annuaire);
    return 0;
}
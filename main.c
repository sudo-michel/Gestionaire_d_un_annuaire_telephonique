#include <stdio.h>
#include <stdlib.h>



typedef struct {
    char nom[50];
    char numero[20];
} Contact;

// Prototypes des fonctions
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


int main() {
    int choix;

    printf("1. Ajouter un contact!\n");
    printf("2. Modifier un contact!\n");
    printf("3. Supprimer un contact!\n");
    printf("4. Afficher un contact!\n");
    printf("5. Rechercher un contact!\n");
    printf("6. Quitter!\n");

    scanf("%d", &choix);
    printf("Vous avez choisi: %d\n", choix);

    Contact *annuaire = NULL; // Pointeur vers le tableau de contacts
    int taille = 10; // Taille initiale de l'annuaire
    int compte = 0; // Nombre actuel de contacts dans l'annuaire

    // Allocation initiale
    annuaire = (Contact *)malloc(taille * sizeof(Contact));
    if (!annuaire) {
        perror("Erreur d'allocation initiale");
        exit(EXIT_FAILURE);
    }

    int action;
    if (choix == 1) {
        printf("Entrez le nom du contact: ");
        char nom[50];
        scanf("%s", nom);
        printf("Entrez le numero du contact: ");
        char numero[20];
        scanf("%s", numero);
        ajouterContact(&annuaire, &taille, &compte, nom, numero);
    }else if
    (choix == 4) {
        afficherAnnuaire(annuaire, compte);
    }
    // Ajout de contacts
    ajouterContact(&annuaire, &taille, &compte, "Alice", "123456789");
    ajouterContact(&annuaire, &taille, &compte, "Bob", "987654321");

    // Affichage de l'annuaire
    afficherAnnuaire(annuaire, compte);



    return 0;
}

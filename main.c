#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main() {
  // Initialize the array of accounts
  int NC = 0;

  // Display the menu and get the user's choice
  int choix = menu();

  while (choix != 0) {
    switch (choix) {
      case 1:
{
    Compte C;
    getchar();
    CreerCompte(&C);
    AjouterCompte(T_Compte, &NC, C);
    break;
}
      case 2:
        // Display the accounts
        ListeComptes(T_Compte, NC);
        break;
      case 3:
        // Add or remove money from an account
        printf("RIB du compte : ");
        int RIB;
        scanf("%d", &RIB);
        printf("Somme à ajouter ou retirer : ");
        float M;
        scanf("%f", &M);
        float solde = Ajouter_Retirer(T_Compte, NC, M, RIB);
        if (solde != -1) {
          printf("Nouveau solde : %.2f\n", solde);
        }
        break;
      case 4:
        // Attribute a prize to the best accounts
        Prime(T_Compte, NC);
        break;
    }

    // Display the menu and get the user's choice again
    choix = menu();
  }

  printf("Au revoir !\n");
  return 0;
}

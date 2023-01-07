#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int menu() {
  int choix;

  printf("\n\n                        ->  Menu  <- \n\n");

  printf("         1 - Ajouter un Nouveau Compte \n");
  printf("         2 - Afficher  les comptes de la banque \n");
  printf("         3 - Ajouter une operation a un compte\n");
  printf("         4 - Attribuer une prime aux meilleurs comptes bancaires \n");
  printf("         0 - Quitte\n");
  printf("\n         --------------------------------------\n");
  do {
    printf("            -> Tapez votre choix :   ");
    scanf("%d",&choix);
    printf("\n\n");
  } while (choix>4 || choix<0);
  return choix;
}

void CreerCompte(Compte *C) {
  printf("RIB du compte : ");
  scanf("%d", &C->RIB);
  printf("Solde initial du compte (supérieur ou égal à 50) : ");
  scanf("%f", &C->solde);
  while (C->solde < 50) {
    printf("Le solde initial doit être supérieur ou égal à 50 !\n");
    printf("Solde initial du compte (supérieur ou égal à 50) : ");
    scanf("%f", &C->solde);
  }
  strcpy(C->etat, "debiteur");
  printf("Plafond de crédit du compte (strictement négatif supérieur à -500) : ");
  scanf("%f", &C->plafond_credit);
  while (C->plafond_credit >= 0 || C->plafond_credit <= -500) {
    printf("Le plafond de crédit doit être un montant strictement négatif supérieur à -500 !\n");
    printf("Plafond de crédit du compte (strictement négatif supérieur à -500) : ");
    scanf("%f", &C->plafond_credit);
  }
  C->nb_operations = 0;
}

int ChercherCompte(Compte T_Compte[], int NC, int RIB) {
  for (int i = 0; i < NC; i++) {
    if (T_Compte[i].RIB == RIB) {
      return i;
    }
  }
  return -1;
}
void AjouterCompte(Compte T_Compte[], int *NC, Compte C) {
  if (ChercherCompte(T_Compte, *NC, C.RIB) != -1) {
    printf("Un compte avec ce RIB existe déjà !\n");
    return;
  }
  T_Compte[*NC] = C;
  (*NC)++;
}

float Ajouter_Retirer(Compte T_Compte[], int NC, float M, int RIB) {
  // Vérifie que la somme à ajouter ou retirer est non nulle
  if (M == 0) {
    printf("La somme à ajouter ou retirer ne peut pas être nulle !\n");
    return -1;
  }
  // Cherche le compte dans le tableau
  int pos = ChercherCompte(T_Compte, NC, RIB);
  // Vérifie que le compte existe
  if (pos == -1) {
    printf("Le compte avec le RIB spécifié n'existe pas !\n");
    return -1;
  }
  Compte C = T_Compte[pos];
  // Vérifie que l'opération de retrait peut être effectuée
  if (M < 0 && (C.solde + M < -C.plafond_credit)) {
    printf("Opération de retrait impossible !\n");
    return -1;
  }
  // Effectue l'opération
  C.solde += M;
  C.nb_operations++;
  T_Compte[pos] = C;
  return C.solde;
}

void ListeComptes(Compte T_Compte[], int NC) {
  printf("Liste des comptes de la banque :\n");
  for (int i = 0; i < NC; i++) {
    Compte C = T_Compte[i];
    printf("RIB : %d, Solde : %.2f, Etat : %s, Plafond de crédit : %.2f, Nombre d'opérations : %d\n",
           C.RIB, C.solde, C.etat, C.plafond_credit, C.nb_operations);
  }
}
void StatCompte(Compte T_Compte[], int NC, int *PNBA, int *PNBR, int RIB) {
  // Initialise les compteurs à 0
  *PNBA = 0;
  *PNBR = 0;
  // Cherche le compte dans le tableau
  int pos = ChercherCompte(T_Compte, NC, RIB);
  if (pos == -1) {
    printf("Le compte avec ce RIB n'existe pas !\n");
    return;
  }
  // Parcours les opérations du compte
  Compte C = T_Compte[pos];
  for (int i = 0; i < C.nb_operations; i++) {
    if (C.operations[i] > 0) {
      (*PNBA)++;
    } else if (C.operations[i] < 0) {
      (*PNBR)++;
    }
  }
}


void Prime(Compte T_Compte[], int NC) {
  printf("Attribution de la prime aux meilleurs comptes de la banque :\n");
  for (int i = 0; i < NC; i++) {
    Compte C = T_Compte[i];
    // Vérifie que le compte est débiteur
    if (strcmp(C.etat, "debiteur") == 0) {
      int nb_ajout = 0;
      int nb_retrait = 0;
      // Parcours les opérations du compte pour compter le nombre d'opérations d'ajout et de retrait
      for (int j = 0; j < C.nb_operations; j++) {
        if (C.operations[j] > 0) {
          nb_ajout++;
        } else if (C.operations[j] < 0) {
          nb_retrait++;
        }
      }
      // Vérifie que le nombre d'opérations d'ajout est supérieur aux nombres d'opérations de retrait
      if (nb_ajout > nb_retrait) {
        float prime = (C.solde / C.nb_operations) * 0.5;
        printf("RIB : %d - Prime : %.2f\n", C.RIB, prime);
      }
    }
  }
}


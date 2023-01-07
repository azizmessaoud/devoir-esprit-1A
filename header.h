#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#define TAILLE_MAX_NOM 50

// Définition du type Compte
typedef struct {
  int RIB;
  float solde;
  char etat[TAILLE_MAX_NOM];
  float plafond_credit;
  int nb_operations;
  float operations[100];
} Compte;
Compte T_Compte[100];


int menu();
void CreerCompte(Compte *C);
int ChercherCompte(Compte T_Compte[],int NC,int RIB );
void AjouterCompte (Compte T_Compte[], int *NC, Compte C);
float Ajouter_Retirer (Compte T_Compte[], int NC, float M,int RIB);
void ListeComptes(Compte T_Compte[], int NC);
void StatCompte (Compte T_Compte[], int NC, int *PNBA,int *PNBR ,int RIB);
void Prime (Compte T_Compte[], int NC);



#endif // HEADER_H_INCLUDED

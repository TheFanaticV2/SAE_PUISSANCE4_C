#include <stdio.h>

#define TAILLE_GRILLE 6

//Initialisation des fonction
int hauteur_colonne ( int grille[TAILLE_GRILLE][TAILLE_GRILLE], int colonne );
int poser_jeton (int grille[TAILLE_GRILLE][TAILLE_GRILLE], int colonne, int joueur);
void init_grille (int grille[TAILLE_GRILLE][TAILLE_GRILLE]);
void affiche_grille (int grille[TAILLE_GRILLE][TAILLE_GRILLE]);
int scan_colonne (int grille[TAILLE_GRILLE][TAILLE_GRILLE]);
int verifie_gagne (int grille[TAILLE_GRILLE][TAILLE_GRILLE], int colonne, int ligne, int joueur);
int verifie_gagne_horizontal (int grille[TAILLE_GRILLE][TAILLE_GRILLE], int colonne, int ligne, int joueur);
int verifie_gagne_vertical (int grille[TAILLE_GRILLE][TAILLE_GRILLE], int colonne, int ligne, int joueur);
int verifie_gagne_diagonal1 (int grille[TAILLE_GRILLE][TAILLE_GRILLE], int colonne, int ligne, int joueur);
int verifie_gagne_diagonal2 (int grille[TAILLE_GRILLE][TAILLE_GRILLE], int colonne, int ligne, int joueur);

//Main
int main () {
	int victoire = 0;
    int nbCoups = 0;
    int colonne, ligne;
	int grille[TAILLE_GRILLE][TAILLE_GRILLE];

	init_grille (grille);
	affiche_grille (grille);

    while (victoire == 0 && nbCoups < TAILLE_GRILLE * TAILLE_GRILLE) {
        nbCoups++;
        colonne = scan_colonne(grille);
        ligne = poser_jeton (grille, colonne, 1);
        victoire = verifie_gagne (grille, colonne, ligne, 1);
        affiche_grille (grille);

        if (victoire == 0) {
            nbCoups++;
            colonne = scan_colonne(grille);
            ligne = poser_jeton (grille, colonne, 2);
            victoire = verifie_gagne (grille, colonne, ligne, 2);
            affiche_grille (grille);
        }
    
    }
    if (victoire == 0)
        printf("Vous avez fait égalité !\n");
    else
        printf("Victoire de : %d !\n", victoire);
}


//Initialisation de la grille  avec des 0
void init_grille(int grille[TAILLE_GRILLE][TAILLE_GRILLE]){
	 for(int i=0; i<TAILLE_GRILLE;i++){
		 for(int j=0; j<TAILLE_GRILLE;j++){
			 grille[i][j] = 0;
		 }
    }
}

//affuchage de la grille avec des X, O, ou des éspaces
void affiche_grille(int grille[TAILLE_GRILLE][TAILLE_GRILLE]){
	for (int i = TAILLE_GRILLE-1; i >=0; i--) {
		printf("|");
        for (int j = 0; j < TAILLE_GRILLE; j++) {
			switch (grille[i][j])
			{
			
			case 0:
				printf(" ");

				break;
			
			case 1:
				printf("X");

				break;
			
			case 2:
				printf("O");

				break;
			}
			printf("|");
		}
			
	printf("\n");

    }
}

//Obtenir la hauteur de la colonne passer en argument
int hauteur_colonne (int grille[TAILLE_GRILLE][TAILLE_GRILLE], int colonne ){
int hauteurCompteur = 0;
	while(hauteurCompteur < TAILLE_GRILLE & grille[hauteurCompteur][colonne] != 0){
		hauteurCompteur++;
	}

	return hauteurCompteur;
}

//Pose de jetons et gestion de quelques erreurs
int poser_jeton(int grille[TAILLE_GRILLE][TAILLE_GRILLE], int colonne, int joueur){
int hauteur = hauteur_colonne(grille, colonne);

	if (joueur !=1 & joueur != 2){
		return -1;
		}
	else if (colonne < 0 | colonne > 5){
		return -2;
		}
	else if(hauteur == TAILLE_GRILLE){
		return -3;
	}
	else{
		grille[hauteur][colonne]=joueur;
	}
	return hauteur;
	
}

//Demande de la colonne ou le joueur veut jouer 
int scan_colonne (int grille[TAILLE_GRILLE][TAILLE_GRILLE]){
    int colonne;
	printf("Dans quel colonne voulez vous jouer ?");
	scanf("%d",&colonne);
		while(colonne < 0 | colonne >= TAILLE_GRILLE){
            printf("Erreur ! : Dans quel colonne voulez vous jouer ?\n");
		    scanf("%d",&colonne);
	}
	return colonne;
}

//Verification de la victoire d'une personne
int verifie_gagne (int grille[TAILLE_GRILLE][TAILLE_GRILLE], int colonne, int ligne, int joueur) {
	int victoire;

    victoire = verifie_gagne_horizontal (grille, colonne, ligne, joueur);
    if (victoire == 0)
        victoire = verifie_gagne_vertical (grille, colonne, ligne, joueur);
    if (victoire == 0)
        victoire = verifie_gagne_diagonal1 (grille, colonne, ligne, joueur);
    if (victoire == 0)
        victoire = verifie_gagne_diagonal2 (grille, colonne, ligne, joueur);

    return victoire;
}

//Verification de l'origine de la victoire

//Verification d'une victoire horizontale
int verifie_gagne_horizontal (int grille[TAILLE_GRILLE][TAILLE_GRILLE], int colonne, int ligne, int joueur) {
	int i;
    int compteur_Alignement = 1;

    i = 1;
    while (colonne - i >= 0 && compteur_Alignement < 4 && grille[ligne][colonne - i] == joueur) {
        compteur_Alignement++; 
        i++;
    }

    i = 1;
    while (colonne + i < TAILLE_GRILLE && compteur_Alignement < 4 && grille[ligne][colonne + i] == joueur) {
        compteur_Alignement++; 
        i++;
    }

    if (compteur_Alignement == 4)
        return joueur;
    else
        return 0;
}

//Verification d'une victoire vertical
int verifie_gagne_vertical (int grille[TAILLE_GRILLE][TAILLE_GRILLE], int colonne, int ligne, int joueur) {
	int compteur_Alignement = 1;

	while (ligne - compteur_Alignement >= 0 && compteur_Alignement < 4 && grille[ligne - compteur_Alignement][colonne] == joueur) {
            compteur_Alignement++;
        }

        if (compteur_Alignement == 4)
            return joueur;
        else
            return 0;
}

//Verification d'une victoire diagonale (deplacement en bas a droite et en haut a gauche)
int verifie_gagne_diagonal1 (int grille[TAILLE_GRILLE][TAILLE_GRILLE], int colonne, int ligne, int joueur) {
	int i;
    int compteur_Alignement = 1;

    i = 1;
    while (ligne + i <= TAILLE_GRILLE - 1 && ligne - i >= 0 && compteur_Alignement < 4 && grille[ligne + i][colonne - i] == joueur) {
        compteur_Alignement++; 
        i++;
    }

    i = 1;
    while (ligne - i >= 0 && colonne + i < TAILLE_GRILLE && compteur_Alignement < 4 && grille[ligne - i][colonne + i] == joueur) {
        compteur_Alignement++; 
        i++;
    }

    if (compteur_Alignement == 4)
        return joueur;
    else
        return 0;
}

//Verification d'une victoire diagonale (deplacement en bas a gauche et en haut a droite)
int verifie_gagne_diagonal2 (int grille[TAILLE_GRILLE][TAILLE_GRILLE], int colonne, int ligne, int joueur) {
	int i;
    int compteur_Alignement = 1;

    i = 1;
    while (ligne + i < TAILLE_GRILLE && colonne + i < TAILLE_GRILLE && compteur_Alignement < 4 && grille[ligne + i][colonne + i] == joueur) {
		compteur_Alignement++; 
        i++;
    }

    i = 1;
    while (ligne - i >= 0 && colonne - i >= 0 && compteur_Alignement < 4 && grille[ligne - i][colonne - i] == joueur) {
        compteur_Alignement++; 
        i++;
    }

    if (compteur_Alignement == 4)
        return joueur;
    else
        return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int LIGNES = 6/*7 pour les numéros de colonnes*/;
const int COLONNES = 7;
const int PUISSANCES = 4;
const char CASE_VIDE = '.';
const char SYMB_P1 = 'X';
const char SYMB_P2 = 'O';

void creerGrille(char cara, char tabMorp[LIGNES][COLONNES]){
    int i, j;
    int numCol=1;
    for (i=0; i < LIGNES; i++)
    {
        for (j=0; j < COLONNES; j++)
            {
                tabMorp[i][j] = cara;
            }
    }
/* numéro des colonnes   for(int lig=0;lig<1;lig++){
        for (int col = 0; col < COLONNES+1; col++)
        {
            if(lig=0){
                char numero = numCol;
                tabMorp[lig][col]=numero;
                numCol++;
            }
        }
    }*/
}

void affichage(char grille[LIGNES][COLONNES]){
    int i, j;
    for (i=0; i<LIGNES; i++)
    {
        for (j=0; j<COLONNES; j++)
            putchar(grille[i][j]);
        putchar('\n');
    }
}   

void posCoord(int inputUser, char coord, char grille[LIGNES][COLONNES]){
    int cpt=0;
    for(int x = 0; x<LIGNES;x++){
        for(int y = 0; y<inputUser+1;y++){
            if(x==LIGNES-1 && y ==inputUser-1){
                if(grille[x][y]!='.'){
                    while(grille[x-cpt][y]!='.')
                    {
                        if(cpt<LIGNES)
                            cpt++;
                        else{
                            printf("La colonne est complète\n");
                            break;
                        }
                    }
                    grille[x-cpt][y]=coord;
                    break;
                }
                else{
                    grille[x][y]=coord;
                    break;
                    }
            }
        }
    }
    printf("nouvelle grille...\n");
    affichage(grille);
}

int cptSymbole(char posActu, char next){
    int cpt = 0;
    //char symbole = tab[LIGNES][COLONNES];
    if(/*symbole*/posActu == SYMB_P1 || posActu == SYMB_P2){
        if(/*symbole*/posActu == next){
            cpt++;
        }
    }
    return cpt;
}

//tab[lig-1][col-1];
int checkIfWin(char tab[LIGNES][COLONNES], int typePartie){
    int cpt_lig=1;
    int cpt_col=1;
    int cpt_diag_dr=1;
    int cpt_diag_ga=1;
    for(int lig = LIGNES-1; lig>=0;lig--){
        for(int col = 0; col<=COLONNES-1;col++){
            char position=tab[lig][col];
            if(cptSymbole(position,tab[lig][col+1])==0){
                cpt_lig=1;
            }
            else{
            cpt_lig+=cptSymbole(position, tab[lig][col+1]);}
            if(position==SYMB_P1 || position == SYMB_P2){
                int cpt=1;
                int count_diag_dr=1;
                int count_diag_ga=1;
                while (tab[lig-cpt][col]==SYMB_P1||tab[lig-cpt][col]==SYMB_P2){
                    cpt_col+= cptSymbole(position,tab[lig-cpt][col]);
                    cpt++;//}
                }

                while(tab[lig-count_diag_dr][col+count_diag_dr]==SYMB_P1 || tab[lig-count_diag_dr][col+count_diag_dr]==SYMB_P2){
                    cpt_diag_dr+= cptSymbole(position,tab[lig-count_diag_dr][col+count_diag_dr]);
                    count_diag_dr++;
                }

                while(tab[lig-count_diag_ga][col-count_diag_ga]==SYMB_P1 || tab[lig-count_diag_ga][col-count_diag_ga]==SYMB_P2){
                    cpt_diag_ga+= cptSymbole(position,tab[lig-count_diag_ga][col-count_diag_ga]);
                    count_diag_ga++;
                }
            }
            if(cpt_lig==PUISSANCES||cpt_col==PUISSANCES||cpt_diag_dr==PUISSANCES||cpt_diag_ga==PUISSANCES){
                return 1;
            }

            /*                if(typePartie == 3 && cpt_col==PUISSANCES-1){
                    tab[lig-cpt][col]=SYMB_P2;
                }*/

            if(typePartie == 3 && cpt_lig==PUISSANCES-1){
                tab[lig][col+1]=SYMB_P2;
            }
            cpt_col=1;
            cpt_diag_dr=1;
            cpt_diag_ga=1;
        }
        cpt_lig=0;
        cpt_col=0;
    }
    return 0;
}

int choixPartie(){
    int choixUser;
    printf("Welcome into HEPuIssAnce_4\n Quelle partie souhaitez-vous jouez ?\n------------------------------\n");
    printf("  1.Joueur vs joueur\n  2.Joueur vs Computer(random version)\n  3.Joueur vs Computer (IA version)\n Votre choix--->");
    scanf("%d",&choixUser);
    printf("\nDebut de la partie, ready player one ...\nDans quelle colonne souhaitez vous jouer ?\n");
    return choixUser;
}

int winner(char numJoueur, int win){
    if (win == 1){
        printf("Félicitation joueur %c vous remportez la partie !!!", numJoueur);
        return 1;
    }
    return 0;
}

void gameStart_P2P(char tab[LIGNES][COLONNES]){
    int inputUser;
    while(checkIfWin(tab,1)==0){
        affichage(tab);
        scanf("%d", &inputUser);
        posCoord(inputUser, 'X',tab);
        if (winner('1', checkIfWin(tab,1))== 1)
            break;
        printf("Dans quelle colonne souhaitez vous jouer player 2?\n");
        scanf("%d", &inputUser);
        posCoord(inputUser, 'O',tab);
        if (winner('2', checkIfWin(tab,1))== 1)
            break;
        printf("Dans quelle colonne souhaitez vous jouer player 1?\n");
    }
}

void gameStart_PvC_v1(char tab[LIGNES][COLONNES]){
    int inputUser;
    srand(time(0));// initialisation de la graine avec l'identifiant du processus

    while(checkIfWin(tab,2)==0){
        affichage(tab);
        scanf("%d", &inputUser);
        posCoord(inputUser, SYMB_P1,tab);
        if (winner('1', checkIfWin(tab,2))== 1)
            break;
        printf("Au tour de l'ordinateur...\n");
        int cpRandom = rand() % (COLONNES + 1); // nombre aleatoire de 0..upperBound
        posCoord(cpRandom,SYMB_P2,tab);
        if (winner('2', checkIfWin(tab,2))== 1)
            break;
        printf("Dans quelle colonne souhaitez vous jouer player 1?\n");
    }
}

void gameStart_PvC_v2(char tab[LIGNES][COLONNES]){
    int inputUser;
    srand(time(0));// initialisation de la graine avec l'identifiant du processus

    while(checkIfWin(tab,3)==0){
        affichage(tab);
        scanf("%d", &inputUser);
        posCoord(inputUser, SYMB_P1,tab);
        if (winner('1', checkIfWin(tab,3))== 1){
            break;
        }
        printf("Au tour de l'ordinateur...\n");
        int cpRandom = rand() % (COLONNES + 1); // nombre aleatoire de 0..upperBound
        posCoord(cpRandom,SYMB_P2,tab);
        if (winner('2', checkIfWin(tab,3))== 1){
            break;
        }
        printf("Dans quelle colonne souhaitez vous jouer player 1?\n");
    }
}

void gameStart(char tab[LIGNES][COLONNES]){
    int choix=choixPartie();
    if(choix == 1){
        gameStart_P2P(tab);
    }
    else if(choix==2){
        gameStart_PvC_v1(tab);
    }
    else if(choix==3){
        gameStart_PvC_v2(tab);
    }
}

void main() {
    char tab[LIGNES][COLONNES];
    creerGrille(CASE_VIDE,tab);
    gameStart(tab);
}
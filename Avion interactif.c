#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "conio.h"

typedef struct Coordonnees Coordonnees;
struct Coordonnees
{
    int x;
    int y;
};

typedef struct Avion Avion;
struct Avion
{
    int x;
    int y;
};

typedef struct Pbm Pbm;
struct Pbm
{
    int largeurImage;
    int longueurImage;
    char nomFichier[100];
};

int main()
{
    int tableauCiel[80][24] = {0};
    int tableauAvion[10][10] = {0};
    int compteurX;
    int compteurY;
    char toucheClavier;

    Pbm image;
    Avion avion;
    Coordonnees position;

    FILE* fichier_1 = NULL;
    FILE* fichier_2 = NULL;
    FILE* fichier_3 = NULL;
    FILE* fichier_4 = NULL;


    fichier_1 = fopen("Avion Droite.pbm", "r");
    fichier_2 = fopen("Avion Gauche.pbm", "r");
    fichier_3 = fopen("Avion Haut.pbm", "r");
    fichier_4 = fopen("Avion Bas.pbm", "r");



        lireResolutionImage(fichier_2, &image);
        chargerImageAvion(fichier_2, &image, tableauAvion);
        integrerAvionDansCiel(tableauCiel, tableauAvion, &compteurX);
        afficherTableauCiel(tableauCiel);



        while (1)
        {
            toucheClavier = getch();

            if (toucheClavier == 67) //Droite
            {
                fichier_1 = fopen("Avion Droite.pbm", "r");
                system("clear");
                compteurX++;
                //memset (tableauCiel, 0, sizeof (tableauCiel));
                clearTableauCiel(tableauCiel);
                lireResolutionImage(fichier_1, &image);
                chargerImageAvion(fichier_1, &image, tableauAvion);
                integrerAvionDansCiel(tableauCiel, tableauAvion, &compteurX, &compteurY);
                afficherTableauCiel(tableauCiel);
                fclose(fichier_1);
                }

            else if (toucheClavier == 32)
            {
                system("clear");
                exit(0);
            }

             else if (toucheClavier == 68) //Gauche
            {
                fichier_2 = fopen("Avion Gauche.pbm", "r");
                system("clear");
                compteurX--;
                //memset (tableauCiel, 0, sizeof (tableauCiel));
                clearTableauCiel(tableauCiel);
                lireResolutionImage(fichier_2, &image);
                chargerImageAvion(fichier_2, &image, tableauAvion);
                integrerAvionDansCiel(tableauCiel, tableauAvion, &compteurX, &compteurY);
                afficherTableauCiel(tableauCiel);
                fclose(fichier_2);
                }

            else if (toucheClavier == 32)
            {
                system("clear");
                exit(0);
            }

             else if (toucheClavier == 65) //Haut
            {
                fichier_3 = fopen("Avion Haut.pbm", "r");
                system("clear");
                compteurY--;
                //memset (tableauCiel, 0, sizeof (tableauCiel));
                clearTableauCiel(tableauCiel);
                lireResolutionImage(fichier_3, &image);
                chargerImageAvion(fichier_3, &image, tableauAvion);
                integrerAvionDansCiel(tableauCiel, tableauAvion, &compteurX, &compteurY);
                afficherTableauCiel(tableauCiel);
                fclose(fichier_3);
                }

            else if (toucheClavier == 32)
            {
                system("clear");
                exit(0);
            }

            else if (toucheClavier == 66) //Bas
            {
                fichier_4 = fopen("Avion Bas.pbm", "r");
                system("clear");
                compteurY++;
                //memset (tableauCiel, 0, sizeof (tableauCiel));
                clearTableauCiel(tableauCiel);
                lireResolutionImage(fichier_4, &image);
                chargerImageAvion(fichier_4, &image, tableauAvion);
                integrerAvionDansCiel(tableauCiel, tableauAvion, &compteurX, &compteurY);
                afficherTableauCiel(tableauCiel);
                fclose(fichier_4);
                }

            else if (toucheClavier == 32)
            {
                system("clear");
                exit(0);
            }


        }


    return 0;
}

void lireResolutionImage (char *fichier, Pbm* p)
{
    char lecture[30] = "";

    for (int i = 0; i < 2; i++)
    {
        fgets(lecture, 30, fichier);
    }

    fscanf(fichier, "%d %d", &p->largeurImage, &p->longueurImage);
    printf("Resolution : %d x %d\n\n", p->largeurImage, p->longueurImage);
}

void chargerImageAvion(char *fichier, Pbm* p, int tableauAvion[10][10])
{
    char lectureLigneFichier[71] = "";
    int binaireImagePBM;

    while (fgets(lectureLigneFichier, 71, fichier) != NULL)// à partir d'ici, on va lire toutes le code de l'image jusqu'à la fin du fichier
    {
        for (int z = 0; z < p->longueurImage; z++) // boucle pour permettre de se positionner dans la première colonne
        {
            for (int k = 0; k < p->largeurImage; k++) // boucle pour lire toutes les données de la première ligne
            {
                fscanf(fichier, "%d ", &binaireImagePBM); // on stocke l'entier lu dans notre variable "binaireImagePBM"
                tableauAvion[k][z] = binaireImagePBM; // on stocke la valeur lue dans notre tableau 2D en partant d'un point précis pour centrer l'image grâc à un calcul
            }
        }
    }
}

void integrerAvionDansCiel(int tableauCiel[80][24], int tableauAvion[10][10], int *pointeurCompteurX, int *pointeurCompteurY)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0;j < 10; j++)
        {
            tableauCiel[j + (*pointeurCompteurX)%80][i + (*pointeurCompteurY)%24] = tableauAvion[j][i];
        }
    }
}

void clearTableauCiel(int tableauCiel[80][24])
{
    for (int i = 0; i < 24; i++)
    {
        for (int j = 0; j < 80; j++)
        {
            tableauCiel[j][i] = 0;
        }
    }
}

void afficherTableauCiel(int tableauCiel[80][24])
{
    char c[] = {226, 150, 136, 0};

    for(int i = 0; i < 24; i++)
    {
        for(int j = 0; j < 80; j++)
        {
            if(tableauCiel[j][i] == 0) // si la valeur du tableau est un 0, on va afficher "X"
            {
                printf(" "); //affichage du caractère " " qui représente notre ciel.
            }
            else // si la valeur n'est pas 0 dans le tableau, alors on affiche " " (espace)
            {
                printf("%s", c);
            }
        }
        printf("\n");

    }

}

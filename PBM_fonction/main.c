#include <stdio.h>
#include <stdlib.h>
#include <string.h> // bibliothèque pour l'utilisation des différentes fonctions de traitement de chaîne de caractères
#include <time.h>
#include <unistd.h>

typedef struct Pbm Pbm; // on remplace "struct Pbm" par "Pbm" pour raccourcir le code
struct Pbm // définition de notre structure Pbm
{
    int largeurImage;   // ces deux int vont stocker la résolution de l'image
    int longueurImage;
    char nomImage[100]; // va comporter le nom de notre fichier PBM tiré aléatoirement
};

void choixImage(Pbm* p); // fonction qui va permettre de choisir un PBM aléatoirement
void lireResolution(char *fichier, Pbm* p); // permet de stocker la résolution de notre image
void insererImageCentreeDansTableau(char *fichier, Pbm* p, int tableauPourImage[80][23]); // permet de charger l'image dans le tableau à deux dimensions tout en la centrant
void afficherTableau(int tableauPourImage[80][23]); // va nous permettre d'afficher le tableau 2D


int main()
{
    Pbm image; // "image" va contenir toutes nos variables situées dans la structure Pbm
    int tableauPourImage[80][23] = {0}; // on créer un tableau à deux dimensions rempli de 0

    choixImage(&image); // on va choisir une image aléatoirement, on envoie "&image" pour utiliser par la suite le char de notre structure afin de stocker le nom du fichier PBM tiré aléatoirement

    FILE* fichier = NULL; // notre "FILE*" permet de récupérer le pointeur du fichier pour ensuite pouvoir le manipuler

    fichier = fopen(image.nomImage, "r"); // on ouvre le fichier qui est contenu dans le char de notre structure et on lui assigne "r" pour juste permettre de lire le fichier

    if(fichier != NULL) // peremt de s'assurer que le fichier s'est bien ouvert
    {
        //printf("Le fichier a bien été ouvert\n");
        lireResolution(fichier, &image); // cette fonction va permettre de stocker la résoltion de l'image PBM
        //printf("Votre image a une résolution de : %dx%d\n\n", image.largeurImage, image.longueurImage); // ici on va stocker les deux entiers de résoltuion (longueur x largeur) dans les variables de notre structure Pbm
        insererImageCentreeDansTableau(fichier, &image, tableauPourImage); // cette fonction va nous permettre d'insérer le code de l'image PBM dans notre tableau à deux dimensions tout en centrant l'image
        fclose(fichier); // après avoir fini de manipuler le fichier, il faut fermer le fichier pour libérer la mémoire vive
    }
    else // permet de savoir si le fichier ne s'est pas ouvert
    {
        printf("Le fichier n'a pas été ouvert");
    }
    afficherTableau(tableauPourImage); // on va afficher le tableau à deux dimensions qui contient le code de l'image PBM, on va afficher un "X" quand la valeur est 0 et un " " quand la valeur est 1

    return 0;
}

void choixImage(Pbm* p) // "Pbm* p" est un pointeur sur la structure
{

    strcpy(p->nomImage, "avion.pbm");

}

void insererImageCentreeDansTableau(char *fichier, Pbm* p, int tableauPourImage[80][23])
{
    char lectureLigneFichier[71] = ""; // on crée un char pour la lecture des lignes de fichier
    int binaireImagePBM; // variable qui permettra de stocker les différentes valeurs de code de l'image

    fgets(lectureLigneFichier, 71, fichier); // fgets permet de lire une ligne dans un fichier, ici fgets va nous permettre de passer la troisième ligne qui est inutile pour directement arrivé là où le code est définie

    while (fgets(lectureLigneFichier, 71, fichier) != NULL) // à partir d'ici, on va lire toutes le code de l'image jusqu'à la fin du fichier
    {
        for(int z = 0; z < p->longueurImage; z++) // boucle pour permettre de se positionner dans la première colonne
        {
            for(int k = 0; k < p->largeurImage; k++) // boucle pour lire toutes les données de la première ligne
            {
                fscanf(fichier, "%d", &binaireImagePBM); // on stocke l'entier lu dans notre variable "binaireImagePBM"
                //printf("%d", binaireImagePBM);
                tableauPourImage[k + ((80 - p->largeurImage)/2)][z + ((23 - p->longueurImage)/2)] = binaireImagePBM; // on stocke la valeur lue dans notre tableau 2D en partant d'un point précis pour centrer l'image grâc à un calcul
            }
            //printf("\n");
        }
    }
}

void lireResolution(char *fichier, Pbm* p) // fonction qui permet de stocker la résolution de l'image
{
    char lectureLigne[10] = ""; // char qui va permettre de stocker la ligne où est écrit la résoltuion de l'image

    for(int i = 0; i < 2; i++)
    {
        fgets(lectureLigne, 71, fichier); // on saute les deux premières lignes afin de se diriger directement là où est noté la résolution de l'image
    }
    fscanf(fichier, "%d %d", &p->largeurImage, &p->longueurImage); // on récupère les données de la résolution en les stockant dans les variables de notre structures
}

void afficherTableau(int tableauPourImage[80][23]) // fonction qui va afficher notre tableau 2D
{
    char c[] = {226, 150, 136, 0};

    for (int i = 0 ; i < 23; i++) // boucle qui va commencer par la première colonne puis la deuxième après qu'on ait fini de lire toutes les valeurs de la première colonne
    {
        for (int j = 0; j < 80; j++) // boucle qui va lire un par un les données de la première ligne du tableau jusqu'à la dernière valeur
        {
            if(tableauPourImage[j][i] == 0) // si la valeur du tableau est un 0, on va afficher "X"
            {
                printf(" ");
            }
            else // si la valeur n'est pas 0 dans le tableau, alors on affiche " " (espace)
            {
                printf("%s", c);
            }
        }
        printf("\n");
    }
    printf("\n");
}

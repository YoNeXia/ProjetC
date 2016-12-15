#include "Avion Interactif.h"


typedef struct Coordonnees Coordonnees; //Définition d'une strucutre de données regroupant les coordonnées de notre avion
struct Coordonnees
{
    int X;
    int Y;
};

typedef struct Pbm Pbm; //Définition d'une structure de données regroupant lar largeur de notre image PBM, la longueur de notre image PBM ainsi que son nom de fichier
struct Pbm
{
    int largeurImage;
    int longueurImage;
    char nomFichier[100];
};


int main()
{
    int tableauCiel[80][24] = {0}; //Déclaration et initialisation de deux tableaux 2D : Ciel en 80x24 et Avion en 10x10
    int tableauAvion[10][10] = {0};

    char toucheClavier; //Déclaration de notre touche qui va nous renvoyer notre valeur ASCII qui va permettre de quitter, ou encore de bouger l'avion lorsque celle-ci sera pressée

    Coordonnees pos; //Définition de la position contenant un x (abcisse) et un y (ordonnée)

    Pbm image; //Définition de l'image contenant une largeur et une longueur ainsi qu'un nom


    /* Initialisation à NULL de quatre fichiers qui vont par la suite contenir nos différents PBM */

    FILE* fichier_1 = NULL;
    FILE* fichier_2 = NULL;
    FILE* fichier_3 = NULL;
    FILE* fichier_4 = NULL;

    /* On défini que chacun des 4 fichiers correspond à une image PBM en mode lecture seule */

    fichier_1 = fopen("Avion Droite.pbm", "r");
    fichier_2 = fopen("Avion Gauche.pbm", "r");
    fichier_3 = fopen("Avion Haut.pbm", "r");
    fichier_4 = fopen("Avion Bas.pbm", "r");

    /* Initialisation d'un switch case qui permet de choisir l'orientation de l'avion au départ  */

    printf("Orientation de départ de notre avion :"
           " 1. Droite / 2. Gauche / 3. Haut / 4. Bas");

    int valeur_switch = 0;

    scanf("%d", &valeur_switch);

    switch (valeur_switch)
    {
    case 1:
        lireResolutionImage(fichier_1, &image); //Fonction permettant de lire la résolution du fichier PBM choisi
        chargerImageAvion(fichier_1, &image, tableauAvion); //Fonction permettant de charger l'image PBM du fichier choisi dans un tableau 2D conçu pour l'avion
        integrerAvionDansCiel(tableauCiel, tableauAvion, &pos); //Fonction permettant d'intégrer notre tableau 2D de notre avion dans le tableau 2D de notre ciel qui est en réalité la console. Le tableau de l'avion aura par ailleurs un pisition bien particulière dans l'espace
        afficherTableauCiel(tableauCiel); //Fonction permettant d'afficher le tableau 2D de notre ciel en 80x24
        break;
    case 2:
        lireResolutionImage(fichier_2, &image);
        chargerImageAvion(fichier_2, &image, tableauAvion);
        integrerAvionDansCiel(tableauCiel, tableauAvion, &pos);
        afficherTableauCiel(tableauCiel);
        break;
    case 3:
        lireResolutionImage(fichier_3, &image);
        chargerImageAvion(fichier_3, &image, tableauAvion);
        integrerAvionDansCiel(tableauCiel, tableauAvion, &pos);
        afficherTableauCiel(tableauCiel);
        break;
    case 4:
        lireResolutionImage(fichier_4, &image);
        chargerImageAvion(fichier_4, &image, tableauAvion);
        integrerAvionDansCiel(tableauCiel, tableauAvion, &pos);
        afficherTableauCiel(tableauCiel);
        break;
    default:
        printf("Erreur valeur");
        exit (0);
        break;

    }


    while (1)
    {
        toucheClavier = getch(); //Fonction permettant d'attendre que l'utilisateur appuie sur une touche afin de réaliser une action

        if (toucheClavier == 67) // Touche Droite
        {
            fichier_1 = fopen("Avion Droite.pbm", "r");//Ouvre le bon fichier en fonction de l'orientation de l'avion donc en fonction des flèches directionnelles
            system("clear"); //Nettoie la console à chaque fois que l'on appuie sur une flèche directionnelle
            pos.X++; //Incrémentation de X afin que l'avion puisse avancr à chaque fois que l'on appuie sur la flèche directionelle Droite
            //memset (tableauCiel, 0, sizeof (tableauCiel)); (clean un tableau normalement)
            clearTableauCiel(tableauCiel); //Reinitilialise le tableau pour que la position de l'avion ne soit pas sauvegarder dans la console
            lireResolutionImage(fichier_1, &image); //Fonction permettant de lire la résolution du fichier PBM choisi
            chargerImageAvion(fichier_1, &image, tableauAvion); //Fonction permettant de charger l'image PBM du fichier choisi dans un tableau 2D conçu pour l'avion
            integrerAvionDansCiel(tableauCiel, tableauAvion, &pos); //Fonction permettant d'intégrer notre tableau 2D de notre avion dans le tableau 2D de notre ciel qui est en réalité la console. Le tableau de l'avion aura par ailleurs un position bien particulière dans l'espace
            afficherTableauCiel(tableauCiel); //Fonction permettant d'afficher le tableau 2D de notre ciel en 80x24
            fclose(fichier_1);
        }

        else if (toucheClavier == 32) //permet de nettoyer la console et de quitter celle-ci si et seulement si la touche espace est enfoncée
        {
            system("clear");
            exit(0);
        }

        else if (toucheClavier == 68) // Touche Gauche
        {
            fichier_2 = fopen("Avion Gauche.pbm", "r");
            system("clear");
            pos.X--;
            pos.X = (pos.X+80)%80;
            //memset (tableauCiel, 0, sizeof (tableauCiel));
            clearTableauCiel(tableauCiel);
            lireResolutionImage(fichier_2, &image);
            chargerImageAvion(fichier_2, &image, tableauAvion);
            integrerAvionDansCiel(tableauCiel, tableauAvion, &pos);
            afficherTableauCiel(tableauCiel);
            fclose(fichier_2);
        }

        else if (toucheClavier == 32)
        {
            system("clear");
            exit(0);
        }

        else if (toucheClavier == 65) // Touche Haut
        {
            fichier_3 = fopen("Avion Haut.pbm", "r");
            system("clear");
            pos.Y--;
            //memset (tableauCiel, 0, sizeof (tableauCiel));
            clearTableauCiel(tableauCiel);
            lireResolutionImage(fichier_3, &image);
            chargerImageAvion(fichier_3, &image, tableauAvion);
            integrerAvionDansCiel(tableauCiel, tableauAvion, &pos);
            afficherTableauCiel(tableauCiel);
            fclose(fichier_3);
        }

        else if (toucheClavier == 32)
        {
            system("clear");
            exit(0);
        }

        else if (toucheClavier == 66) //Touche Bas
        {
            fichier_4 = fopen("Avion Bas.pbm", "r");
            system("clear");
            pos.Y++;
            //memset (tableauCiel, 0, sizeof (tableauCiel));
            clearTableauCiel(tableauCiel);
            lireResolutionImage(fichier_4, &image);
            chargerImageAvion(fichier_4, &image, tableauAvion);
            integrerAvionDansCiel(tableauCiel, tableauAvion, &pos);
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

void lireResolutionImage (char *fichier, Pbm* p) //Fonction permettant de lire la résolution du fichier PBM choisi reçevant un fichier et un pointeur sur la structure Pbm en paramètre
{
    char lecture[30] = ""; //Initialiasion d'une chaîne de 30 caractères vide

    for (int i = 0; i < 2; i++)
    {
        fgets(lecture, 30, fichier); //permet de sauter les deux premières lignes du fichier PBM : fgets permettant de lire une chaîne de caractère
    }

    fscanf(fichier, "%d %d", &p->largeurImage, &p->longueurImage); //Permettant de lire la résolution donnée d'une image PBM grâce à la fonction fscanf et d'insérer la valeur de la résolution dans la structure du PBM afin de définir une longeur et une largeur du PBM
    printf("Resolution : %d x %d\n\n", p->largeurImage, p->longueurImage); //Permet d'afficher la résolution du PBM donné
}

void chargerImageAvion(char *fichier, Pbm* p, int tableauAvion[10][10]) //Fonction permettant de charger l'image PBM du fichier choisi dans un tableau 2D conçu pour l'avion qui prend en paramètre un nom de fichier, un pointeur sur la structure PBM et un tableau avion
{
    char lectureLigneFichier[71] = ""; //Déclaration d'une chaine de caractère à vide et d'un entier binairePBM
    int binaireImagePBM;

    while (fgets(lectureLigneFichier, 71, fichier) != NULL)//À partir d'ici, on va lire tout le code de l'image jusqu'à la fin du fichier
    {
        for (int z = 0; z < p->longueurImage; z++) //Boucle pour permettre de se positionner dans la première colonne
        {
            for (int k = 0; k < p->largeurImage; k++) //Boucle pour lire toutes les données de la première ligne
            {
                fscanf(fichier, "%d ", &binaireImagePBM); //On stocke l'entier lu dans notre variable "binaireImagePBM" 0 ou 1
                tableauAvion[k][z] = binaireImagePBM; //On stocke la valeur lue dans notre tableau 2D ainsi on tranfère une image PBM dans un tableau
            }
        }
    }
}

void integrerAvionDansCiel(int tableauCiel[80][24], int tableauAvion[10][10], Coordonnees* p) //Fonction permettant d'intégrer notre tableau 2D de notre avion dans le tableau 2D de notre ciel qui est en réalité la console. Le tableau de l'avion aura par ailleurs un position bien particulière dans l'espace qui prends en paramètre les deux tableaux 2D ainsi que les coordonnées
{

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            tableauCiel[j + (p->X)%80][i + (p->Y)%24] = tableauAvion[j][i]; //Intégration de notre tableau de l'avion dans le tableau de ciel donc la console à  des coordonnées précise
        }
    }
}

void clearTableauCiel(int tableauCiel[80][24]) //Reinitilialise le tableau pour que la position de l'avion ne soit pas sauvegarder dans la console
{
    for (int i = 0; i < 24; i++)
    {
        for (int j = 0; j < 80; j++)
        {
            tableauCiel[j][i] = 0;
        }
    }
}

void afficherTableauCiel(int tableauCiel[80][24]) //Fonction permettant d'afficher le tableau 2D de notre ciel en 80x24
{
    char c[] = {226, 150, 136, 0}; //Caractère initialisé qui va nous permettre d'afficher un caractère ASCII

    for(int i = 0; i < 24; i++)
    {
        for(int j = 0; j < 80; j++)
        {
            if(tableauCiel[j][i] == 0) //Si la valeur du tableau est un 0, on va afficher "X"
            {
                printf(" "); //Affichage du caractère " " qui représente notre ciel.
            }
            else //Si la valeur n'est pas 0 dans le tableau, alors on affiche le caractère ASCII correspondant
            {
                printf("%s", c);
            }
        }
        printf("\n");

    }

}

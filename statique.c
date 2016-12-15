#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include <signal.h> //Cette bibliothèque renferme les routines de traitement de signal.

#include <termios.h> /* Cette bibliothèque renferme les définitions des valeurs du «termios».  Les fonctions termios  établissent une interface générale pour les
			terminaux, permettant de contrôler et tirer partis des possibilités du terminal. Permettant de contrôler les ports de communication asynchrone (ici entre clavier et console).*/

#include <unistd.h> //Cette bibliothèque renferme les types et les constantes symbole standard.
#include "statique2.h"



/*void processusFils(Pbm image)
{


    pid_t pid_fils;
	pid_fils = fork();

    if (pid_fils == 0) {
	char *fichier_a_ouvrir[] = {"ex1.pbm", "ex2.pbm", "ex3.pbm", "j.pbm", "licorne.pbm", NULL};
	   int nombre_aleatoire;
    int nombre;

    srand(time(NULL));
    nombre_aleatoire = rand();                      // Notre variable prend une valeur aléatoire
    nombre = nombre_aleatoire %5;                   // A l'aide du modulo, notre variable prend une valeur comprise entre 0 et 4
	
	
	chargerImage(&image, nombre);
	exit(0);
    }
	wait(NULL);

    return nombre;
}
*/

void chargerImage(Pbm* pointeur_structure) // Cette fonction permet de choisir de manière aléatoire l'image à afficher sur cet écran de veille
{

char *fichier_a_ouvrir[] = {"ex1.pbm", "ex2.pbm", "ex3.pbm", "j.pbm", "licorne.pbm", NULL};
	   int nombre_aleatoire;
    int nombre;

pid_t pid_fils;
	pid_fils = fork();


    if (pid_fils == 0) {
	

    srand(time(NULL));
    nombre_aleatoire = rand();                      // Notre variable prend une valeur aléatoire
    nombre = nombre_aleatoire %5;                   // A l'aide du modulo, notre variable prend une valeur comprise entre 0 et 4
	}

    switch(nombre)
    {
    case 0:
        strcpy(pointeur_structure->nom_image, "ex1.pbm");
	break;
    case 1:
        strcpy(pointeur_structure->nom_image, "ex2.pbm");
	break;
    case 2:
        strcpy(pointeur_structure->nom_image, "ex3.pbm");
	break;
    case 3:
        strcpy(pointeur_structure->nom_image, "j.pbm");
	break;
    case 4:
        strcpy(pointeur_structure->nom_image, "licorne.pbm");
	break;
    }

}


void insererImageCentreeDansTableau(char *fichier, Pbm* pointeur_structure, int tableau_pour_image[80][24]) // Cette fonction permet de centrer l'image au format .pbm
{
    char lecture_ligne[71] = "";                                     // Cette variable sera incrémenter de chacun de caractères du fichier
    int binaire_image;

    fgets(lecture_ligne, 71, fichier);

    while (fgets(lecture_ligne, 71, fichier) != NULL)
    {
        for(int i=0; i<pointeur_structure->longueur_image; i++)
        {
            for(int j=0; j<pointeur_structure->largeur_image; j++)
            {
                fscanf(fichier, "%d", &binaire_image);            // Le fscanf permet de stocker les carctères lus dans le fichier dans une variable
                tableau_pour_image[j + ((80 - pointeur_structure->largeur_image)/2)][i + ((24 - pointeur_structure->longueur_image)/2)] = binaire_image;
            }
        }
    }
}


void connaitreResolution(char *fichier, Pbm* pointeur_structure)// Cette fonction permet de connaître la résolution de l'image .pbm
{
    char lecture_ligne[71] = "";

    for(int i=0; i<2; i++)
    {
        fgets(lecture_ligne, 71, fichier); // Grâce à cette boucle les deux premières lignes sont lues, mais ignorées
    }
    fscanf(fichier, "%d %d", &pointeur_structure->largeur_image, &pointeur_structure->longueur_image);
}


void afficherTableau(int tableau_pour_image[80][24]) // Cette fonction permet d'afficher l'image qui a été stockée dans un tableau
{
    char c[] = {226, 150, 136, 0};

    for (int i=0 ; i<24; i++)
    {
        for (int j=0; j<80; j++)
        {
            if(tableau_pour_image[j][i] == 1)
            {
                printf("%s", c);
            }
            else
            {
                printf(" ");
            }
        }
    }
}


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//


int getch(void){    
struct termios oldattr, newattr;    
int ch;    
tcgetattr( STDIN_FILENO, &oldattr);    
newattr = oldattr;   
newattr.c_lflag &= ~( ICANON | ECHO);   
tcsetattr( STDIN_FILENO, TCSANOW, &newattr );  
ch = getchar(); 
tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );   
return ch;
}


char touche(){
   touche == getch(); 
   system("setterm -cursor off");  
   while(1)
   {
       if (touche == 32) // 32 pour la barre espace
       {
           system("clear");
           system("setterm -cursor on");
           system("clear");
           exit(0);
       }
       else
       {
           touche == getch();
       }
   }
}


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//


int statique()
{

    
    Pbm image;
    int tableau_pour_image[80][24] = {0};
    chargerImage(&image);


    FILE* fichier = NULL;

    fichier = fopen(image.nom_image, "r");

    if(fichier != NULL)
    {
        connaitreResolution(fichier, &image);
        insererImageCentreeDansTableau(fichier, &image, tableau_pour_image);
        fclose(fichier);
    }
    else
    {
        printf("Le fichier n'a pas été ouvert");
    }
    afficherTableau(tableau_pour_image);
    getch();
    touche();

   	

    return 0;
}


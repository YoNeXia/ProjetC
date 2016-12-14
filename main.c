#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include <signal.h> //Cette bibliothèque renferme les routines de traitement de signal.
#include <termios.h> /* Cette bibliothèque renferme les définitions des valeurs du «termios».  Les fonctions termios  établissent une interface générale pour les
terminaux, permettant de contrôler et tirer partis des possibilités du terminal. Permettant de contrôler les ports de communication asynchrone (ici entre clavier et console).*/
#include <unistd.h> //Cette bibliothèque renferme les types et les constantes symbole standard.
#include "statique2.h"


// Cette fonction permet de choisir de manière aléatoire l'image à afficher sur cet écran de veille
void chargerImage(char *fichier,Pbm* pointeur_structure, char heure[10],int tableau_pour_image[80][24])
{

    char *fichier_a_ouvrir[] = {"1.pbm", "2.pbm", "3.pbm", "4.pbm", "5.pbm", "6.pbm", "7.pbm", "8.pbm", "9.pbm", "points.pbm", NULL};

	int i = 0;
char k = "";
	for(i=0; i<5; i++){
		k = heure[i];




   /*switch(k)
    {
    case "0":
        strcpy(pointeur_structure->nom_image, "0.pbm");
	break;
    case "1":
        strcpy(pointeur_structure->nom_image, "1.pbm");
	break;
    case 50:
        strcpy(pointeur_structure->nom_image, "2.pbm");
	break;
    case 51:
        strcpy(pointeur_structure->nom_image, "3.pbm");
	break;
    case 52:
        strcpy(pointeur_structure->nom_image, "4.pbm");
	break;
    case 53:
        strcpy(pointeur_structure->nom_image, "5.pbm");
	break;
    case 54:
        strcpy(pointeur_structure->nom_image, "6.pbm");
	break;
    case 55:
        strcpy(pointeur_structure->nom_image, "7.pbm");
	break;
    case 56:
        strcpy(pointeur_structure->nom_image, "8.pbm");
	break;
    case 57:
        strcpy(pointeur_structure->nom_image, "9.pbm");
	break;
    //default:
        //strcpy(pointeur_structure->nom_image, "points.pbm");
	//break;

    }*/


	if(k == '0'){
		strcpy(pointeur_structure->nom_image, "0.pbm");
	}
	else if(k == '1'){
		strcpy(pointeur_structure->nom_image, "1.pbm");
	}
	else if(k == '2'){
		strcpy(pointeur_structure->nom_image, "2.pbm");
	}
	else if(k == '3'){
		strcpy(pointeur_structure->nom_image, "3.pbm");
	}
	else if(k == '4'){
		strcpy(pointeur_structure->nom_image, "4.pbm");
	}
    	else if(k == '5'){
		strcpy(pointeur_structure->nom_image, "5.pbm");
	}
   	else if(k == '6'){
		strcpy(pointeur_structure->nom_image, "6.pbm");
	}
	else if(k == '7'){
		strcpy(pointeur_structure->nom_image, "7.pbm");
	}
	else if(k == '8'){
		strcpy(pointeur_structure->nom_image, "8.pbm");
	}
	else if(k == '9'){
		strcpy(pointeur_structure->nom_image, "9.pbm");
	}
	}

}

// Cette fonction permet de centrer l'image au format .pbm
void insererImageCentreeDansTableau(char *fichier, Pbm* pointeur_structure, int tableau_pour_image[80][24])
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
                tableau_pour_image[j +10][i +28] = binaire_image;
            }
        }
    }
}

// Cette fonction permet de connaître la résolution de l'image .pbm
void connaitreResolution(char *fichier, Pbm* pointeur_structure)
{
    char lecture_ligne[71] = "";

    for(int i=0; i<2; i++)
    {
        fgets(lecture_ligne, 71, fichier); // Grâce à cette boucle les deux premières lignes sont lues, mais ignorées
    }
    fscanf(fichier, "%d %d", &pointeur_structure->largeur_image, &pointeur_structure->longueur_image);
}

// Cette fonction permet d'afficher l'image qui a été stockée dans un tableau
void afficherTableau(int tableau_pour_image[80][24])
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
return ch;}


char touche(){
   touche == getch();
   system("setterm -cursor off");
   while(1)
   {
       if (touche) // 32 pour la barre espace
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

/*void afficherHeure()
{
time_t now = time (NULL);
struct tm tm_now = *localtime (&now);
char heure[sizeof "HH:MM:SS"];
strftime (heure, sizeof heure, "%H:%M:%S", &tm_now);
return 0;
}

*/
int main()
{
    Pbm image;
    int tableau_pour_image[80][24] = {0};

			time_t now = time (NULL);
			struct tm tm_now = *localtime (&now);
			char heure[10];
			strftime (heure, 10, "%H:%M:%S", &tm_now);
			printf("%s",heure);




    FILE* fichier = NULL;

    chargerImage(fichier,&image, heure,tableau_pour_image[80][24]);

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

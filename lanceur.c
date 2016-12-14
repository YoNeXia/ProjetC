#include <unistd.h>
	#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>

#include "statique2.h"

void processusFils()
{
Pbm image;


    pid_t pid_fils;
	pid_fils = fork();

    if (pid_fils == 0) {
	printf("\n Je suis le fils !\n");
	choixAleatoireImage(&image);
exit(0);
    } else {
	printf("\n Je suis le père !\n");
    }
	wait(NULL);

    return EXIT_SUCCESS;
}


void choixAleatoireImage(Pbm* pointeur_structure)
{

    int nombre_aleatoire;
    int nombre;
    char *fichier_a_ouvrir[] = {"ex1.pbm", "ex2.pbm", "ex3.pbm", "j.pbm", "licorne.pbm", NULL};

    srand(time(NULL));
    nombre_aleatoire = rand();                      // Notre variable prend une valeur aléatoire
    nombre = nombre_aleatoire %5;                   // A l'aide du modulo, notre variable prend une valeur comprise entre 0 et 4

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
    

int main()
{

// ici le random de l'écran

    int nombre_aleatoire;
    int nombre;
    char *programme[]={"test", NULL};

    srand(time(NULL));
    nombre_aleatoire = rand();                      // Notre variable prend une valeur aléatoire
    nombre = nombre_aleatoire %3;                   // A l'aide du modulo, notre variable prend une valeur comprise entre 0 et 4

    switch(nombre)
    {
    case 0:
	processusFils();
        execv("test", programme);
	break;
    case 1:
        printf("Je suis dyna\n");
	break;
    case 2:
        printf("Je suis interac\n");
	break;
    }

return 0;
}

// dans le cas ou je tombe sur l'ecran statique je fais d'abord le random de l'image puis je l'envoi au programme en l'éxécutant
// le random image se fais dans un processus fils

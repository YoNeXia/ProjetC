#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>

#include "statique2.h"




void definir_heure()
{
        time_t temps;			//
        struct tm date;			//

        time(&temps);			//
        date = *gmtime(&temps);		//

	FILE * historique;		//
	historique = fopen ("historique.txt", "a+");	//ouvre le fichier historique.txt et permet d'ecrire dedans

        fprintf(historique, "%s", ctime(&temps));	//ecrit l'heure dans le fichier dur
}

    

int main()
{

	int nombre;
	int nombre_aleatoire;

	char *programme[]={"statique", "dynamique", "interactif", NULL};

	FILE * historique;
	historique = fopen ("historique.txt", "a+");

	srand(time(NULL));				//initialise le random
	nombre_aleatoire = rand();                      // Notre variable prend une valeur aléatoire
	nombre = nombre_aleatoire %3;                   // A l'aide du modulo, notre variable prend une valeur comprise entre 0 et 4    switch(nombre)

	if (nombre == 0)
	{

		fprintf(historique, "%s","statique "); 		//ecrit le type de l'ecran de veille, ici statique,  dans l'historique
		definir_heure();		//appel fonction qui permet d'afficher l'heure dans l'historique

		execv("statique", programme);
		      

	} else if (nombre == 1)
	{
		
		fprintf(historique, "%s", "dynamique ");	//ecrit le type de l'ecran de veille, ici dynamique,  dans l'historique
		definir_heure();		//appel fonction qui permet d'afficher l'heure dans l'historique

		execv("dynamique", programme);

	} else if (nombre == 2)
	{
		
		fprintf(historique, "%s", "interactif ");	//ecrit le type de l'ecran de veille, ici interactif,  dans l'historique
		definir_heure();		//appel fonction qui permet d'afficher l'heure dans l'historique

		execv("interactif", programme);
	}
	fclose (historique);
return 0;
}

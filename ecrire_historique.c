#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(void)
{
	int nombre;
	int nombre_image;
	FILE * historique;
	historique = fopen ("historique.txt", "a+");	//on ouvre historique.txt pour pouvoir ecrire dedans
	fprintf(historique, "%s/%s/%s %s:%s:%s", "jour", "mois", "annee", "heure", "minute", "seconde");	//on ecrit dans le .txt

	/*	Selon l'ecran de veille on ecrit dans le .txt le type d'ecran et ces caracteristiques
			(quel image pour statique, taille de l'horloge pour le dynamique
				position initial de l'avion pour l'interactif)				*/
	if (nombre == 0)
	{
		fprintf(historique,";%s", "statique");

		if (nombre_image == 0)
		{
			fprintf(historique, ";image%s\n", "1");
		}else if (nombre_image == 1)
		{
			fprintf(historique, ";image%s\n", "2");
		}else if (nombre_image == 2)
		{
			fprintf(historique, ";image%s\n", "3");
		}else if (nombre_image == 3)
		{
			fprintf(historique, ";image%s\n", "4");
		}else
		{
			fprintf(historique, ";image%s\n", "5");
		}

	} else if (nombre == 1)
	{
		fprintf(historique,";%s;%s\n", "dynamique", "taille_horloge");
	} else
	{
		fprintf(historique,";%s;%s\n", "interactif","position_avion");
	}

	fclose(historique);	//on ferme le .txt
	return(0);
}

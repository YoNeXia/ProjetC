#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

void afficher_historique()
{
	FILE *historique;
	int c;

	historique = fopen("historique.txt", "r");
	while(1)
	{
		c = fgetc(historique);
		if( feof(historique))
		{
			break;
		}
		printf("%c", c);
	}
	fclose(historique);
}

void trier_historique()
{
	FILE * historique_sort;
	historique_sort = fopen ("historique_sort.txt", "w+");
	system("sort -o historique_sort.txt historique.txt");
	fclose(historique_sort);
}

void afficher_tri()
{
	FILE *tri_sort;
	int c;

	tri_sort = fopen("historique_sort.txt", "r");
	while(1)
	{
		c = fgetc(tri_sort);
		if( feof(tri_sort))
		{
			break;
		}
		printf("%c", c);
	}
	fclose(tri_sort);


}


int main(int argc, char *argv[])
{
	int valeur_afficher_historique;
	int valeur_trier_historique;
	if(argc == 2 && strcmp(argv[1], "-stat")==0)
	{
//		printf("Historique");
		printf("Afficher l'historique ? 1 pour oui, 2 pour non\n");
		scanf("%d", &valeur_afficher_historique);
		printf("Trier l'historique et l'afficher ? 1 pour oui, 2 pour non\n");
		scanf("%d", &valeur_trier_historique);
		if (valeur_afficher_historique == 2 && valeur_trier_historique == 1)
		{
			trier_historique();
			afficher_tri();
		}else if (valeur_afficher_historique == 1 && valeur_trier_historique == 2)
		{
			afficher_historique();
		}else if (valeur_afficher_historique == 1 && valeur_trier_historique == 1)
		{
			afficher_historique();
			printf("------------------------------------\n");
			trier_historique();
			afficher_tri();
		}
	}
	else
	{
//		printf("Lanceur");
	}
	return 0;
}

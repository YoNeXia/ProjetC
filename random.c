#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (){

	int nombre_aleatoire;
	int nombre;
	srand(time(NULL));	//initialisation de rand
	nombre_aleatoire = rand();
	nombre = nombre_aleatoire %5;
	printf("%d\n",nombre);
	if (nombre == 0)
	{
		printf("image1\n");
	} else if(nombre == 1)
	{
		printf("image2\n");
	} else if (nombre == 2)
	{
		printf("image3\n");
	} else if (nombre == 3)
	{
		printf("image4\n");
	} else
	{
		printf("image5\n");
	}
	return 0;
}

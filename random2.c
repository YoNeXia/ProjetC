#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (){

    int nombre_aleatoire;
    int i = 5;
    int image[i];
    srand(time(NULL));  //initialisation de rand
    nombre_aleatoire = rand()%i;    //générer un nombre aleatoire modulo i
    printf("%d\n", nombre_aleatoire);   //afficher nombre aleatoire

    for (i=0; i<5; i++)
    {
        if (nombre_aleatoire == i)  //si le nombre aleatoire = i
        {
            printf("image%d\n", i); //afficher i
        }
    }
    return 0;
}


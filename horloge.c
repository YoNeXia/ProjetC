#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>
#include "conio.h"

void Afficher_heure ()
{
    time_t actuel;
    struct tm *ts;
    char temps [100];


    actuel = time(NULL); /* Récupération du temps */
    ts = localtime(&actuel);
    strftime (temps, sizeof(temps), " %H:%M:%S ", ts);
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf ("                                 %s\n", temps);
}

void Actualisation_heure ()
{

    int i = 0;
    printf("\n");
    printf("\n");
    printf ("              Cet écran sera actualisé dans quelques secondes");


    while (i < 5)
    {

        sleep (1);
        printf (" . ");
        fflush (stdout);

        i ++;



    }

}



void main(void)
{

	char touche_quitter;
	//touche_quitter = kbhit();


		 while (1)
    		{
			if (kbhit())
			{
				system("clear");
				exit(0);
			}

			else
			{

				Afficher_heure();
        			Actualisation_heure();
        			system ("clear");
			}

   		 }






}

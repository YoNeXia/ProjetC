#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

void Afficher_heure ()
{
    time_t actuel;
    struct tm *ts;
    char temps [100];


    actuel = time(NULL); /* Récupération du temps */
    ts = localtime(&actuel);
    strftime (temps, sizeof(temps), " %H:%M:%S ", ts);
    printf ("%s\n", temps);
}

void Actualsation_heure ()
{
    int i = 0;
    printf ("Cet écran sera actualisé dans quelques secondes");



    while (i < 10)
    {

        sleep (1);
        printf (" . ");
        fflush (stdout);

        i ++;

    }
}

int main(void)
{

    while (1)
    {
        Afficher_heure();
        Actualsation_heure();
        system ("clear");
    }

    return 0;
}

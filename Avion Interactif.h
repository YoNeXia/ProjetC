#ifndef AVION_INTERACTIF_H_INCLUDED
#define AVION_INTERACTIF_H_INCLUDED

#include <stdlib.h> //Cette bibliothèque renferme les routines standard.
#include <stdio.h> //Cette bibliothèque renferme les routines de traitement d'entrée/sortie fichier.
#include <string.h> //Cette bibliothèque renferme les routines de traitement de chaine de caractères.
#include <time.h> //Cette bibliothèque renferme les routines de traitement du temps.
#include <unistd.h> //Cette bibliothèque renferme les types et les constantes symbole standard.
#include "conio.h" //Cette bibliothèque est équivalente au <terminios.h> : bibliothèque renferme les définitions des valeurs du «termios» qui permet de modifier le terminal.


typedef struct Coordonnees Coordonnees;
typedef struct Pbm Pbm;
void lireResolutionImage (char *fichier, Pbm* p);
void chargerImageAvion(char *fichier, Pbm* p, int tableauAvion[10][10]);
void integrerAvionDansCiel(int tableauCiel[80][24], int tableauAvion[10][10], Coordonnees* p);
void clearTableauCiel(int tableauCiel[80][24]);
void afficherTableauCiel(int tableauCiel[80][24]);





#endif // AVION_INTERACTIF_H_INCLUDED

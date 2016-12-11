#include <stdio.h> //Cette bibliothèque renferme les routines de traitement d'entrée/sortie fichier.
#include <signal.h> //Cette bibliothèque renferme les routines de traitement de signal.
#include <termios.h> /* Cette bibliothèque renferme les définitions des valeurs du «termios».  Les fonctions termios  établissent une interface générale pour les
terminaux, permettant de contrôler et tirer partis des possibilités du terminal. Permettant de contrôler les ports de communication asynchrone (ici entre clavier et console).*/
#include <stdlib.h> //Cette bibliothèque renferme les routines standard.
#include <unistd.h> //Cette bibliothèque renferme les types et les constantes symbole standard.

struct termios ancien_terminal; /* structure de données "ancien_terminal" qui permet de restaurer l'ancien terminal. */

int modeBrut (int variable) /* Passage du terminal en mode raw ou brut. */
{
	struct termios nouveau_terminal; /* structure de données "nouveau_terminal" qui permet de passer au nouveau terminal. */

	/* Configuration Nouveau Terminal. */

	if(tcgetattr(variable, &ancien_terminal) < 0) /* Récupère les paramètres associés à variable et les stocke dans la structure ancien_terminal, permet 		d'obtenir les paramètres actuels de la structure */

		return(-1);

		nouveau_terminal = ancien_terminal;

		/* Réglages des nouveaux attributs pour configurer le nouveau terminal. */

		nouveau_terminal.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG); // --> syntaxe

		/* .c_lflag --> modes locaux : Ce champ est d'une importance capitale : il définit le mode (canonique ou non) et la gestion de l'écho. 

		- ECHO -> Activer l'écho des caractères saisis, afin que la console les prennents en compte sans quoi le programme ne marcherait pas.

		- ICANON -> Valider des caractères spéciaux tel que : erase, kill (signaux). Active le mode canonique autrement dit le mode interactif c'est-à-dire 			que les caractèes reçus sont stockés dans un tampon et qu'ils ne sont disponibles qu'à la réception d'un caractère, les caractères ne peuvent pas 			être luent immédiatement. L'utilisateur n'a plus besoin d'appuyer sur la touche ENTER. Dès lors qu'une touche est enfoncée, le caractère ASCII est 			directement sauvegarder contrairement au mode non canonique où il faut appuyer sur ENTER pour enregistrer son ou ces caractères.

		- IEXTEN -> Valider des caractères spéciaux tel que eol2,  lnext,  reprint  et  werase (signaux). 

		- ISIG -> Valider des caractères spéciaux tel que : interrupt, quit et suspend (signaux). */
												
		nouveau_terminal.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON); 

		/* .c_iflag --> modes d'entrée : Ils définissent un traitement à appliquer sur les caractères en provenance de la liaison série (ici le clavier).

		- BRKINT -> un break videra les files d'attente de processus en entrée et sortie, et si le terminal contrôle un groupe de processus au premier 			plan, un signal SIGINT sera envoyé à ce groupe pour le tuer.
				
		- ICRNL -> Traduire les Retours-Chariots.

		- INPCK -> Active la vérification de parité. Le contrôle de parité permet de vérifier l'intégrité des données envoyées (ou reçues) en 			comptant le nombre de bits à 1 et en collant le résultat directement à la suite des bits envoyés. Cette méthode ne permet pas de correction, 			uniquement la détection d'erreur dans la transmission. Pour être plus explicite il consiste à ajouter un 1 si le nombre de bits du mot de code est 			impair, 0 dans le cas contraire. Dans un octet s'il y a 3 "1" et 4 "0", alors le bit de partité sera un "1", si il y avait eu 4 "1" et 3 "0", alors 			le bit de partité aurait été "0".

		- ISTRIP -> Effacer le 8ième bits/caractères en entrée et le transformer en 0.

		- IXON -> Activer le controle de flux XON/XOFF. L’idée de base est simple, quand la mémoire tampon du receveur est remplie au point de ne plus 			pouvoir recevoir aucune donnée il émet un XOff à l’émetteur. Quand l’émetteur voit la chaine XOff, il arrête d’émettre. Il va reprendre uniquement 			s’il voit un XOn correspondant. 

		Le but du contrôle de flux est de synchroniser un ordinateur et un périphérique qui n'ont pas la même vitesse de traitement des informations, mais 			qui peuvent avoir la même vitesse de transmission.
		Par exemple, un ordinateur envoie des données à une imprimante plus rapidement que l'imprimante ne peut imprimer (asynchronie). L'imprimante 			enregistre les informations dans une zone de mémoire tampon (buffer en anglais). Lorsque cette zone de mémoire tampon est presque 			saturée, l'imprimante envoie un signal "X-off" à l'ordinateur qui stoppe l'envoi des données ; inversement, dès que la mémoire tampon de l'imprimante 			est de nouveau disponible, cette dernière envoie à l'ordinateur un signal "X-on", et l'ordinateur reprend l'envoi de données jusqu'au prochain signal 			"X-off" reçu et ainsi de suite.*/


		nouveau_terminal.c_cflag &= ~(CSIZE | PARENB); 
		nouveau_terminal.c_cflag |= CS8; 

		/* .c_cflag --> modes de contrôle : Ce champ est important, car c'est ici que l'on définit le débit, la parité utilisée, les bits de donnée et de 			stop, ... 

		- CSIZE -> Permet de définir la longueur des caractères ici 8 bits car CS8
		
		- PARENB -> Valider le codage de parité en sortie, et la vérification de parité en entrée. */

		nouveau_terminal.c_oflag &= ~(OPOST); 

		/* .c_oflag --> modes de sortie : Ils définissent un traitement à appliquer sur les caractères envoyés sur la liaison série. 

		- OPOST -> Traitement en sortie. */
 
		nouveau_terminal.c_cc[VMIN] = 1; 
		nouveau_terminal.c_cc[VTIME] = 0; 

		/* .c_cc[NCCS] --> caractères de contrôle : C'est un tableau de caractères. Des constantes sont définies pour accéder à quelques éléments 			particuliers et pai ailleurs les définir.

		- VMIN -> En mode non-canonique uniquement, spécifie le nombre de caractéres que doit contenir le tampon pour être accessible à la lecture. En 			général, on fixe cette valeur à 1 comme ici. Nombre minimum de caractères lors d'une lecture en mode non canonique.

		- VTIME -> En mode non-canonique uniquement, spécifie, le temps au bout duquel un caractère devient accessible, même si le tampon ne contient pas 			c_cc [VMIN] caractères. Une valeur de 0 représente un temps infini comme ici. Délai en dixièmes de seconde pour une lecture en mode non canonique. */

		

	if(tcsetattr(variable, TCSAFLUSH, &nouveau_terminal) < 0) /* Fixe les paramètres du nouveau terminal en lisant la structure nouveau_terminal. Cette fonction 		permet donc de appliquer les nouveaux paramètres du terminal. 

	TCSAFLUSH -->  Les modifications sont effectuées lorsque toutes les opérations d'écriture sur variable auront été transmises. Les entrées qui n'ont pas été 		traitées  seront éliminées avant de faire les modifications. Autrement dit Le changement se produit après que toute la sortie écrite sur l'objet référencé 		par variable a été transmise et toutes les entrées qui ont été reçues mais qui n'ont pas été lues seront rejetées avant que la modification soit effectuée. */

		return(-1);

	return(0);
}
	
	 
int ReinitialisationTerminal (int variable) /* Permet d'afficher l'ancien Terminal --> passage en mode cooked */
{
	if(tcsetattr(variable, TCSAFLUSH, &ancien_terminal) < 0)
		return(-1);

	return(0);
}

void sigcatch(int sig) /* Signal permettant la réinitialisation du terminal en mode cooked autrement dit le terminal basique */
{
	ReinitialisationTerminal(0);
	exit(0);
}

void main()
{
	int i;
	char caractere_ASCII;

	/* Différents signaux permettant dans des cas diverses tel que des erreurs de revenir à l'ancien terminal. */

	if ((int) signal(SIGINT,sigcatch) < 0)
	{
		perror("signal");
		exit(1);
	}
	if ((int)signal(SIGQUIT,sigcatch) < 0)
	{
		perror("signal");
		exit(1);
	}
	if ((int) signal(SIGTERM,sigcatch) < 0)
	{
		perror("signal");
		exit(1);
	}

	if(modeBrut(0) < 0) /* Sécurité si le mode brut ne fonctionne pas. */
	{
		fprintf(stderr,"Impossible de démarrer le mode brut.\n");
		exit(1);
	}

	/* Condition TANT_QUE permettant de décider quelle(s) touche(s) permet de quitter le mode brut lorsque celle(s)-ci sont appuyées + affichage du nombre ASCII 		de chaque touche. */

	while( (i = read(0, &caractere_ASCII, 1)) == 1)
	{
		if( (caractere_ASCII &= 255) == 32 )
			break;
		printf( "%o\n\r", caractere_ASCII);	

	}
	
	if(ReinitialisationTerminal(0) < 0) /* Sécurité si la réinitialisation ne fonctionne pas. */
	{
		fprintf(stderr, "Impossible de réinitialiser le terminal\n");
		exit(-1);
	}

	if(i < 0) /* Sécurité si erreur(s). */
	{
		fprintf(stderr,"Erreur.\n");
		exit(-1);
	}

	exit(0);
}

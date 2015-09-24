#include <prodcons.h>

int n;	/* global variable definition */

/*------------------------------------------------------------------------
 * xsh_prodcons - Producer Consumer Problem
 *------------------------------------------------------------------------
 */
shellcmd xsh_prodcons(int nargs, char *args[])
{
	/* Output info for '--help' argument */

	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
		printf("Usage: %s <integer> \n\n", args[0]);
		printf("Description:\n");
		printf("\tProducer Consumer Problem\n");
		printf("\t--help\tdisplays this help and exit\n");
		return 0;
	}
	
	if(nargs >2){
	/* throw error saying too many arguements */
		fprintf(stderr, "%s: too many arguements\n", args[0]);
		fprintf(stderr, "Try '%s --help' for more information\n",
			args[0]);
		return 1;
	}

	/* default count value of 2000 */
	int count = 2000;
	n = 0;

	if(nargs == 2){
	/* Assign value of arg to count */
		count = atoi(args[1]);
	}

	/* Create the producer & consumer and put them in the ready queue */
	resume( create(producer, 1024, 20, "producer", 1, count) );
	resume( create(consumer, 1024, 20, "consumer", 1, count) );
}

	

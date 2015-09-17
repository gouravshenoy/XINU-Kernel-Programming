/* xsh_hello.c - xsh_hello */

#include <xinu.h>
#include <string.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * xsh_hello - obtain and print a hello message
 *------------------------------------------------------------------------
 */

shellcmd xsh_hello(int nargs, char *args[]){

	/* Output info for '--help' argument */

	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
		printf("Usage: %s <string> \n\n", args[0]);
		printf("Description:\n");
		printf("\tDisplays a simple hello message\n");
		printf("\t--help\tdisplays this help and exit\n");
		return 0;
	}
	
	if(nargs <2){
	/* throw error saying too less arguements */
		fprintf(stderr, "%s: too less arguements\n", args[0]);
		fprintf(stderr, "Try '%s --help' for more information\n",
			args[0]);
		return 1;
	}
	
	if(nargs >2){
	/* throw error saying too many arguements */
		fprintf(stderr, "%s: too many arguements\n", args[0]);
		fprintf(stderr, "Try '%s --help' for more information\n",
			args[0]);
		return 1;
	}

	if(nargs == 2){
	/* Print the hello message */
		printf("\nHello %s, Welcome to the world of Xinu!!\n\n", args[1]);
		return 0;
	}

}


#include <future.h>

/* global variable definition */
int n;

/* global semaphores definition */
sid32 produced, consumed, mutex;
pid32 main_pid;

/*global futures definittion */
future *f_shared, *f_queue, *f_exclusive;

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
		return SYSERR;
	}
	
	if(nargs >2){
	/* throw error saying too many arguements */
		fprintf(stderr, "%s: too many arguements\n", args[0]);
		fprintf(stderr, "Try '%s --help' for more information\n",
			args[0]);
		return SYSERR;
	}
	

	if (nargs == 2 && strncmp(args[1], "-f", 7) == 0) {
	/* the -f option is enabled */
		
		main_pid = currpid;
		mutex = 0;
		
		printf("----- FUTURE_EXCLUSIVE -----\n");
		/* Allocate futures */
		f_exclusive = future_alloc(FUTURE_EXCLUSIVE);
		if(f_shared == NULL) {
			printf("Future Allocation Failed\n");
			return SYSERR;
		}

		/* Create the producer & consumer and put them in the ready queue */
		resume( create(future_cons, 1024, 20, "fcons1", 1, f_exclusive) );
		resume( create(future_cons, 1024, 20, "fcons1", 1, f_exclusive) );

		/* Delete the exclusive future */
		future_free(f_exclusive);

		printf("----- FUTURE_SHARED -----\n");
		/* Allocate futures */
		f_shared = future_alloc(FUTURE_SHARED);
		if(f_shared == NULL) {
			printf("Future Allocation Failed\n");
			return SYSERR;
		}

		/* Create the producer & consumer and put them in the ready queue */
		resume( create(future_cons, 1024, 20, "fcons2", 1, f_shared) );
		resume( create(future_cons, 1024, 20, "fcons3", 1, f_shared) );
		resume( create(future_cons, 1024, 20, "fcons4", 1, f_shared) );
		resume( create(future_cons, 1024, 20, "fcons5", 1, f_shared) );
		resume( create(future_prod, 1024, 20, "fprod2", 1, f_shared) );	
		
		sleep(1);

		printf("----- FUTURE_QUEUE -----\n");

		/* Allocate futures */
		f_queue = future_alloc(FUTURE_QUEUE);
		if(f_queue == NULL) {
			printf("Future Allocation Failed\n");
			return SYSERR;
		}

		resume( create(future_cons, 1024, 20, "fcons6", 1, f_queue) );
		resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
		resume( create(future_cons, 1024, 20, "fcons8", 1, f_queue) );
		resume( create(future_cons, 1024, 20, "fcons9", 1, f_queue) );
		resume( create(future_prod, 1024, 20, "fprod3", 1, f_queue) );	
		resume( create(future_prod, 1024, 20, "fprod4", 1, f_queue) );	
		resume( create(future_prod, 1024, 20, "fprod5", 1, f_queue) );
		resume( create(future_prod, 1024, 20, "fprod6", 1, f_queue) );	
		
		/* wait for a message */
		//receive();

		/* de-allocate the futures created */
		//future_free(f_shared);
		return OK;
	}
	else {
	/* Semapaphore calls */
		/* default count value of 2000 */
		int count = 2000;
		n = 0;
		
		/* Assign value of arg to count */
		
		if (nargs == 2){
			count = atoi(args[1]);
		}

		if(count <= 0) {
			fprintf(stderr, "Please enter a valid integer greater than 0\n");
			return SYSERR;
		}	
		
		/* initialize the semaphores */
		produced = semcreate(0);
		consumed = semcreate(1);

		/* Create the producer & consumer and put them in the ready queue */
		resume( create(producer, 1024, 20, "producer", 1, count) );
		resume( create(consumer, 1024, 20, "consumer", 2, count, currpid) );

		/* wait for a message to be received */
		receive();

		/* Delete the semaphores */
		semdelete(produced);
		semdelete(consumed);
	}

}

	

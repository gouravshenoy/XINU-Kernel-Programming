#include <network_future.h>

uint32 network_cons(future *fut, pid32 pid) {
	int i, status;
	fprintf(stdout, "Network_Cons called!\n");

	status = network_future_get(fut, &i);
	
	if (status < 1) {
		printf("network_cons | network_future_get failed\n");
		return SYSERR;
	}
	
	printf("Printing Value = %d\n\n", i);

	/* Send a message to parent */
	send(pid, "Completed");
	return OK;
}

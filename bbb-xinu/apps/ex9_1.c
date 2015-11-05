#include<xinu.h>

void print_addr()
{
	struct memblk *curr;
	curr = memlist.mnext;

	while(curr != NULL) {
		fprintf(stdout, "Address: 0x%08X and length: %8d\n", curr, curr->mlength);
		curr = curr->mnext;
	}

	return OK;
}

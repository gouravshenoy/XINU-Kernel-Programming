#include <memmgr.h>

/*------------------------------------------------------------------------
 * xsh_memmgr - memmgr implementation
 *------------------------------------------------------------------------
 */
int32 stkcount;

shellcmd xsh_memmgr(int nargs, char *args[])
{

	/*------------------------------------------------------------------------
	 * Ex 9.1
	 *------------------------------------------------------------------------
	 */
	pid32 pid;
	stkcount = 0;
	
	fprintf(stdout, "********** Ex 9.1 ***********\n");
	resume(create(print_addr, 1024, 20, "print_addr", 0));
	sleep(1);
	
	/*------------------------------------------------------------------------
	 * Ex 9.4
	 *------------------------------------------------------------------------
	 */	
	char *block = getmem_new(2048);
	fprintf(stdout, "\n\n********** Ex 9.4 ***********\n");
	printf("Allocated storage block: 0x%08X \n", block);

	resume(create(print_addr, 1024, 20, "print_addr", 0));
	sleep(1);
	
	freemem(block, 2048);
	printf("\nFree'd up block storage!\n\n");
	
	sleep(1);
	resume(create(print_addr, 1024, 20, "print_addr", 0));

	sleep(1);
	printf("\nDemonstrating the new getstk..\n");
	resume(create_9_4(fn_rec, 1024, 20, "rec", 1, 2));
	
	resume(create(print_addr, 1024, 20, "print_addr", 0));
	
	
	/*------------------------------------------------------------------------
	 * Ex 9.7

	 *------------------------------------------------------------------------
	 */
	sleep(1);
	fprintf(stdout, "\n\n********** Ex 9.7 ***********\n");
	resume(create_new(fn_rec, 1024, 20, "rec", 1, 10));
	fprintf(stdout, "The unused stack size = %d \n", stkcount);
	fprintf(stdout, "The max used stack size = %d \n", (1024-stkcount));

	return OK;
}

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

	fprintf(stdout, "Printing Free Memory List\n");
	resume(create(print_addr, 1024, 20, "print_addr", 0));
	
	/*------------------------------------------------------------------------
	 * Ex 9.4
	 *------------------------------------------------------------------------
	 */	
	char *block = getmem_new(2048);
	resume(create(print_addr, 1024, 20, "print_addr", 0));

	freemem(block, 1024);
	resume(create(print_addr, 1024, 20, "print_addr", 0));

	/*------------------------------------------------------------------------
	 * Ex 9.7
	 *------------------------------------------------------------------------
	 */
	resume(create_new(fn_rec, 1024, 20, "rec", 1, 10));	
	fprintf(stdout, "The unused stack size = %d \n", stkcount);
	fprintf(stdout, "The max used stack size = %d \n", (1024-stkcount));
	
	return OK;
}

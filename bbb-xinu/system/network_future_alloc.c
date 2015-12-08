/* future_alloc.c - future allocation */

#include <network_future.h>
/*----------------------------------------------------------------------------
 *  future alloc  -  Create a new future and return the future to tthe caller
 *----------------------------------------------------------------------------
 */
future* network_future_alloc(
	  int future_flag		/* Flag to be set for this future	*/
	)
{
	intmask mask;
	mask = disable();

	/* create a new future */
	future *fptr = (future *)getmem(sizeof(future));

	if(fptr == SYSERR){
		restore(mask);
		return NULL;
	}

	/* assign the flag */
	fptr->flag = future_flag;

	/* assign the furure state*/
	fptr->state = FUTURE_EMPTY;

	restore(mask);
	return fptr;

}


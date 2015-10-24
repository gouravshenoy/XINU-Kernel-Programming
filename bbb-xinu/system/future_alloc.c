/* future_alloc.c - future allocation */

#include <future.h>
/*----------------------------------------------------------------------------
 *  future alloc  -  Create a new future and return the future to tthe caller
 *----------------------------------------------------------------------------
 */
future* future_alloc(
	  int future_flag		/* Flag to be set for this future	*/
	)
{
	intmask mask;
	mask = disable();

	/* create a new future */
	future *fptr = (future *)getmem(sizeof(future));
	
	/* initialize the front & rear pointers */
	fptr->setq_front = fptr->setq_rear = fptr->getq_front = fptr->getq_rear = 0;

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


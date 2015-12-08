/* network_future_set.c - set the value of the future */

#include <network_future.h>

/*------------------------------------------------------------------------
 *  network_future_set  -  Set a value and changes state from FUTURE_EMPTY 
 *		   or FUTURE_WAITING to FUTURE_VALID
 *------------------------------------------------------------------------
 */
syscall network_future_set(
	  future* f,		/* Future to be set	*/
	  int* value		/* the value to be set into the future */
	)
{
	intmask mask;
	mask = disable();

	if(f->state == FUTURE_VALID){
		restore(mask);		
		return SYSERR;
	}
	else if(f->state == FUTURE_WAITING){
		//fprintf(stdout, "fut_set | waiting, setting: %d\n", *value);
		/* set the future value and state */
		f->value = *value;		
		f->state = FUTURE_VALID;				
	}
	else if(f->state == FUTURE_EMPTY){
		//fprintf(stdout, "fut_set | empty, setting\n");
		/* set the future value and state */
		f->value = *value;
		f->state = FUTURE_VALID;
	}
	restore(mask);
	return OK;

}

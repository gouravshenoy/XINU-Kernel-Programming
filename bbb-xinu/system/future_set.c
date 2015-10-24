/* future_set.c - set the value of the future */

#include <future.h>

/*------------------------------------------------------------------------
 *  future set  -  Set a value and changes state from FUTURE_EMPTY 
 *		   or FUTURE_WAITING to FUTURE_VALID
 *------------------------------------------------------------------------
 */
syscall future_set(
	  future* f,		/* Future to be set	*/
	  int* value		/* the value to be set into the future */
	)
{
	int i;
	intmask mask;
	mask = disable();

	/*------------------------------------------------------------------------
	 *  FUTURE_SHARED
	 *------------------------------------------------------------------------
	 */
	if(f->flag == FUTURE_SHARED) {
		if(f->state == FUTURE_VALID){
			restore(mask);		
			return SYSERR;
		}
		else if(f->state == FUTURE_WAITING) {
			/* set the future value and state */
			f->value = *value;
			f->state = FUTURE_VALID;

			/* dequeue all processes waiting */
			while(!isGetQueueEmpty(f)) {
				resume(remove_from_getq(f));
			}
		}
		else if(f->state == FUTURE_EMPTY){ 
			/* set the future value and state */
			f->value = *value;
			f->state = FUTURE_VALID;
		}
	} //end-if

	/*------------------------------------------------------------------------
	 *  FUTURE_QUEUE
	 *------------------------------------------------------------------------
	 */
	else if(f->flag == FUTURE_QUEUE) {
		if(isGetQueueEmpty(f)) {
			insert_in_setq(f, currpid);
			suspend(currpid);
			
			// after resumption
			f->value = *value;
			signal(mutex);
		}
		else {
			f->value = *value;
			resume(remove_from_getq(f));
		}
	} //end-if
	
	/*------------------------------------------------------------------------
	 *  OTHERS
	 *------------------------------------------------------------------------
	 */
	else {
		if(f->state == FUTURE_VALID){
			//restore(mask);		
			return SYSERR;
		}
		else if(f->state == FUTURE_WAITING){
			/* set the future value and state */
			f->value = *value;		
			f->state = FUTURE_VALID;				
		}
		else if(f->state == FUTURE_EMPTY){
			/* set the future value and state */
			f->value = *value;
			f->state = FUTURE_VALID;
		}
	} //end-else

	
	restore(mask);
	return OK;

}

/* future_get.c - get the value of the future */

#include <network_future.h>

/*------------------------------------------------------------------------
 *  network future get  -  Get the value of a future set by an operation and change 
 *		   the state of future from FUTURE_VALID to FUTURE_EMPTY
 *------------------------------------------------------------------------
 */
syscall network_future_get(
	  future* f,
	  int* value
	)
{
	intmask mask;
	mask = disable();

	if(f->state == FUTURE_VALID){
		*value = f->value;
		f->state = FUTURE_EMPTY;
	}
	else if(f->state == FUTURE_WAITING){
		restore(mask);
		return SYSERR;
	}
	else if(f->state == FUTURE_EMPTY){ 
		/*block waiting for it to set and store pid */
		f->pid = currpid;
		f->state = FUTURE_WAITING;
		
		/* busy wait on the future */
		while(1) {
			//fprintf(stdout, "fut_get | empty, waiting\n");
			if(f->state == FUTURE_VALID) {
				//fprintf(stdout, "fut_get | valid, reading: %d\n", f->value);
				/* read future value & break from loop */
				*value = f->value;
				f->state = FUTURE_EMPTY;
				break;
			}
			else {
				//fprintf(stdout, "Rescheduling\n");
				/* reschedule */
				resched();
			}
		}
	}

	restore(mask);
	return OK;
}

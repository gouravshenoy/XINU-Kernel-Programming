#include <prodcons.h>

void consumer(int count, pid32 pid)
{
	int i;

	for(i=1; i<=count; i++){
		/* Wait for an item to be produced */
		wait(produced);
		
		/* Consume the item */
		kprintf("Consumed: %d \n", n);

		/* Signal an item has been consumed */
		signal(consumed);
	}

	/* send message to parent */
	send(pid, "Consumer finished");
}

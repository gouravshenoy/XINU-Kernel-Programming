#include <prodcons.h>

void consumer(int count)
{
	int i;

	for(i=1; i<=count; i++){
		/* Wait for an item to be produced */
		wait(produced);
		
		/* Consume the item */
		printf("Consumed: %d \n", n);

		/* Signal an item has been consumed */
		signal(consumed);
	}
}

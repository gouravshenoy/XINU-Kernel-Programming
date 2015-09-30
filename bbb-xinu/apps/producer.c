#include <prodcons.h>

void producer(int count)
{		
	int i;

	for (i=1; i<=count; i++) {
		/* Wait till all values are consumed */		
		wait(consumed);
		
		/* Produce a value */
		n++;
		printf("Produced: %d \n", n);

		/* Signal that value has been produced */
		signal(produced);
	}
}

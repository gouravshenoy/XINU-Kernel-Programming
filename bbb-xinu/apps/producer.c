#include <prodcons.h>

void producer(int count)
{		
	int i;

	for (i=1; i<=count; i++) {
		n++;
		kprintf("Produced: %d \n", n);
	}
}

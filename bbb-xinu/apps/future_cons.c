#include <future.h>

uint32 future_cons(future *fut) {
	int i, status;
	status = future_get(fut, &i);
	
	if (status < 1) {
		kprintf("future_cons | future_get failed\n");
		return SYSERR;
	}
	
	printf("read value = %d\n\n", i);
	return OK;
}

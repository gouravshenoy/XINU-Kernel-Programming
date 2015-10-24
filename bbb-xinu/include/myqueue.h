/* include the prodcons header file */

#include <prodcons.h>

#ifndef _MYQUEUE_H_
#define _MYQUEUE_H_

/* Define future table entry struct */
typedef struct quent {
	pid32 pid;
	struct queue *qnext;
} queue;

/* Interface for queue call */
void myenqueue(queue *q, pid32 pid);
int32 mydequeue(queue *q);

#endif	/* _MYQUEUE_H_ */

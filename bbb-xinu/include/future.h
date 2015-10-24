#include <prodcons.h>

#ifndef _FUTURE_H_
#define _FUTURE_H_

/* define states */
#define FUTURE_EMPTY		0
#define FUTURE_WAITING		1
#define FUTURE_VALID		2

/* modes of operation for future */
#define FUTURE_EXCLUSIVE	1
#define FUTURE_SHARED 		2
#define FUTURE_QUEUE		3

#define MAX_SIZE		100

/* main program pid */
extern pid32 main_pid;

/* Define the future structure */
typedef struct futent
{
   int value;
   int flag;
   int state;
   pid32 pid;
   pid32 set_queue[MAX_SIZE];
   pid32 get_queue[MAX_SIZE];
   int32 setq_front, setq_rear, getq_front, getq_rear;
} future;

/* Interfaces for Queue calls */
void insert_in_setq(future *, pid32);
void insert_in_getq(future *, pid32);
pid32 remove_from_setq(future *);
pid32 remove_from_getq(future *);

/* Interfaces for system call */
future* future_alloc(int future_flags);
syscall future_free(future*);
syscall future_get(future*, int*);
syscall future_set(future*, int*);

/* function prototypes */
uint32 future_cons(future*);
uint32 future_prod(future*);

#endif /* _FUTURE_H_ */



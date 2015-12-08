#include <prodcons.h>

#ifndef _NETFUTURE_H_
#define _NETFUTURE_H_

/* define states */
#define FUTURE_EMPTY	0
#define FUTURE_WAITING	1
#define FUTURE_VALID	2

/* modes of operation for future */
#define FUTURE_EXCLUSIVE 1

typedef struct futent
{
   int value;
   int flag;
   int state;
   pid32 pid;
} future;

/* Interfaces for system call */
future* network_future_alloc(int future_flags);
syscall network_future_free(future*);
syscall network_future_get(future*, int*);
syscall network_future_set(future*, int*);

/* function prototypes */
uint32 network_cons(future*, pid32);

#endif /* _NETFUTURE_H_ */

#include <xinu.h>

/* Global variable for producer consumer */
extern int n; /* declaration */

/* Declare the required semaphores */
extern sid32 consumed, produced, mutex;

/* function prototypes */
void consumer(int count, pid32 pid);
void producer(int count);

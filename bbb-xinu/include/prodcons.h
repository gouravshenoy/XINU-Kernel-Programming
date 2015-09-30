#include <xinu.h>

/* Global variable for producer consumer */
extern int n; /* declaration */

/* Declare the required semaphores */
extern sid32 consumed, produced;

/* function prototypes */
void consumer(int count);
void producer(int count);

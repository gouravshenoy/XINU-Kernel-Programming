#include <xinu.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* Global variable for producer consumer */
extern int n; /* declaration */

/* function prototypes */
void consumer(int count);
void producer(int count);

# REPORT ASSIGNMENT 3

###How exactly is sychronization achieved using semaphore in our assignnment?

Ans) Syncronisation is achieved using two semaphores, produced and consumed. Initially, the produced semaphore's count is set to 0 and the consumed semaphore's
count is set to 1.
When the producer code first enters the for loop, it calls wait(consumed) which decrements the count of semaphore consumed to 0. Since the value is non-negative, it is not blocked and enters the critical section where it produces value into global variable n. Once it is done using the critical section, it calls signal(produced) which increaments the value of count of semaphore produced to 1. In the next iteration of the loop, wait(consumed) is called again which decreaments the count of semaphore consumed from 0 to -1. Since the value is negative, the producer process is blocked and placed in the consumed semaphore's queue and is brought back to the ready state when the consumer process calls signal(consumed).

Now, when the consumer code enters the for loop, it calls wait(produced) which decrements the count of semaphore produced from 1 to 0. Since the value is non-negative, it is not blocked and enters the critical section where it consumes the value of the global variable n. Once it is done using the critical section, it calls signal(consumed), which increaments the value count of semaphore consumed which was -1 to 0 and unblocks the producer process which was in the
queue of semaphore consumed.

To summarize,
The producer code first calls wait(consumed) and is blocked if the count of consumed semaphor is negative(This shows that the consumer process is in the critical section of using the global variable). Similarly, the consumer code first calls wait(produced) and is blocked if the count of produced semaphor is negative.( This mean that the producer process is in the critical section).

Once the producer code is done using the critical section, it calls signal(produced) so that any process(consumer code in this case) waiting on the semaphore is moved to the ready queue. Similarly, when the consumer code is done using the critical section for each iteration, it calls signal(consumed), so that any process(producer process in this case) waiting on the semaphore is moved to the ready queue

### Can the above sychronization be achieved with just one semphore? Why or why not?

No, we cant use one semaphore to handle the producer-consumer synchronisation.

Consider we use just one semaphore say "sem" and initialise its count to 1. The producer code will enter the loop and call wait(sem) which will decreament the count from 1 to 0. Since its non-negative, it enters critical section and once done it calls signal(sem) which will bring the count value back to 1. Now during the next iteration, it will again call wait(sem) which gets the count value to 0 and so it will overwrite the value of the global variable n even before it was consumed by the consumer code.

Also, consider the case when the consumer code executes before the producer code. It calls wait(sem) and decreamets the value from 1 to 0. Since its non-negative, it consumes the value of n even before it could be produced by producer code.

### Also write down all the functions in the project.

Following functions used:

* **PRODUCER**
```c
void producer(int count);
```
> _This is a user defined function with input parameter "count" and produces count number of items
in n(global variable)_

* **CONSUMER**
```c
void consumer(int count);
```
> _This is a user defined function with input parametr "count" and consuming n, "count" number of times._

* **RESUME**
```c
pri16 resume(pid32 pid);
```
> _It unsuspends a process, making it ready_

> Input parameter: pid  [This is the process id of the process to unsuspend]

> Return value: Returns the priority

* **CREATE**
```c
pid32 create(void		*procaddr,/* procedure address		*/
	  uint32	ssize,		/* stack size in words		*/
	  pri16		priority,	/* process priority > 0		*/
	  char		*name,		/* name (for debugging)		*/
	  uint32	nargs,		/* number of args that follow	*/
	  ...
	)
```
> _create a process to start running a procedure_

> Return value: The process id

* **SEMCREATE**
```c
sid32	semcreate(
	  int32		count		/* Initial semaphore count	*/
	)
```
> _Create a new semaphore and return the ID to the caller_

> Input parameter: count  [This is the initial semaphore count]

> Return value: Returns the semphore id

* **SEMDELETE**
```c
syscall	semdelete(
	  sid32		sem		/* ID of semaphore to delete	*/
	)
```
> _Delete a semaphore by releasing its table entry_

* **WAIT**
```c
syscall	wait(
	  sid32		sem		/* Semaphore on which to wait  */
	)
```
> _Cause current process to wait on a semaphore_

* **SIGNAL**
```c
syscall	signal(
	  sid32		sem		/* ID of semaphore to signal	*/
	)
```
> _Signal a semaphore, releasing a process if one is waiting_

### Note the tasks of the group members who developed the various components
* Gourav: producer code
* Erika: Consumer code

_**The rest have been done collaboratively and has been a joint effort**_





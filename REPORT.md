# REPORT ASSIGNMENT 2

### Q: Does your program output any garbage? If yes, Why?
A: No! The program does not output any garbage value, but what is observed is that the output is totally out of sync. The producer and consumer processes execute at erratic times and hence the produced and consumed values overlap due to lack of synchronization between the 2 processes.

### Q: Are all the produced values getting consumed? Check your program for a small count like 20.
A: No! All the produced values aren't getting consumed by the consumer. In fact due to lack of synchronization between the producer and consumer processes, the output response pattern is very unpredictable - There is an unsynchronized overlap between the producer & consumer processes. What is observed is that the producer produces items and the consumer is not able to consume all that has been produced. Rather due to lack of sync, the consumer process executes & consumes a very small or sometimes a negligible amount of what has been produced. For e.g.: If we give a count value of 20, the producer might generate 1,2,3...10 & then the consumer process comes up consuming 10,10,10 & then again the producer process comes up and produces 10,11..20 and consumer then comes up consuming 20,20,20... (which is the current 'n') value. So there is absolutely no sync between the 2 processes and consumer is not able to consume all that has been produced!

### Also write down all the functions in the project.

There are four functions used:

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

### Note the tasks of the group members who developed the various components
* Gourav: producer code
* Erika: Consumer code

_**The rest have been done collaboratively and has been a joint effort**_

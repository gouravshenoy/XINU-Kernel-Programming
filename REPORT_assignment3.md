How exactly is sychronization achieved using semaphore in our assignnment?

Ans) Syncronisation is achieved using two semaphores, produced and consumed. Initially, the produced semaphore's count is set to 0 and the consumed semaphore's
count is set to 1.
When the producer code first enters the for loop, it calls wait(consumed) which decrements the count of semaphore consumed to 0. Since the value is non-negative,
it is not blocked and enters the critical section where it produces value into global variable n. Once it is done using the critical section, it calls
signal(produced) which increaments the value of count of semaphore produced to 1. In the next iteration of the loop, wait(consumed) is called again which decreaments
the count of semaphore consumed from 0 to -1. Since the value is negative, the producer process is blocked and placed in the consumed semaphore's queue and is
brought back to the ready state when the consumer process calls signal(consumed).

Now, when the consumer code enters the for loop, it calls wait(produced) which decrements the count of semaphore produced from 1 to 0. Since the value is 
non-negative, it is not blocked and enters the critical section where it consumes the value of the global variable n. Once it is done using the critical section,
it calls signal(consumed), which increaments the value count of semaphore consumed which was -1 to 0 and unblocks the producer process which was in the
queue's list of semaphore consumed.

To summarize,
The producer code first calls wait(consumed) and is blocked if the count of consumed semaphor is negative(This shows that the consumer process is in
the critical section of using the global variable). Similarly, the consumer code first calls wait(produced) and is blocked if the count of produced semaphor is
negative.( This mean that the producer process is n the critical section).

Once the producer code is done using the critical section, it calls signal(produced) so that any process(consumer code in this case) waiting on the semaphore is moved
to the ready queue. Similarly, when the consumer code is done using the critical section for each iteration, it calls signal(consumed), so that any process(producer
process in this case) waiting on the semaphore is moved to the ready queue

# Threads_EX
https://github.com/Amit040802/Threads_EX




### Task 3
We created a single object with a shared field 'bar' that is initialized to 0 when we create 'foo'. 
We then create an array of 2 threads. Each thread runs a loop of 10,000 iterations and calls 'f.baz()' that execute 'bar++', for each. 
When running the code we should get 20,000 (2 threads × 10,000) but we dont get it for this reason:'
the expression 'bar++' is not atomic action, and implemented as three separate steps:  
1) read the current value of 'bar' from memory.
2) add 1.
3) write the new value back to memory.
When two threads execute 'bar++' together, they can both read the same old value, adding 1, and then write it back. 
In that case one update is lost, this happend when two threads update the same shared variable at the same time.
example of what can happen:

Thread A reads bar = 2020
Thread B reads bar = 2020

Thread A increase the value and writes bar = 2021
Thread B increase the (old) value and writes bar = 2021

The final value increased only once (one update is lost).



### Task 4
When method declared as synchronized, then lock of the current object (this) before executing the method, and releases it when the method returns. 
This means that for a given 'Foo' instance, only one thread at a time is allowed to execute the synchronized methods.

Before this change, 'bar++' was not atomic. Two threads could read the same old value of bar, increase it, and write it back, and one update would be lost. 
s a result, the final value of bar was smaller than 20,000 even though each of the threads performed 10,000 increases.

After adding synchronized, only one thread can run 'baz' at a time on the shared object 'Foo, so the program prints the correct result: 20000.



### Task 5
This version uses an synchronized block, The lock is taken on 'this', which is similar to the synchronized method.
only one thread at a time can enter the synchronized(this) block for the same Foo object, the increase 'bar++' is protected, and the result is always 20,000.
Synchronized method locks the entire method, while a synchronized(this) block allows us to synchronize only a specific section of the code what gives us more contro.



### Task 6
The theoretical result for bar should be: 100,000,000
10 threads, each performing 10,000,000 increas.
But we get difrent output, This is because 'bar++' is not atomic action .
Multiple threads execute 'bar++' together, so they sometimes read the same old value of bar, increase it, and write it back, causing lost updates.

The second number is the total running time in milliseconds.
In this version the time is short, because there is no locking: all threads run in parallel without waiting for each other. 
The result is fast but incorrect.



### Task 7
This time, the first number is always 100,000,000.
The reason is synchronized(this) makes the increse protected section by a lock on the Foo object.
Only one thread at a time can enter the synchronized(this) block, so 'bar++' is no longer executed together, No updates are lost and the final result is correct.
However, the time is now much larger than in Task 6.
All 10 threads must acquire the same lock lots of times. This forces the threads to wait and perform many context switches. 
Conclusion: We pay a significant performance cost for using synchronization.
Task 6 and 7 demonstrate the trade-off:

-Without synchronization: fast but incorrect.

-With synchronization: correct but slower.

# REPORT 
### Vanshika Dhingra (2021101092)
### Vrinda Agarwal (2021101110)

>MacOS Monterey

*  Following is the report for the fourth assignment of Operating Systems & Networks course at IIIT Hyderabad.
The purpose of xv6 is to explain the main concepts of Operating systems by looking at an example Kernel.

* > Specification 2: Scheduling 

   * > First Come First Come (FCFS) 

Let us understand what FCFS does, whenever a process comes to the CPU it is executed. In case of multiple processes, the process which comes first is executed first.
Description of the implementation: 
  * We first made changes in the MAKEFILE to support Scheduler macro for compilation of the scheduling algorithm.

  * Then in the Kernel folder go to proc.c file , to declare a variable createTime.

  *  Initialising the createTime variable in proc.c file within the allocproc() function.

  *  Implementing the scheduling functionality of FCFS algorithm in scheduler function in proc.c file , here the process with least createTime is selected from the available processes.

  *  The yield()  function in trap.c has been disabled to prevent the process from restarting after the clock interrupts.
  *  we first iterate over all process and find the process with the least create time and is in the input queue i.e. ready to run and put that to running .

### values
#### Average rtime 26,  wtime 119

  * > Priority Based Scheduking (PBS)

  In Priority Based Scheduling algorithm the process is assigned to the CPU , the process which is assigned has the highest priority among all present.

  Description of the implementation:
   * We start off by adding variables to the struct proc in kernel/proc.c.There datatypes is uint and the variables names are createTime, startTime,exitTime,runTime,waitTime,sleepTime,totalRunTime,num_runs,priority.

   * Then in kernel/proc.c we initialise all of these variables to their respective values in the allocproc() function.

   * Further,we add the functionality of the PBS algorithm in the code.This is done by firstly declaring a nice variable and applying our PBS formula to it.

   * Then,we created a function named set_priority() in the proc.c file which basically which first iterrates through all the process first ,locking them, if the process is found then old priority is set otherwise new priority is set,followed by unlocking the process.Id the priority of the process is lower we yield the CPU,else we break out from the loop.

   * Furthermore in user folder, setpriority.c we define our own main program  which sets the priorities of the process passed in the arguements and returns an error if the function fails to setup the priority.

   * The last step involves adding the sys_set_priority() system call in sysproc.c under the kernel folder.

### values
#### Average rtime 13,  wtime 127

  * > Lottery Based Scheduling (LBS)

  Process scheduling of the lottery variety is slightly unique from normal scheduling. Random scheduling is used for scheduling processes. Implementing  a preemptive scheduler that gives each process a time slice at random based on how many tickets it possesses. This means that the likelihood that the process executes in a particular time slice depends on the number of tickets it owns.

  Description of the implementation:

  * The first step involves making a system call which helps us in setting the tickets.The name of this syscall is sys_settickets.

  * Then for generating the random number we have made two files rand.c and rand.h which are included in the Kernel folder.This will be responsible for scheduling all the processes.
  
  * The last step involves making a scheduler function wherein we count the total number of tickets for all processes that are runnable.This also counts the total no of tickets.

  * The implementation idea revolves around using the lottery scheduler function we calculate the total no of tickets.Then using the random number generator number a number between 0 and total no of tickets is generated.After this we iterate over the for loop which runs through all the processes counting the number of processes that are in the RUNNABLE state.When the total number of tickets validated exceeds the random number we received, we repeat the process.

### values
#### Average rtime 13,  wtime 150

  * > Multi-level Feedback Scheduling Algorithm (MLFQ)

    A process is assigned to a CPU using the scheduling mechanism known as Multilevel Feedback Queue (MLFQ). The task with the highest priority is the one that gets given the CPU. The quantity of times a process has been given CPU priority determines its priority. When a process is assigned to the CPU, its priority rises by one (CPU Bursts). When the process has done running, its priority is reduced by one (IO Bursts).

    Description of the implementation:
    
    * The priority, allocated time, times dispatched , times added to the queue, and times spent in each queue were modified in the struct proc.

    * The above created variables were initialised in the allocproc() function in proc.c file.

    * Then we created 5 queues each having different priorities.

    * Then we made editions in the scheduler() function which runs the process with highest priority.

    * Further, in the clockintr() function we made changes so that we can track runtime, add processes to the queue and handle aging.

    * Furthermore, we made changes in the  kerneltrap() and usertrap() functions  to yield when process has exhausted its time slice.

* > Specification 3 : Copy-on-write fork 
   COW, or copy on write, is a resource management strategy. Its primary application is the fork system call implementation, in which it distributes the operating system's virtual memory (pages). 

   The fork() system call in an operating system similar to UNIX generates a copy of the parent process that is referred to as the child process. 

   The concept of copy-on-write is that when a parent process creates a child process, both processes initially share the same memory pages and these shared pages will be marked as copy-on-write, meaning that if any of these processes try to modify the shared pages, only a copy of these pages will be created and the modifications will be done.

   Description of the implementation:

   * Instead of allocating additional pages, alter uvmcopy() to move the parent's physical pages into the child. In the PTEs of the parent and kid, clear PTE_W.Making those parent pages that are tagged as writable become unwritable pages and using a new bit to mark them as COW pages are both necessary. By doing this, we can allow parents and kids to share reading pages, and when new COW pages are needed for writing, we can create them.

   * Modified usertrap() to detect page errors. Allocate a new page with kalloc() when a page fault occurs on a COW page, copy the problematic page to the new page, then install the new page in the PTE with PTE W set. 
  
   It should be noted that this only affects the active process, so we simply set aside a page for the cow page and map the new page to the pagetable. To release the previous page, which becomes a cow page if no process owns it, we must call kfree().

   * Changes in copyout()- When copyout() comes across a COW page, it should be changed to use the same scheme as page faults.



















//For Assignment 1 here is a possible template to start from...

//========================================================================================================================================================


#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <inttypes.h>

//========================================================================================================================================================
//#defines
#define MAX_THREAD_COUNT 9
#define MAX_TASK_COUNT 9



//========================================================================================================================================================
//Typedefs

typedef struct{
	int threadCount;
	pthread_t threadId;
	int threadPolicy;
	int threadPri;
	long processTime;
	int64_t timeStamp[MAX_TASK_COUNT+1];
	time_t startTime;
	time_t endTime;
} ThreadArgs;

//Globals

//Try to change this to use a single condition variable
pthread_mutex_t g_ThreadMutex [MAX_THREAD_COUNT];
pthread_cond_t g_conditionVar [MAX_THREAD_COUNT];
ThreadArgs g_ThreadArgs[MAX_THREAD_COUNT];

//========================================================================================================================================================

void InitGlobals(void)
{
// Initialize all globals
	g_ThreadMutex;
	g_conditionVar;
	g_ThreadArgs;
}


//========================================================================================================================================================
void DisplayThreadSchdAttributes( pthread_t threadID, int policy, int priority )
{

	printf("\nDisplayThreadSchdAttributes:\n threadID = 0x%lx\n policy = %s\n priority = %d\n",
									threadID,
									(policy == SCHED_FIFO) ? "SCHED_FIFO" :
									(policy == SCHED_RR)	? "SCHED_RR" :
									(policy == SCHED_OTHER) ? "SCHED_OTHER" :
									"???",
									priority);
}

//========================================================================================================================================================
void DisplayThreadArgs(ThreadArgs*	myThreadArg)
{
int i,y;

	if( myThreadArg )
	{
	DisplayThreadSchdAttributes(myThreadArg->threadId, myThreadArg->threadPolicy, myThreadArg->threadPri);
	printf(" startTime = %s endTime = %s", ctime(&myThreadArg->startTime), ctime(&myThreadArg->endTime));
	printf(" TimeStamp [%"PRId64"]\n", myThreadArg->timeStamp[0] );

		for(y=1; y<MAX_TASK_COUNT+1; y++)
		{
			printf(" TimeStamp [%"PRId64"] Delta [%"PRId64"]us\n", myThreadArg->timeStamp[y],
			(myThreadArg->timeStamp[y]-myThreadArg->timeStamp[y-1]));
		}
	}
}

//========================================================================================================================================================
void DoProcess(void)
{
	unsigned int longVar =1 ;

	while(longVar < 0xffffffff) longVar++;
}

//========================================================================================================================================================


void* threadFunction(void *arg)
{
	ThreadArgs*	myThreadArg;
	myThreadArg = (ThreadArgs*)arg;
	if (myThreadArg.threadCount == 1 || myThreadArg.threadCount == 2 || myThreadArg.threadCount == 3) {
		int pthread_setscheduleparam(myThreadArg.threadId, SCHED_OTHER, &param);
	}
	/*1.	Typecast the argument to a �ThreadArgs*� variable
	2.	Use the �pthread_setscheduleparam� API to set the thread policy
	3.	Init the Condition variable and associated mutex
	4.	Wait on condition variable
	5.	Once condition variable is signaled, use the �time� function and the �clock_gettime(CLOCK_REALTIME, &tms)� to get timestamp
	6.	Call �DoProcess� to run your task
	7.	Use �time� and �clock_gettime� to find end time.
	8.	You can repeat steps 6 and 7 a few times if you wish */
}
//========================================================================================================================================================
int main (int argc, char *argv[])
{
	InitGlobals();
	ThreadArgs myThreadArgs;
	pthread_t thread1, thread2, thread3, thread4, thread5, thread6, thread7, thread8, thread9;
	pthread_create( &thread1, (void*) SCHED_OTHER, &threadFunction, NULL);
	/*pthread_create( &thread2, (void*) SCHED_OTHER, &threadFunction, NULL);
	pthread_create( &thread3, (void*) SCHED_OTHER, &threadFunction, NULL);
	pthread_create( &thread4, (void*) SCHED_FIFO, &threadFunction, NULL);
	pthread_create( &thread5, (void*) SCHED_FIFO, &threadFunction, NULL);
	pthread_create( &thread6, (void*) SCHED_FIFO, &threadFunction, NULL);
	pthread_create( &thread7, (void*) SCHED_RR, &threadFunction, NULL);
	pthread_create( &thread8, (void*) SCHED_RR, &threadFunction, NULL);
	pthread_create( &thread9, (void*) SCHED_RR, &threadFunction, NULL);*/
	myThreadArgs.threadCount = 1;
	pthread_attr_t threadAttrib;
	while(myThreadArgs.threadCount < MAX_THREAD_COUNT)
	{
		if( pthread_create(&(g_ThreadArgs[myThreadArgs.threadCount].threadId), &threadAttrib, &threadFunction, &g_ThreadArgs[myThreadArgs.threadCount])) {
			printf("This thread has failed: %lu\n", &(g_ThreadArgs[myThreadArgs.threadCount].threadId));
		}

		myThreadArgs.threadCount++;
	}
	pthread_join(thread1, NULL);
	/*pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	pthread_join(thread4, NULL);
	pthread_join(thread5, NULL);
	pthread_join(thread6, NULL);
	pthread_join(thread7, NULL);
	pthread_join(thread8, NULL);
	pthread_join(thread9, NULL);
/*	1.	Call InitGlobals
	2.	Create a number of threads (start with 1 and increase to 9) using �pthread_Create�
	3.	Assign 3 threads to SCHED_OTHER, another 3 to SCHED_FIFO and another 3 to SCHED_RR
	4.	Signal the condition variable
	5.	Call �pthread_join� to wait on the thread
	6.	Display the stats on the threads*/
}




//========================================================================================================================================================



/*

************* HINTS ******************

========================================================================================================================================================
Every time you run into issues with usage of an API, please look up samples on how that API is used here...

http://www.yolinux.com/TUTORIALS/LinuxTutorialPosixThreads.html

========================================================================================================================================================


Please check the return values from all system calls and print an error message in all error cases including the error code.. That will help catch errors quickly.
========================================================================================================================================================


You can use the following technique to pass the address of the element corresponding to a particular thread to the thread function...

	void* threadFunction(void *arg)
	{
		ThreadArgs*	myThreadArg;

		myThreadArg = (ThreadArgs*)arg;

	}


	int main (int argc, char *argv[])
	{

		while(threadCount < MAX_THREAD_COUNT)
		{
		...
			if( pthread_create(&(g_ThreadArgs[threadCount].threadId), &threadAttrib, &threadFunction, &g_ThreadArgs[threadCount]) )
		...

		}
	}
========================================================================================================================================================

Here is the usage for clock_gettime�

	clock_gettime(CLOCK_REALTIME, &tms);
	myThreadArg->timeStamp[y+1] = tms.tv_sec *1000000;
	myThreadArg->timeStamp[y+1] += tms.tv_nsec/1000;
	if(tms.tv_nsec % 1000 >= 500 ) myThreadArg->timeStamp[y+1]++;

========================================================================================================================================================

Here is how you wait on a condition event�

	pthread_mutex_lock ( &g_ThreadMutex[myThreadArg->threadCount] );
	pthread_cond_wait ( &g_conditionVar[myThreadArg->threadCount], &g_ThreadMutex[myThreadArg->threadCount] );
	pthread_mutex_unlock( &g_ThreadMutex[myThreadArg->threadCount] );

========================================================================================================================================================

Note that this sample is changing the policy of the current thread... so if you follow this sample, make sure you are making the call from the thread function.


	http://man7.org/linux/man-pages/man3/pthread_setschedparam.3.html

	if (main_sched_str != NULL) {
	if (!get_policy(main_sched_str[0], &policy))
		usage(argv[0], "Bad policy for main thread (-m)\n");
		param.sched_priority = strtol(&main_sched_str[1], NULL, 0);

	s = pthread_setschedparam(pthread_self(), policy, &param);
	if (s != 0)
		handle_error_en(s, "pthread_setschedparam");
	}

========================================================================================================================================================
For those confused about my comment on trying to using a single Condition variable instead of an array... please read the following...

http://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_cond_signal.html

You can use the broadcast API to wake multiple threads waiting on the same condition variable.

For those who really like to go deeper, know that you have access to the code for most of the Linux system APIs... here is the code pthread_cond_broadcast...

https://code.woboq.org/userspace/glibc/nptl/pthread_cond_broadcast.c.html

========================================================================================================================================================
*/

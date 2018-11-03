//assignment 1
//Note: I used cc -pthread Assignment1.c to compile
//and ./a.out to run since that is what was used on
//the linux tutorial. gcc Assignment1.c -lpthread also
//seems to compile
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void *print_message_function(void *ptr);

typedef struct thread {
  unsigned long int threadID; //use pthread_self()
  char policy[12];
  int priority;
  char startTime[100];
  char endTime[100];
  long int startTimeStamp;
  long int endTimeStamp;
} statistics[9];

int main() {
  statistics threadstats;
  pthread_t mainThread,thread1;
  mainThread = pthread_self();
  const char *message1 = "Main Thread";
  const char *message2 = "thread 1";
  int iret1 = pthread_create( &mainThread, NULL, print_message_function, (void*) message1);
  int iret2 = pthread_create( &mainThread, NULL, print_message_function, (void*) message2);
  /*if(iret1) {
    fprintf(stderr, "Error - pthread_create() return code: %d\n", iret1);
    exit(EXIT_FAILURE);
  }*/
  pthread_join(mainThread, NULL);
  pthread_join(thread1, NULL);
  exit(EXIT_SUCCESS);
}

void *print_message_function(void *ptr) {
  printf("%lu\n",pthread_self());
  return NULL;
}

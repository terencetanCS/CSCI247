//assignment 1
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void *print_message_function(void *ptr);

int main() {
  pthread_t thread1;
  const char *message1 = "Thread 1";
  int iret1 = pthread_create( &thread1, NULL, print_message_function, (void*) message1);
  if(iret1) {
    fprintf(stderr, "Error - pthread_create() return code: %d\n", iret1);
    exit(EXIT_FAILURE);
  }
  pthread_join(thread1, NULL);
  exit(EXIT_SUCCESS);
}

void *print_message_function(void *ptr) {
  char *message = (char *) ptr;
  printf("%s\n", message);
}

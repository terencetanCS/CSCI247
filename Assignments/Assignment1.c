//assignment 1
#include <stdio.h>
#include <pthread.h>
void *print_message_function(void *ptr);
int main() {
  pthread_t thread1;
  const char *message1 = "Thread 1";
  int iret1 = pthread_create( &thread1, NULL, print_message_function, (void*) message1);

}

void *print_message_function(void *ptr) {
  char *message = (char *) ptr;
  printf("%s\n", message);
}

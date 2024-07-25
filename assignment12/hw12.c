// name: Fang Huang
// email: huang.fang@northeastern.edu
// Compile with:
//
// gcc -lpthread hw12.c -o hw12
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> 

#define NTHREADS 100

// shared variable
int counter = 0;

// thread to be executed - unspecified variable arguments
void* thread1 (void* vargp) {
  // add 1 to counter
	usleep(rand()%1000);
	counter = counter +1;
	return NULL;
}

void* thread2 (void* vargp) {
  // add 5 to counter
  // *** YOUR CODE GOES HERE ***
	usleep(rand()%1000);
	counter = counter + 5;
	return NULL;
}

void* thread3 (void* vargp) {
  // subtract 2 from counter
  // *** YOUR CODE GOES HERE ***
	usleep(rand()%1000);
	counter = counter - 2;
	return NULL;
}

void* thread4 (void* vargp) {
  // subtract 10 from counter
  // *** YOUR CODE GOES HERE ***
	usleep(rand()%1000);
	counter = counter - 10;
	return NULL;
}

int main() {
  // array to keep Pthread IDs of created threads
  pthread_t tid[NTHREADS * 4];
  int thread_indices[NTHREADS * 4];
  int i;

  srand(time(NULL)); // seed the random number generator

  printf("Counter starts at %d\n", counter);

  // initialize thread indices
  for (i = 0; i < NTHREADS * 4; ++i) {
    thread_indices[i] = i;
  }

  // shuffle thread indices to randomize creation order
  for (i = NTHREADS * 4 - 1; i > 0; --i) {
    int j = rand() % (i + 1);
    int temp = thread_indices[i];
    thread_indices[i] = thread_indices[j];
    thread_indices[j] = temp;
  }

  // create and run the threads in random order
  for (i = 0; i < NTHREADS * 4; ++i) {
    int idx = thread_indices[i];
    if (idx < NTHREADS) {
      pthread_create(&(tid[idx]), NULL, thread1, NULL);
    } else if (idx < 2 * NTHREADS) {
      pthread_create(&(tid[idx]), NULL, thread2, NULL);
    } else if (idx < 3 * NTHREADS) {
      pthread_create(&(tid[idx]), NULL, thread3, NULL);
    } else {
      pthread_create(&(tid[idx]), NULL, thread4, NULL);
    }
  }

  //wait until all threads are done
  for (i=0; i < NTHREADS*4; ++i){
    pthread_join(tid[i], NULL);
  }

  printf("Counter ends at %d\n", counter);

  return 0;
}

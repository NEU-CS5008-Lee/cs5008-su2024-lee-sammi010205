//Fang Huang
//huang.fang@northeastern.edu

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t chopstick[5]; // lock variables for chopsticks
pthread_mutex_t lock; // single lock to control access to critical section
int eat_count[5] = {0}; // array to keep track of how many times each philosopher has eaten
int total_meals = 0; // total number of meals eaten by all philosophers
const int max_eat_count = 3; // maximum number of times each philosopher can eat
const int num_philosophers = 5; // number of philosophers

// Thread to be executed
void *philosopher(void *x)
{
    //Treat variable x as a pointer to an int and then extract the value into n
    int* a=(int*)x;
    int n=*a;
    
    /*-----Insert your code here----*/

    while (1) {
        // Philosopher is thinking
        printf("Philosopher %d is thinking.\n", n);
        sleep(1);

        // Lock the critical section
        pthread_mutex_lock(&lock);
        
        if (total_meals >= num_philosophers * max_eat_count) {
            pthread_mutex_unlock(&lock);
            break;
        }

        // Pick up chopsticks
        pthread_mutex_lock(&chopstick[n]); // pick up left chopstick
        pthread_mutex_lock(&chopstick[(n + 1) % 5]); // pick up right chopstick

        // Unlock the critical section
        pthread_mutex_unlock(&lock);

        // Philosopher is eating
        printf("Philosopher %d is eating.\n", n);
        sleep(2);
        
        // Increment eat count
        pthread_mutex_lock(&lock);
        eat_count[n]++;
        total_meals++;
        pthread_mutex_unlock(&lock);
        
        // Put down chopsticks
        pthread_mutex_unlock(&chopstick[n]); // put down left chopstick
        pthread_mutex_unlock(&chopstick[(n + 1) % 5]); // put down right chopstick

        // Philosopher is done eating
        printf("Philosopher %d is done eating %d times.\n", n, eat_count[n]);
        sleep(1);
    }
    
    return NULL;
    
}


/*------------ Main Program---------*/
int main()
{
    int i,val[5];
    pthread_t threads[5];
    //initializing the mutex (for chopsticks)
    for(i=0;i<5;i++){
        pthread_mutex_init(&chopstick[i],NULL);
    }   

    //create and run the thread
    for(i=0;i<5;i++){
        val[i]=i;
        pthread_create(&threads[i],NULL,(void *)philosopher,&val[i]);
    }
    
    //wait until all the threads are done
    for(i=0;i<5;i++){
        pthread_join(threads[i],NULL);
    }
    
    // Destroying the mutex
    for(i=0;i<5;i++){
        pthread_mutex_destroy(&chopstick[i]);
    }
    
    return 0;
}
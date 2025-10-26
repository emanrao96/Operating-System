#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUM_THREADS 5

// Thread function
void* threadFunction(void* arg) {
    int threadNum = *((int*)arg); // Get thread number
    pthread_t threadID = pthread_self(); // Get thread ID

    printf("Thread %d started (ID: %lu)\n", threadNum, threadID);

    // Sleep for 1–3 seconds randomly
    int sleepTime = rand() % 3 + 1;
    sleep(sleepTime);

    printf("Thread %d (ID: %lu) finished after %d seconds\n",
           threadNum, threadID, sleepTime);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int threadNumbers[NUM_THREADS];
    srand(time(NULL)); // Seed random number generator

    printf("Creating %d threads...\n\n", NUM_THREADS);

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        threadNumbers[i] = i + 1;
        pthread_create(&threads[i], NULL, threadFunction, &threadNumbers[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nAll threads completed.\n");
    return 0;
}
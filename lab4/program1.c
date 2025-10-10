#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/* Thread function: runs in the new thread */
void* thread_function(void* arg) {
    (void)arg; // unused here
    printf("Hello from the new thread!\n");
    /* pthread_self() returns a pthread_t; cast to unsigned long for printing */
    printf("New thread ID: %lu\n", (unsigned long)pthread_self());
    return NULL;
}

int main(void) {
    pthread_t thread_id;
    int rc;

    printf("Main thread starting...\n");
    printf("Main thread ID: %lu\n", (unsigned long)pthread_self());

    /* Create the new thread:
       - &thread_id: where the created thread's ID is stored
       - NULL: default thread attributes
       - thread_function: function to run in new thread
       - NULL: argument passed to thread_function */
    rc = pthread_create(&thread_id, NULL, thread_function, NULL);
    if (rc != 0) {
        fprintf(stderr, "pthread_create failed: %d\n", rc);
        exit(EXIT_FAILURE);
    }

    /* Wait for the thread to finish */
    rc = pthread_join(thread_id, NULL);
    if (rc != 0) {
        fprintf(stderr, "pthread_join failed: %d\n", rc);
        exit(EXIT_FAILURE);
    }

    printf("Main thread exiting...\n");
    return 0;
}

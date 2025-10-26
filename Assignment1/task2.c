#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

// Thread function
void* greetingThread(void* arg) {
    char* name = (char*)arg;  // Retrieve name argument
    printf("Thread says: Hello, %s! Welcome to the world of threads.\n", name);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;
    char name[50];

    // Get user input
    printf("Enter your name: ");
    scanf("%s", name);

    // Create a thread and pass the user's name
    printf("Main thread: Waiting for greeting...\n");

    pthread_create(&thread, NULL, greetingThread, (void*)name);
    pthread_join(thread, NULL);  // Wait for thread to finish

    printf("Main thread: Greeting completed.\n");

    return 0;
}

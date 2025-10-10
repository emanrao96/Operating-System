#include <stdio.h>
#include <pthread.h>
#include <unistd.h>  // For sleep()

// Thread function
void* print_message(void* arg) {
    char* message = (char*)arg;  // Receive string argument
    printf("Thread ID: %lu | Message: %s\n", pthread_self(), message);
    sleep(1);
    return NULL;
}

int main() {
    pthread_t threads[3];
    char* messages[3] = {"Hello from Thread 1!", "Hi from Thread 2!", "Hey from Thread 3!"};

    // Create 3 threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, print_message, messages[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Main thread: All threads finished.\n");
    return 0;
}

#include <stdio.h>
#include <pthread.h>

// Thread function — runs in the new thread
void* print_number(void* arg) {
    // Convert the void pointer back to an int pointer, then get the value
    int num = *(int*)arg;
    printf("Thread received number: %d\n", num);
    printf("Square: %d\n", num * num);
    return NULL;
}

int main() {
    pthread_t thread_id;
    int number = 42;

    printf("Creating thread with argument: %d\n", number);

    // Create thread and pass address of 'number'
    pthread_create(&thread_id, NULL, print_number, &number);

    // Wait for the thread to finish
    pthread_join(thread_id, NULL);

    printf("Main thread done.\n");
    return 0;
}

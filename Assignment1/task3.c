#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Thread function
void* numberInfo(void* arg) {
    int num = *((int*)arg);  // Retrieve number passed from main
    printf("Thread: Number = %d\n", num);
    printf("Thread: Square = %d\n", num * num);
    printf("Thread: Cube = %d\n", num * num * num);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;
    int number;

    // Take user input
    printf("Enter an integer: ");
    scanf("%d", &number);

    // Create thread and pass number
    pthread_create(&thread, NULL, numberInfo, &number);

    // Wait for thread to complete
    pthread_join(thread, NULL);

    printf("Main thread: Work completed.\n");
    return 0;
}

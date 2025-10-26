#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Thread function to calculate factorial
void* factorialThread(void* arg) {
    int n = *((int*)arg);
    long long* result = malloc(sizeof(long long)); // allocate memory for result

    *result = 1;
    for (int i = 1; i <= n; i++) {
        *result *= i;
    }

    pthread_exit((void*)result); // return result pointer
}

int main() {
    pthread_t thread;
    int num;
    long long* factorialResult;

    // Get user input
    printf("Enter a number: ");
    scanf("%d", &num);

    // Create thread
    pthread_create(&thread, NULL, factorialThread, &num);

    // Wait for thread to finish and get return value
    pthread_join(thread, (void**)&factorialResult);

    // Print the result
    printf("Factorial of %d is: %lld\n", num, *factorialResult);

    // Free allocated memory
    free(factorialResult);

    printf("Main thread: Work completed.\n");
    return 0;
}

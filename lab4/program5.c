#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>  


void* calculate_sum(void* arg) {
    int n = *(int*)arg;             
    int* result = malloc(sizeof(int));  
    *result = 0;

    for (int i = 1; i <= n; i++) {
        *result += i;
    }

    printf("Thread calculated sum of 1 to %d = %d\n", n, *result);
    return (void*)result;  
}

int main() {
    pthread_t thread_id;
    int n = 100;     // We will calculate sum of 1 to 100
    void* sum;       // To store the return value from thread

    // Create a thread and pass 'n' as argument
    pthread_create(&thread_id, NULL, calculate_sum, &n);

    // Wait for the thread to finish and get return value
    pthread_join(thread_id, &sum);

    // Print the result received from thread
    printf("Main received result: %d\n", *(int*)sum);

    // Free the dynamically allocated memory
    free(sum);

    return 0;
}

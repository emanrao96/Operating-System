#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>

// Thread function to check if a number is prime
void* check_prime(void* arg) {
    int n = *(int*)arg;
    bool* is_prime = malloc(sizeof(bool));
    *is_prime = true;

    if (n <= 1)
        *is_prime = false;
    else {
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                *is_prime = false;
                break;
            }
        }
    }

    printf("Thread checked number: %d\n", n);
    return (void*)is_prime;  // Return pointer to result
}

int main() {
    pthread_t thread_id;
    int num;
    void* result;

    printf("Enter a number: ");
    scanf("%d", &num);

    // Create thread to check prime
    pthread_create(&thread_id, NULL, check_prime, &num);

    // Wait for thread to finish and get result
    pthread_join(thread_id, &result);

    bool is_prime = *(bool*)result;
    if (is_prime)
        printf("%d is a prime number.\n", num);
    else
        printf("%d is NOT a prime number.\n", num);

    free(result);
    return 0;
}

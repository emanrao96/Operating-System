#include <stdio.h>
#include <pthread.h>

typedef struct {
    int id;
    char* message;
} ThreadData;

// Thread function — receives and prints the data
void* printData(void* arg) {
    // Convert void* back to ThreadData*
    ThreadData* data = (ThreadData*)arg;
    printf("Thread %d says: %s\n", data->id, data->message);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Initialize data for each thread
    ThreadData data1 = {1, "Hello"};
    ThreadData data2 = {2, "World"};

    // Create two threads and pass data to each
    pthread_create(&t1, NULL, printData, &data1);
    pthread_create(&t2, NULL, printData, &data2);

    // Wait for both threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("All threads done.\n");
    return 0;
}

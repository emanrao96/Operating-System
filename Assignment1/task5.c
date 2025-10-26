#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

// Define the Student struct
typedef struct {
    int student_id;
    char name[50];
    float gpa;
} Student;

// Thread function to check Dean’s List eligibility
void* checkDeansList(void* arg) {
    Student* stu = (Student*)arg;
    int* eligible = malloc(sizeof(int)); // allocate memory for return value

    printf("Thread for Student ID: %d\n", stu->student_id);
    printf("Name: %s\n", stu->name);
    printf("GPA: %.2f\n", stu->gpa);

    if (stu->gpa >= 3.5) {
        printf("Result: %s is on the Dean's List!\n\n", stu->name);
        *eligible = 1;  // eligible
    } else {
        printf("Result: %s is NOT on the Dean's List.\n\n", stu->name);
        *eligible = 0;  // not eligible
    }

    pthread_exit((void*)eligible);
}

int main() {
    pthread_t threads[3];
    Student students[3] = {
        {101, "Ali", 3.8},
        {102, "Sara", 3.4},
        {103, "Usman", 3.9}
    };

    int deansListCount = 0;
    int* result;

    printf("=== Student Database System ===\n\n");

    // Create 3 threads for 3 students
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, checkDeansList, (void*)&students[i]);
    }

    // Wait for all threads and collect results
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], (void**)&result);
        deansListCount += *result;
        free(result);
    }

    printf("Total students on Dean's List: %d\n", deansListCount);
    printf("Main thread: Work completed.\n");
    return 0;
}

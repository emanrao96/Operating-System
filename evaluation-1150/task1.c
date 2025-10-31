// Write a C program that creates 4 threads. Each thread should:

// 1.  Receive a unique number N as an argument (use values: 10, 20, 30, 40)
// 2.  Calculate the sum of numbers from 1 to N
// 3.  Print the thread number and calculated sum
// 4.  Return the sum through thread's return value
// Main thread should:
// Create all 4 threads and pass arguments Wait for all threads to complete
// Collect all return values
// Calculate and print the total of all sums

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
 
void* calculate_sum(void* arg){  //function to calculate sum
    int n=*((int*)arg);  //get value of n passed as argument
    int* result=malloc(sizeof(int));  //Allocate memory to store result
    *result=0;

    for(int i=1;i<=n;i++){   //calculate sum from 1 to n
        *result+=i;      //add i to result
    }

    printf("Thread for value: %d \n Sum for %d : %d\n",n,n,*result);  //print thread number and calculated sum

    pthread_exit((void*)result); //return sum through return value of thread
}
int main(){
    pthread_t threads[4];    //array to hold thread IDs
    int values[4]={10,20,30,40};  //values to be passed to threads
    int* result; //pointer to hold return value from threads
    int sum=0;  //variable to hold total sum of all threads

     //create 4 threads
    for(int i=0;i<4;i++){
        pthread_create(&threads[i],NULL,calculate_sum,&values[i]);
    }

    //wait for all threads to complete and collect return values
    for(int i=0;i<4;i++){
        pthread_join(threads[i],(void**)&result);
        sum+=*result;
        free(result);
    }
    //print total sum of all threads

    printf("=============Total Sum ==============\n");
    printf("Total sum of all threads: %d\n",sum);
    return 0;

}
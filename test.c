#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void* thread_func(void* arg) 
{
    printf("Hello from the thread!\n");
    return NULL;
}

int main() 
{
    pthread_t thread_id;

    // Create a new thread
    if (pthread_create(&thread_id, NULL, thread_func, NULL) != 0) 
    {
        perror("Failed to create thread");
        return 1;
    }

    // Give the thread some time to execute.
    sleep(2);

    // 🚨🚨 Uncomment the following line to reclaim resources of the thread, 
    // preventing the leak.🚨🚨
    pthread_join(thread_id, NULL);

    printf("Exiting main function.\n");
    return 0;
}
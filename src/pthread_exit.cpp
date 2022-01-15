#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void* callback(void* arg)
{
    sleep(1);
    printf("我是子线程， id: %ld \n", pthread_self());
    for (size_t i = 0; i < 9; i++)
    {
        printf("child -- i == %d \n", i);
    }
    return nullptr;
}

int main(int argc, char * argv[])
{
    pthread_t tid;
    pthread_create(&tid, nullptr, callback, nullptr);
    for (size_t i = 0; i < 5; i++)
    {
        printf("主线程， i = %d \n", i);
    }
    printf("主线程 %ld \n", pthread_self());
    pthread_exit(NULL);
    // sleep(3);
    return 0;
}
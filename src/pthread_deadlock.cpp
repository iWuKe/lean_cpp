//线程同步-互斥锁

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>

#define MAX 1000
//全局变量
int number;

//创建一把互斥锁
//全局变量，多个线程共享
pthread_mutex_t mutex;

//线程处理函数
void* funcA_NUM(void* arg)
{
    for (size_t i = 0; i < MAX; i++)
    {
        pthread_mutex_lock(&mutex);
        int cur = number;
        cur++;
        usleep(10);
        number = cur;
        //忘记解锁
        printf("A thread id %u, number = %d \n", pthread_self(), number);
    }
    return nullptr;
}

//线程处理函数
void* funcB_NUM(void* arg)
{
    for (size_t i = 0; i < MAX; i++)
    {
        pthread_mutex_lock(&mutex);
        int cur = number;
        cur++;
        number = cur;
        pthread_mutex_unlock(&mutex);
        printf("B thread id %u, number = %d \n", pthread_self(), number);
        usleep(5);
    }
    return nullptr;
}
int main(int argc, const char* argv[])
{
    pthread_t p1, p2;
    //初始化互斥锁
    pthread_mutex_init(&mutex, NULL);

    //创建两个子线程
    pthread_create(&p1, NULL, funcA_NUM, NULL);
    pthread_create(&p2, NULL, funcB_NUM, NULL);

    //阻塞， 资源回收
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    //销毁互斥锁
    //线程销毁后，再去释放互斥锁
    pthread_mutex_destroy(&mutex);
    return 0;
}
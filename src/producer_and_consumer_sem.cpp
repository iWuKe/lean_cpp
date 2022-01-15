//使用信号量实现生产消费者模型

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <queue>
#include <semaphore.h>


int number;

std::queue<int> line;

//生产者信号量
sem_t psem;
//消费者信号量
sem_t csem;

//互斥锁变量
pthread_mutex_t mutex;

//生产者回调函数
void* producer(void *arg)
{
    //一直循环生产
    while (1)
    {
        //要先拿灯，是因为如果生产者先加锁而等不到灯，消费者被阻塞也无法生产信号灯，导致死锁
        //生产者拿一个信号灯
        sem_wait(&psem);
        //加锁
        pthread_mutex_lock(&mutex);
        //创建一个新节点
        number++;
        line.push(number);
        //通知消费者消费
        sem_post(&csem);
        printf("+++ producer, number = %d, line size = %d,  tid = %ld \n", number, line.size(), pthread_self());
        //互斥锁解锁
        pthread_mutex_unlock(&mutex);
        //慢一点生产
        sleep(rand() % 3);
    }
    return NULL;
}

//消费者回调函数
void* consumer(void* arg)
{
    //一直在消费
    while (1)
    {
        //等待信号灯
        sem_wait(&csem);
        //加锁
        pthread_mutex_lock(&mutex);

        printf("--- consumer: number %d \n", line.front());
        //消费头节点，将其删除
        line.pop();

        //通知生产者进行生产，加信号灯
        sem_post(&psem);
        pthread_mutex_unlock(&mutex);
        sleep(rand() % 3);
    }
    return NULL;
}

int main(int argc, char* argv[])
{
    //5个生产者可以同时生产
    sem_init(&psem, 0, 5);
    //消费者线程没有资源，因此不能进行消费
    sem_init(&csem, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    //创建5个生产者，5个消费者
    pthread_t ptid[5];
    pthread_t ctid[5];

    for (size_t i = 0; i < 5; i++)
    {
        pthread_create(&ptid[i], NULL, producer, NULL);
    }
    for (size_t i = 0; i < 5; i++)
    {
        pthread_create(&ctid[i], NULL, consumer, NULL);
    }
    
    for (size_t i = 0; i < 5; i++)
    {
        //阻塞等待子线程退出
        pthread_join(ptid[i], NULL);
    }
    for (size_t i = 0; i < 5; i++)
    {
        //阻塞等待子线程退出
        pthread_join(ctid[i], NULL);
    }
    
    pthread_mutex_destroy(&mutex);
    
    return 0;
}


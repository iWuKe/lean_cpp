//使用条件变量实现生产消费者模型

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <queue>



int number;

std::queue<int> line;

//定义条件变量，控制消费者线程
pthread_cond_t cond;
//互斥锁变量
pthread_mutex_t mutex;

//生产者回调函数
void* producer(void *arg)
{
    //一直循环生产
    while (1)
    {
        //加锁
        pthread_mutex_lock(&mutex);
        //创建一个新节点
        number++;
        line.push(number);
        printf("+++ producer, number = %d, line size = %d,  tid = %ld \n", number, line.size(), pthread_self());
        //互斥锁解锁
        pthread_mutex_unlock(&mutex);
        //生产了任务，通知消费者消费
        pthread_cond_broadcast(&cond);
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
        //加锁
        pthread_mutex_lock(&mutex);

        while (line.empty())
        {
            //任务队列已经没有商品可以消费了
            //消费线程需要阻塞
            //线程加互斥成功，但是线程阻塞在这行代码上，锁还没解开
            //其他线程在访问这把锁的时候也会阻塞，生产者也会阻塞->死锁
            //这个函数会自动将线程拥有的锁解开
            pthread_cond_wait(&cond, &mutex);
            printf("我找不到商品\n");
            //消费者线程解除后会自动把这把锁锁上
            //这时当前线程又重新拥有了这一把互斥锁
        }
        printf("--- consumer: number %d, tid = %ld \n", line.front(), pthread_self());
        //消费头节点，将其删除
        line.pop();
        pthread_mutex_unlock(&mutex);
        sleep(rand() % 3);
    }
    return NULL;
}

int main(int argc, char* argv[])
{
    //初始化条件变量，
    pthread_cond_init(&cond, NULL);
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
    
    //销毁条件变量
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);
    
    return 0;
}


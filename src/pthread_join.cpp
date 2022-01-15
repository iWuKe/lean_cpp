#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

struct Test
{
    int num;
    int age;
};


void* callback(void* arg)
{
    sleep(1);
    printf("我是子线程， id: %ld \n", pthread_self());
    for (size_t i = 0; i < 9; i++)
    {
        printf("child -- i == %d \n", i);
    }
    struct Test *t = (struct Test*)arg;
    t->num = 100;
    t->age = 6;
    pthread_exit(&t);
    return nullptr;
}

int main(int argc, char * argv[])
{
    struct Test t;
    pthread_t tid;
    pthread_create(&tid, nullptr, callback, &t);
    printf("主线程 %ld \n", pthread_self());

    pthread_join(tid, nullptr);
    printf("num: %d, age = %d \n", t.num, t.age);
    
    // sleep(3);
    return 0;
}
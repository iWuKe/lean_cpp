#include "lean_thread/thread_pool.h"

//创建线程池并初始化
ThreadPool* threadPoolCreate(int min, int max, int queueSize)
{
  ThreadPool* pool = (ThreadPool*)malloc(sizeof(ThreadPool));

  do
  {
    if (pool == NULL)
    {
      printf("malloc threadpool fail...\n");
      break;
    }

    pool->threadIDs = (pthread_t*)malloc(sizeof(pthread_t) * max);
    if (pool->threadIDs == NULL)
    {
      printf("malloc threadIDs fail...\n");
      break;
    }
    memset(pool->threadIDs, 0, sizeof(pthread_t) * max);
    pool->minNum = min;
    pool->maxNum = max;
    pool->busyNUM = 0;
    pool->liveNum = min;  // 和最小个数相等
    pool->exitNum = 0;

    //锁整个的线程池
    if (pthread_mutex_init(&pool->mutexPool, NULL) != 0 ||
        pthread_mutex_init(&pool->mutexBusy, NULL) != 0 ||
        pthread_mutex_init(&pool->notEmpty, NULL) != 0 ||
        pthread_mutex_init(&pool->notFull, NULL) != 0)
    {
      printf("mutex or condition init fial ...\n");
      break;
    }

    //任务队列
    pool->taskQ = (Task*)malloc(sizeof(Task) * queueSize);
    pool->queueCapacity = queueSize;
    pool->queueSize = 0;
    pool->queueFront = 0;
    pool->queueRear = 0;

    pool->shutdown = 0;
    //创建线程
    pthread_create(&pool->managerID, NULL, manager, pool);
    for (size_t i = 0; i < min; i++)
    {
      pthread_create(&pool->threadIDs[i], NULL, worker, pool);
    }
  } while (0);
  
  //释放资源
  if (pool && pool->threadIDs) free(pool->threadIDs);
  if (pool && pool->taskQ) free(pool->taskQ);
  if (pool) free(pool);
  
  return NULL;
}

//销毁线程池并初始化
int threadPoolDestroy(ThreadPool* pool)
{
  if (pool == NULL)
  {
    return -1;
  }
  //关闭线程池
  pool->shutdown = 1;
  //阻塞回收管理者线程
  pthread_join(pool->managerID, NULL);
  //唤醒阻塞的消费者线程
  for (size_t i = 0; i < pool->liveNum; i++)
  {
    pthread_cond_signal(&pool->notEmpty);
  }
  //释放堆内存
  if (pool->taskQ)
  {
    free(pool->taskQ);
  }
  
  if (pool->threadIDs)
  {
    free(pool->threadIDs);
  }
  
  pthread_mutex_destroy(&pool->mutexPool);
  pthread_mutex_destroy(&pool->mutexBusy);
  pthread_cond_destroy(&pool->notEmpty);
  pthread_cond_destroy(&pool->notFull);

  free(pool);
  pool = NULL;

  return 0;
}

//给线程池添加任务
void threadPoolAdd(ThreadPool* pool, void(*func)(void*), void *arg)
{
  pthread_mutex_lock(&pool->mutexPool);
  while (pool->queueSize == pool->queueCapacity && !pool->shutdown)
  {
    //阻塞生产者线程
    pthread_cond_wait(&pool->notFull, &pool->mutexPool);
  }
  if (pool->shutdown)
  {
    pthread_mutex_unlock(&pool->mutexPool);
    return;
  }
  
  //添加任务
  pool->taskQ[pool->queueRear].function = func;
  pool->taskQ[pool->queueRear].arg = arg;
  pool->queueRear = (pool->queueRear + 1) % pool->queueCapacity;
  pool->queueSize ++;

  pthread_cond_signal(&pool->notEmpty);
  pthread_mutex_unlock(&pool->mutexPool);
}

//获取线程池中工作的线程的个数
int threadPoolBusyNum(ThreadPool* pool)
{
  //加互斥锁
  pthread_mutex_lock(&pool->mutexPool);
  int busyNum = pool->busyNum;
  pthread_mutex_unlock(&pool->mutexPool);

  return busyNum;
}

//获取线程池活着的线程个数
int threadPoolAliveNum(ThreadPool* pool)
{
  //加互斥锁
  pthread_mutex_lock(&pool->mutexPool);
  int aliveNum = pool->liveNum;
  pthread_mutex_unlock(&pool->mutexPool);
  return aliveNum;
}

//////////////////////////////////////
//工作的线程（消费者线程）任务函数
void* worker(void* arg)
{
  ThreadPool* pool = (ThreadPool*)arg;

  while (1)
  {
    pthread_mutex_lock(&pool->mutexPool);
    //当前任务队列是否为空
    while (pool->queueSize == 0 && !pool->shutdown)
    {
      //阻塞工作线程
      pthread_cond_wait(&pool->notEmpty, &pool->mutexpool);

      //判断是不是要销毁线程
      if (pool->exitNum > 0)
      {
        pool->exitNum --;
        if (pool->liveNum > pool->minNum)
        {
          pool->liveNum --;
          pthread_mutex_unlock(&pool->mutexPool);
          threadExit(pool);
        }
      }
    }

    //判断线程池是否被关闭了
    if (pool->shutdown)
    {
      pthread_mutex_unlock(&pool->mutexPool);
      threadExit(pool);
    }
    
    //从任务队列中取出一个任务
    Task task;
    task.function = pool->taskQ[pool->queueFront].function;
    task.arg = pool->taskQ[pool->queueFront].arg;
    //移动头结点
    pool->queueFront = (pool->queueFront + 1) % pool->queueCapacity;
    pool->queueSize --;
    //解锁
    pthread_cond_signal(&pool->notFull);
    pthread_mutex_unlock(&pool->mutexPool);

    printf("thread %ld, start working ...\n", pthread_self());
    pthread_mutex_lock(&pool->mutexBusy);
    pool->busyNUM ++;
    pthread_mutex_unlock(&pool->mutexBusy);
    task.function(task.arg);
    free(task.arg);
    task.arg = NULL;

  }
  
}














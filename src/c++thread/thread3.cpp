/*
条件变量
*/
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <functional>
#include <condition_variable>
#include <list>

/*
condition_variable需要配合std::unique_lock<std::mutex>进行
wait操作，也就是阻塞线程的操作

condition_variable_any:可以和任意带有lock(),unlock()语义的mutex搭配使用
也就说有四种
std::mutex 独占的非递归互斥锁
std::timed_mutex 带超时的独占非递归互斥锁
std::recursive_mutex 不带超时功能的递归互斥锁
std::recursive_timed_mutex 带超时的递归互斥锁
*/

using namespace std;

class SyncQueue
{
private:
//存储队列数据
    list<int> m_queue;
    //互斥锁
    mutex m_mutex;
    //不为空的条件变量
    condition_variable m_notEmpty;
    //没有满的条件变量
    condition_variable m_notFull;
    //任务队列的最大任务数
    int m_max_size;

public:
    SyncQueue(int max_size) : m_max_size(max_size){}
    //入队
    void put(const int& x)
    {
        unique_lock<mutex> locker(m_mutex);
        //判断任务队列是否已经满了
        while (m_queue.size() == m_max_size)
        {
            cout << "任务队列已满，请耐心等候 ..." << endl;
            //阻塞线程
            m_notFull.wait(locker);
        }
        //将任务放入到任务队列中
        m_queue.push_back(x);
        cout << x << " 被生产" << endl;
        //通知消费者消费
        m_notEmpty.notify_one();
    }

    int take()
    {
        unique_lock<mutex> locker(m_mutex);
        while (m_queue.empty())
        {
            cout << "任务队列已空，请耐心等候..." << endl;
            m_notEmpty.wait(locker);
        }
        //从任务队列中取出任务(消费)
        int x = m_queue.front();
        m_queue.pop_front();
        cout << x << " 被消费" << endl;
        //通知生产者进行生产
        m_notFull.notify_one();
        return x;
    }

    bool empty()
    {
        lock_guard<mutex> locker(m_mutex);
        return m_queue.empty();
    }

    bool full()
    {
        lock_guard<mutex> locker(m_mutex);
        return m_queue.size() == m_max_size;
    }

    int size()
    {
        lock_guard<mutex> locker(m_mutex);
        return m_queue.size();
    }
    ~SyncQueue(){m_queue.clear();}
};

void test0()
{
    SyncQueue taskQ(50);
    //生产者
    auto produce = bind(&SyncQueue::put, &taskQ, placeholders::_1);
    //消费者
    auto consume = bind(&SyncQueue::take, &taskQ);

    //生产者消费者各三个线程
    thread t1[3];
    thread t2[3];
    for (size_t i = 0; i < 3; i++)
    {
        t1[i] = thread(produce, i+100);
        t2[i] = thread(consume);
    }

    for (size_t i = 0; i < 3; i++)
    {
        t1[i].join();
        t2[i].join();
    }
    return;
}

int main()
{
    test0();
    cout << "--------------------------- " << endl;
    return 0;
}










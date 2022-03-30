#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <chrono>
#include <mutex>

using namespace std;

/*
std::mutex 独占的互斥锁，不能递归使用
std::lock_guard在上面提供的这个构造函数构造对象时，会自动锁定互斥量，而在退出作用域后进行析构时会自动解锁，从而保证了互斥量的正确操作
std::recursive_mutex递归互斥锁允许统一鲜橙多次获得互斥锁，可以用来解决同一线程需要多次获取互斥量时死锁的问题
std::timed_mutex是超时独占互斥锁，
*/

int g_num = 0;
mutex g_num_mutex;

void slow_increment(int id)
{
  for (size_t i = 0; i < 3; i++)
  {
    g_num_mutex.lock();
    g_num++;
    cout << id << " - >" << g_num << endl;
    g_num_mutex.unlock();
    this_thread::sleep_for(chrono::seconds(1));
  }
}

/*
1.在所有线程的任务函数执行完毕之前互斥锁对象不能被析构，一定要在程序中保证这个对象的可用性
2.互斥锁的个数和共享资源的个数相等，也即是说每一个共享资源都应该对应一个互斥锁对象。互斥锁对象的个数和线程的个数没有关系
*/
void test0()
{
  thread t1(slow_increment, 0);
  thread t2(slow_increment, 1);
  t1.join();
  t2.join();
}

void slow_increment_guard(int id)
{
  for (size_t i = 0; i < 3; i++)
  {
    lock_guard<mutex> lock(g_num_mutex);
    g_num++;
    cout << id << " - >" << g_num << endl;
    this_thread::sleep_for(chrono::seconds(1));
  }
}

void test1()
{
  thread t1(slow_increment_guard, 0);
  thread t2(slow_increment_guard, 1);
  t1.join();
  t2.join();
}

//由于lock_guard是独占锁，所以递归调用会导致死锁
struct Calculate
{
  Calculate() : m_i(6){}
  void mul(int x)
  {
    cout << "mul" << endl;
    lock_guard<mutex> locker(m_mutex);
    m_i *= x;
  }
  void div(int x){
    cout << "div" << endl;
    lock_guard<mutex> locker(m_mutex);
    m_i /= x;
  }

  void both(int x, int y)
  {
    cout << "both" << endl;
    lock_guard<mutex> locker(m_mutex);
    mul(x);
    div(y);
  }

  int m_i;
  mutex m_mutex;
};

//std::recursive_mutex允许统一线程多次获得互斥锁
struct Calculate1
{
  Calculate1() : m_i(6){}
  void mul(int x)
  {
    cout << "mul" << endl;
    lock_guard<recursive_mutex> locker(m_mutex);
    m_i *= x;
  }
  void div(int x){
    cout << "div" << endl;
    lock_guard<recursive_mutex> locker(m_mutex);
    m_i /= x;
  }

  void both(int x, int y)
  {
    cout << "both" << endl;
    lock_guard<recursive_mutex> locker(m_mutex);
    mul(x);
    div(y);
  }

  int m_i;
  recursive_mutex m_mutex;
};

/*

*/
void test2()
{
  //Calculate cal;
  Calculate1 cal;
  cal.both(6, 3);
}


int main()
{
  test0();
  cout << "-----------------------" << endl;
  test1();
  cout << "-----------------------" << endl;
  test2();
  return 0;
}
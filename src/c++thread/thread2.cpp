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
1.使用递归锁的场景往往都是可以简化的，使用递归互斥锁很容易放纵复杂逻辑的产生，从而导致bug的产生
2. 递归互斥锁比非递归互斥锁效率低一点
3. 递归互斥锁虽然允许同一线程获得同一互斥锁的所有权，但是最大次数并未具体说明，一旦超过一定次数，就会抛出std::system错误
*/
void test2()
{
  //Calculate cal;
  Calculate1 cal;
  cal.both(6, 3);
}

/*
std::timed_mutex超时独占互斥锁,主要是在获取互斥锁资源时增加了超时等待功能，因为不知道获取锁资源需要等待多长时间
，为了保证不一直等待下去，设置了一个超时时长，超时后线程就可以解除阻塞去做其他的事情了
多两个成员函数 try_lock_for()和try_lock_until()
try_lock_for()是当线程获取不到互斥锁资源时，让线程阻塞一定时间
try_lock_until()是当线程获取不到互斥锁资源时，让线程阻塞到某一个指定的时间点
关于两个函数的返回值，当得到互斥锁的所有权之后，函数会马上解除阻塞，返回true，如果阻塞的时长用完或达到指定时间点之后
函数会解除阻塞，返回false
*/
timed_mutex g_mutex;
void work()
{
  chrono::seconds timeout(1);
  while (true)
  {
    if (g_mutex.try_lock_for(timeout))
    {
      cout << "当前线程id " << this_thread::get_id() << " 得到互斥锁所有权 " << endl;
      //模拟处理任务用了一定时长
      this_thread::sleep_for(chrono::seconds(10));
      g_mutex.unlock();
      break;
    }else
    {
      cout << "当前线程id " << this_thread::get_id() << " 没有得到互斥锁所有权 " << endl;
      //模拟其他任务
      this_thread::sleep_for(chrono::seconds(1));
    }
  }
}

void test3()
{
  thread t1(work);
  thread t2(work);
  t1.join();
  t2.join();
}

/*
std::recursive_timed_mutex递归超时互斥锁和timed_mutex是一样的，只不过它可以允许一个线程多次获得互斥锁所有权，
另外也拥有和他一样的弊端，不建议频繁使用
*/

int main()
{
  test0();
  cout << "-----------------------" << endl;
  test1();
  cout << "-----------------------" << endl;
  test2();
  cout << "-----------------------" << endl;
  test3();
  cout << "-----------------------" << endl;
  return 0;
}
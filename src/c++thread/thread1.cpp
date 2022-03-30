/*
c++多线程
*/

/*
join() 等待线程终止（阻塞）
detach()线程分离，分理处主线程和创建出的子线程
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <chrono>

using namespace std;

void func(int num, string str)
{
  for (size_t i = 0; i < 10; i++)
  {
    cout << "子线程 " << i << " num :" << num << " str " << str << endl;
  }
}

void do_some_work()
{
  for (size_t i = 0; i < 5; i++)
  {
    cout << "work " << i << endl;
  }
}

void test0()
{
  cout  << "test0 " << endl;
  thread t(func, 520, "i love you");
  std::thread my_tread(do_some_work);
  cout << " t " << t.get_id() << endl;
  cout << " t1 " << my_tread.get_id() << endl;
  t.join();
  my_tread.join();
}

void download1()
{
  this_thread::sleep_for(chrono::milliseconds(500));
  cout << "子线程1 : " << this_thread::get_id() << ",找到历史正文" << endl;
}

void download2()
{
  this_thread::sleep_for(chrono::milliseconds(300));
  cout << "子线程2 ： " << this_thread::get_id() << ",找到历史正文" << endl;
}

void doSomething()
{
    cout << "集齐历史正文, 呼叫罗宾...." << endl;
    cout << "历史正文解析中...." << endl;
    cout << "起航，前往拉夫德尔...." << endl;
    cout << "找到OnePiece, 成为海贼王, 哈哈哈!!!" << endl;
    cout << "若干年后，草帽全员卒...." << endl;
    cout << "大海贼时代再次被开启...." << endl;
}
void test1()
{
  thread t1(download1);
  thread t2(download2);
  //阻塞主线程
  t1.join();
  t2.join();
  doSomething();
}

/*
detach()线程分离，分理处主线程和创建出的子线程
detach不回阻塞县车顶，子线程和主线程分离之后，在主线程中就不能对子线程做任何控制了，例如join和get_id等
*/
void test2()
{
  cout << "主线程id " << this_thread::get_id() << endl;
  thread t(func, 520, "i love you");
  thread t1(do_some_work);
  cout << "t " << t.get_id() << endl;
  cout << "t1 " << t1.get_id() << endl;
  t.detach();
  t1.detach();
  //core down 此时子线程已经分离，无法在get_id了
  // cout << "t " << t.get_id() << endl;
  // cout << "t1 " << t1.get_id() << endl;
  //让主线程休眠，等待子线程执行完毕
  this_thread::sleep_for(chrono::seconds(5));
}

/*
joinable()用于判断主线程和子线程是否处于关联状态,返回布尔类型
*/
void test3()
{
  thread t1;
  cout << "t1 joinable " << t1.joinable() << endl;
  t1 = thread(do_some_work);
  cout << "t1 joinable " << t1.joinable() << endl;
  t1.join();
  cout << "join t1 joinable " << t1.joinable() << endl;

  thread  t2(do_some_work);
  cout << "t2 joinable " << t2.joinable() << endl;
  t2.detach();
  cout << "t2 joinable " << t2.joinable() << endl;

}

//静态函数获取cpu线程数
void test4()
{
  int num = thread::hardware_concurrency();
  cout << "cpu number " << num << endl;
}

int main(int argc, char* argv[])
{
  // test0();
  // cout << "------------------------------------" << endl;
  // test1();
  // cout << "------------------------------------" << endl;
  // test2();
  cout << "------------------------------------" << endl;
  test3();
  cout << "------------------------------------" << endl;
  test4();
  return 0;
}


